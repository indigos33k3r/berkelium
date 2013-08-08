// Copyright (c) 2013 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BERKELIUM_API_WINDOW_HPP_
#define BERKELIUM_API_WINDOW_HPP_
#pragma once

// =========================================
// WARNING:
//   THIS FILE IS AUTOMATICALLY GENERATED!
//   !! ANY CHANGES WILL BE OVERWRITTEN !!
//
// See berkelium/berkelium-api/update.sh
// =========================================

#include <Berkelium/API/Berkelium.hpp>

namespace Berkelium {

class Window {
protected:
	Window();

public:
	virtual ~Window() = 0;

	// Returns the associated Runtime.
	virtual RuntimeRef getRuntime() = 0;

	// Internal Update Function
	virtual void internalUpdate() = 0;

	// Returns the current tab count.
	virtual int32_t getTabCount() = 0;

	// Returns an ordered list of all tabs in this window.
	virtual TabListRef getTabList() = 0;

	// Creates a new (about:blank) Tab.
	virtual TabRef createTab() = 0;

	// Returns the Instance used to create this Window.
	virtual InstanceRef getInstance() = 0;

	// Move this Tab to the given index.
	virtual void moveTo(TabRef tab, int32_t index) = 0;

	// Returns true if this is a incognito window.
	virtual bool isIncognito() = 0;
};

} // namespace Berkelium

#endif // BERKELIUM_WINDOW_HPP_
