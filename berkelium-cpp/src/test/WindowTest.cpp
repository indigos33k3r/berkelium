// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <Berkelium/API/Runtime.hpp>
#include <Berkelium/API/BerkeliumFactory.hpp>
#include <Berkelium/API/Instance.hpp>
#include <Berkelium/API/Window.hpp>
#include <Berkelium/API/Tab.hpp>
#include <Berkelium/Impl/Logger.hpp>
#include "gtest/gtest.h"

#include <list>

#include "test.h"

namespace {

using Berkelium::InstanceRef;
using Berkelium::WindowRef;
using Berkelium::TabRef;

class WindowTest : public ::testing::Test {
};

void createWindow(WindowRef& ret) {
	Berkelium::RuntimeRef runtime(Berkelium::BerkeliumFactory::getDefaultRuntime());
	Berkelium::Log::debug() << "creating host executable..." << std::endl;
	Berkelium::HostExecutableRef host = runtime->forSystemInstalled();
	ASSERT_NOT_NULL(host);

	Berkelium::Log::debug() << "creating profile..." << std::endl;
	Berkelium::ProfileRef profile = runtime->createTemporaryProfile();
	ASSERT_NOT_NULL(profile);

	Berkelium::Log::debug() << "launching berkelium host executable..." << std::endl;
	Berkelium::InstanceRef instance = runtime->open(host, profile);
	ASSERT_NOT_NULL(instance);

	Berkelium::Log::debug() << "creating window..." << std::endl;
	int old = instance->getWindowCount();
	ret = instance->createWindow(false);
	ASSERT_EQ(old + 1, instance->getWindowCount());
	ASSERT_EQ(0, ret->getTabCount());
}

TEST_F(WindowTest, create) {
	WindowRef subject;
	createWindow(subject);
	ASSERT_NOT_NULL(subject);
}

TEST_F(WindowTest, createSecondProcessWindow) {
	WindowRef subject1;
	createWindow(subject1);
	WindowRef subject2;
	createWindow(subject2);
	ASSERT_NOT_SAME(subject1->getInstance(), subject2->getInstance());
}

TEST_F(WindowTest, createSecondWindow) {
	WindowRef subject1;
	createWindow(subject1);
	ASSERT_NOT_NULL(subject1);

	Berkelium::Log::debug() << "creating second window..." << std::endl;
	WindowRef subject2 = subject1->getInstance()->createWindow(false);
	ASSERT_NOT_NULL(subject2);
	ASSERT_SAME(subject1->getInstance(), subject2->getInstance());
}

TEST_F(WindowTest, createWindows) {
	WindowRef first;
	createWindow(first);
	ASSERT_NOT_NULL(first);
	InstanceRef instance = first->getInstance();

	std::vector<WindowRef> windows;
	for(int i = 0; i < 10; i++) {
		Berkelium::Log::debug() << "creating window" << i << "..." << std::endl;
		WindowRef other = instance->createWindow(false);
		ASSERT_NOT_NULL(other);
		ASSERT_SAME(instance, other	->getInstance());
		windows.push_back(other);
	}
}

TEST_F(WindowTest, createDeleteRandomWindows) {
	WindowRef first;
	createWindow(first);
	ASSERT_NOT_NULL(first);
	InstanceRef instance = first->getInstance();

	std::list<WindowRef> windows;
	for(int i = 0; i < 20; i++) {
		bool del = !windows.empty();
		if(del) {
			del = rand() % 2 == 0;
		}
		if(del) {
			int pos = rand() % windows.size();
			for (std::list<WindowRef>::iterator it = windows.begin(); it != windows.end(); it++) {
				if(pos == 0) {
					Berkelium::Log::info() << "removing window..." << std::endl;
					windows.remove(*it);
					break;
				}
				pos--;
			}
		} else {
			Berkelium::Log::debug() << "creating window..." << std::endl;
			WindowRef other = instance->createWindow(rand() % 2 == 0);
			ASSERT_NOT_NULL(other);
			ASSERT_SAME(instance, other->getInstance());
			windows.push_back(other);
		}
	}
	windows.clear();
}

TEST_F(WindowTest, createTab) {
	WindowRef window;
	createWindow(window);
	ASSERT_NOT_NULL(window);

	ASSERT_EQ(0, window->getTabCount());
	TabRef tab = window->createTab();
	ASSERT_NOT_NULL(tab);
	ASSERT_EQ(1, window->getTabCount());
}

TEST_F(WindowTest, createMultipleTabs) {
	WindowRef window;
	createWindow(window);
	ASSERT_NOT_NULL(window);

	std::list<TabRef> tabs;
	for(int i = 0; i < 10; i++) {
		ASSERT_EQ(i, window->getTabCount());
		TabRef tab = window->createTab();
		ASSERT_NOT_NULL(tab);
		tabs.push_back(tab);
		ASSERT_EQ(i + 1, window->getTabCount());
	}
	tabs.clear();
	ASSERT_EQ(0, window->getTabCount());
}

TEST_F(WindowTest, free1) {
	WindowRef window;
	createWindow(window);
	ASSERT_NOT_NULL(window);

	TabRef tab = window->createTab();
	int count = tab->getWindow().use_count();
	window.reset();
	ASSERT_EQ(count - 1, tab->getWindow().use_count());
}

TEST_F(WindowTest, free2) {
	WindowRef window;
	createWindow(window);
	ASSERT_NOT_NULL(window);

	ASSERT_EQ(0, window->getTabCount());
	TabRef tab = window->createTab();
	ASSERT_NOT_NULL(tab);
	ASSERT_EQ(1, window->getTabCount());
	tab.reset();
	ASSERT_EQ(0, window->getTabCount());
}

} // namespace