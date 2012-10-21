// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BERKELIUM_HOSTDELEGATE_HPP_
#define BERKELIUM_HOSTDELEGATE_HPP_
#pragma once

// =========================================
// WARNING:
//   THIS FILE IS AUTOMATICALLY GENERATED!
//   !! ANY CHANGES WILL BE OVERWRITTEN !!
//
// See berkelium/berkelium-api/update.sh
// =========================================

#include "berkelium/Berkelium.hpp"

namespace Berkelium {

// Handler for events concerning the berkelium host process.
class HostDelegate {
protected:
	HostDelegate();

public:
	virtual ~HostDelegate() = 0;

	// Called if the host process was unexpected terminated.
	virtual void onCrashed(InstanceRef instance);

	// Called if the host process was properly closed.
	virtual void onClosed(InstanceRef instance);
};

} // namespace Berkelium

#endif // BERKELIUM_HOSTDELEGATE_HPP_
