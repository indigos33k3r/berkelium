// Copyright (c) 2013 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <Berkelium/API/BerkeliumFactory.hpp>
#include <Berkelium/API/Runtime.hpp>
#include <Berkelium/API/Util.hpp>
#include <Berkelium/API/Logger.hpp>
#include <Berkelium/API/LogDelegate.hpp>
#include <Berkelium/Impl/Impl.hpp>
#include <Berkelium/Impl/Filesystem.hpp>

#include <set>

using Berkelium::impl::Filesystem;

namespace Berkelium {

Runtime::Runtime() {
}

Runtime::~Runtime() {
}

namespace {

RuntimeWRef defaultRuntime;

bool checkPath(const char* p, std::string& path) {
	if(!Filesystem::exists(p)) return false;
	path = Filesystem::absolute(p);
	return true;
}

} // namespace

namespace impl {

template<typename T>
struct set {
	typedef std::set<T, std::owner_less<T>> type;
};

typedef set<LogDelegateRef>::type LogDelegateRefSet;

class RuntimeLogDelegate : public LogDelegate {
public:
	RuntimeLogDelegate() :
		LogDelegate() {
	}

	virtual ~RuntimeLogDelegate() {
	}

	virtual void log(RuntimeRef runtime, LogSource source, LogType type, const std::string& clazz, const std::string& name, const std::string& message) {
		if(runtime) {
			runtime->log(source, type, clazz, name, message);
		}
	}
};

class RuntimeImpl : public Runtime {
private:
	LoggerRef logger;
	std::string defaultExecutable;
	LogDelegateRefSet logs;
	LogDelegateRef target;
	RuntimeWRef self;

	RuntimeImpl(const RuntimeImpl&);
	void operator=(const RuntimeImpl&);

	RuntimeImpl() :
		Runtime(),
		logger(),
		defaultExecutable(""),
		logs(),
		target(new RuntimeLogDelegate()),
		self() {
	}

public:
	static RuntimeRef createRuntime() {
		RuntimeImpl* impl = new RuntimeImpl();
		RuntimeRef ret(impl);
		impl->self = ret;
		impl->logger = impl::newLogger(impl->target, ret, "Runtime", "");
		return ret;
	}

	virtual ~RuntimeImpl() {
	}

	RuntimeRef getSelf() {
		return self.lock();
	}

	virtual void setDefaultExecutable(const std::string& pathTo) {
		defaultExecutable = pathTo;
	}

	virtual HostExecutableRef forExecutable(const std::string& pathTo) {
		return HostExecutableRef(newHostExecutable(getSelf(), pathTo));
	}

	virtual HostExecutableRef forSystemInstalled() {
		std::string path;

#ifdef WIN32
		path = Berkelium::Util::getEnv("PROGRAMFILES(X86)", "C:\\Program Files") + "\\Google\\Chrome\\Application\\chrome.exe";
#elif defined(LINUX)
		if(!defaultExecutable.empty() && checkPath(defaultExecutable.c_str(), path)) {
		} else if(checkPath("berkelium", path)) {
		} else if(checkPath("../berkelium", path)) {
		} else if(checkPath("../berkelium-host/berkelium", path)) {
		} else if(checkPath("../../berkelium-host/berkelium", path)) {
		} else if(checkPath("../../berkelium", path)) {
		} else {
			return HostExecutableRef();
		}
#else
#error "please add path to chrome here"
#endif

		logger->debug() << "using berkelium host executable " << path << std::endl;

		return newHostExecutable(getSelf(), path);
	}

	virtual ProfileRef forProfile(const std::string& application) {
		return impl::newProfile(getSelf(), application);
	}

	virtual ProfileRef getChromeProfile() {
		return impl::getChromeProfile(getSelf());
	}

	virtual ProfileRef getChromiumProfile() {
		return impl::getChromiumProfile(getSelf());
	}

	virtual ProfileRef forProfilePath(const std::string& path) {
		return impl::forProfilePath(getSelf(), path);
	}

	virtual ProfileRef createTemporaryProfile() {
		return impl::createTemporaryProfile(getSelf());
	}

	virtual HostVersionRef forVersion(const std::string& version) {
		return impl::newVersion(getSelf(), version);
	}

	virtual HostVersionRef forVersion(int32_t vMajor, int32_t vMinor, int32_t vBuild, int32_t vPatch) {
		return impl::newVersion(getSelf(), vMajor, vMinor, vBuild, vPatch);
	}

	virtual InstanceRef open(HostExecutableRef executable, ProfileRef profile) {
		return impl::newInstance(getSelf(), executable, profile);
	}

	virtual LoggerRef getLogger(const std::string& clazz, const std::string& name) {
		return impl::newLogger(target, getSelf(), clazz, name);
	}

	virtual void addLogDelegate(LogDelegateRef delegate) {
		logs.insert(delegate);
	}

	virtual void removeLogDelegate(LogDelegateRef delegate) {
		for(LogDelegateRefSet::iterator it = logs.begin(); it != logs.end(); it++) {
			LogDelegateRef ref = *it;
			if(ref.get() == delegate.get()) {
				it = logs.erase(it);
			}
		}
	}

	virtual void log(LogSource source, LogType type, const std::string& clazz, const std::string& name, const std::string& message) {
		for(LogDelegateRefSet::iterator it = logs.begin(); it != logs.end(); it++) {
			LogDelegateRef ref = *it;
			ref->log(getSelf(), source, type, clazz, name, message);
		}
	}
};

} // namespace impl

RuntimeRef BerkeliumFactory::createRuntime() {
	RuntimeRef ret(impl::RuntimeImpl::createRuntime());
	if(defaultRuntime.expired()) {
		defaultRuntime = ret;
	}
	return ret;
}

RuntimeRef BerkeliumFactory::getDefaultRuntime() {
	RuntimeRef ret(defaultRuntime.lock());
	if(!ret) {
		throw "No default Runtime found!";
	}
	return ret;
}

namespace Util {

RuntimeRef createRuntime(int argc, char* argv[]) {
	RuntimeRef ret(BerkeliumFactory::createRuntime());
	Berkelium::Util::parseCommandLine(ret, argc, argv);
	ret->addLogDelegate(impl::newLogDelegate());
	return ret;
}

} // namespace Util

} // namespace Berkelium
