// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifdef LINUX

#include <Berkelium/API/Logger.hpp>
#include <Berkelium/API/Runtime.hpp>
#include <Berkelium/Impl/Impl.hpp>
#include <Berkelium/Impl/Process.hpp>
#include <Berkelium/IPC/Pipe.hpp>
#include <Berkelium/IPC/PipeGroup.hpp>

#include <sys/wait.h>
#include <unistd.h>
#include <sstream>

#ifdef BERKELIUM_NO_HOST_REDIRECT
#define redirect 0
#else
#define redirect 1
#endif

namespace Berkelium {

namespace impl {

int exec(const std::vector<std::string>& args) {
	const size_t size = args.size();
	std::vector<char*> tmp(size + 1);
	for(size_t i = 0; i < size; i++) {
		tmp[i] = (char*)args[i].c_str();
	}
	tmp[size] = NULL;
    return execvp(args[0].c_str(), &tmp[0]);
}

#define BUF_SIZE 1024

using Berkelium::Ipc::PipeCallback;
using Berkelium::Ipc::PipeCallbackRef;

class ConsoleRedirector : public PipeCallback
{
private:
	RuntimeRef runtime;
	LogType type;
	std::string buffer;

public:
	ConsoleRedirector(RuntimeRef runtime, LogType type) :
		Berkelium::Ipc::PipeCallback(),
		runtime(runtime),
		type(type) {
	}

	virtual ~ConsoleRedirector() {
	}

	virtual void onPipeDataReady(Ipc::PipeRef pipe) {
		int fd = getPipeFd(pipe);

		char buf[BUF_SIZE];

		// read everything available into buffer
		while(!pipe->isEmpty()) {
			int r = ::read(fd, &buf, BUF_SIZE);
			if(r == 0) {
				break;
			} else if(r == -1) {
				bk_error("ConsoleWriter: read error!");
				return;
			}
			buffer += std::string(buf, 0, r);
		}

		// split into lines
		std::string line;
		std::istringstream is(buffer);

		if(buffer[buffer.length() - 1] == 10) {
			// buffer end == line end
			while(std::getline(is, line)) {
				log(line);
			}
			buffer = "";
		} else {
			// buffer end != line end
			std::list<std::string> lines;
			while(std::getline(is, line)) {
				lines.push_back(line);
			}
			if(lines.empty()) {
				return;
			}
			// store incomplete line
			buffer = lines.back();
			lines.pop_back();
			while(!lines.empty()) {
				log(lines.front());
				lines.pop_front();
			}
		}
	}

	void log(std::string line) {
		runtime->log(LogSource::Host, type, type == LogType::StdOut ? "STDOUT" : "STDERR", "", line);
	}
};

class ProcessLinuxImpl : public Process {
private:
	PipeCallbackRef out;
	PipeCallbackRef err;
	pid_t pid;
	int exit;

public:
	ProcessLinuxImpl(RuntimeRef runtime, LoggerRef logger, const std::string& dir) :
		Process(runtime, logger, dir),
		out(new ConsoleRedirector(runtime, LogType::StdOut)),
		err(new ConsoleRedirector(runtime, LogType::StdErr)),
		pid(-1),
		exit(-1) {
		group->registerCallback(pipeout, out);
		group->registerCallback(pipeerr, err);
	}

	virtual ~ProcessLinuxImpl() {
		if(pid == -1) return;
		logger->debug() << "waiting for pid " << pid << "..." << std::endl;
		wait(0);
	}

	bool wait(int options) {
		int status;
		int wp = waitpid(pid, &status, options);
		if (wp != -1) {
			if(wp == 0 && options == WNOHANG) {
				return true;
			}
			logger->debug() << "Child exited with status " << status << std::endl;
			exit = status;
			pid = -1;
			logger->info() << "berkelium host process terminated!" << std::endl;
			return false;
		} else {
			logger->systemError("waitpid");
		}
		return true;
	}

	virtual bool isRunning() {
		if(exit != -1) {
			return false;
		}
		return wait(WNOHANG);
	}


	virtual const bool start(const std::vector<std::string>& args) {
		pid = fork();
		switch (pid) {
		case -1: {
			logger->systemError("fork");
			return false;
		}
		case 0: {
			if(redirect) {
				dup2(getPipeFd(pipeout), 1);
				dup2(getPipeFd(pipeerr), 2);
			}
			int ret = exec(args);
			logger->systemError(("launch " + args[0]).c_str());
			::exit(ret);
			break;
		}
		default: {
			logger->debug() << "started berkelium host process with pid " << pid << "!" << std::endl;
		}
		}
		return true;
	}
};

ProcessRef Process::create(RuntimeRef runtime, LoggerRef logger, const std::string& dir) {
	return ProcessRef(new ProcessLinuxImpl(runtime, logger, dir));
}

} // namespace impl

} // namespace Berkelium

#endif // LINUX
