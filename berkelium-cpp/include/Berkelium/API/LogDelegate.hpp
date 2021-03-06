// Copyright (c) 2013 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BERKELIUM_API_LOGDELEGATE_HPP_
#define BERKELIUM_API_LOGDELEGATE_HPP_
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

class LogDelegate {
protected:
	LogDelegate();

public:
	virtual ~LogDelegate() = 0;

	// Allows the client application to handle berkelium library and host messages.
	virtual void log(RuntimeRef runtime, LogSource source, LogType type, const std::string& clazz, const std::string& name, const std::string& message) = 0;
};

} // namespace Berkelium

#endif // BERKELIUM_LOGDELEGATE_HPP_
