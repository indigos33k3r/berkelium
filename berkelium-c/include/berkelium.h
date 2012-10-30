// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BERKELIUM_API_H_
#define BERKELIUM_API_H_
#pragma once

// =========================================
// WARNING:
//   THIS FILE IS AUTOMATICALLY GENERATED!
//   !! ANY CHANGES WILL BE OVERWRITTEN !!
//
// See berkelium/berkelium-api/update.sh
// =========================================

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t bk_int32;
typedef int32_t bk_bool;
typedef const char* bk_string;

typedef bk_int32 BK_HostVersion;
typedef bk_int32 BK_BerkeliumFactory;
typedef bk_int32 BK_HostExecutable;
typedef bk_int32 BK_Profile;
typedef bk_int32 BK_LogDelegate;
typedef bk_int32 BK_HostDelegate;
typedef bk_int32 BK_Instance;
typedef bk_int32 BK_Window;
typedef bk_int32 BK_WindowDelegate;
typedef bk_int32 BK_Tab;
typedef bk_int32 BK_TabDelegate;

// =========================================
// interface HostVersion
// =========================================

// Returns the berkelium host version e.g. “22.0.1229.94”
bk_string BK_HostVersion_getVersionString(BK_HostVersion self);

// Returns the Major Version, e.g. “22”
bk_int32 BK_HostVersion_getMajor(BK_HostVersion self);

// Returns the Minor Version, always zero?
bk_int32 BK_HostVersion_getMinor(BK_HostVersion self);

// Returns the Build Version, e.g. “1229”
bk_int32 BK_HostVersion_getBuild(BK_HostVersion self);

// Returns the Patch Version, e.g. “94”
bk_int32 BK_HostVersion_getPatch(BK_HostVersion self);

// Returns true if the given Version is less or equal to the version of the executable represented by this executable object.
bk_bool BK_HostVersion_isMinVersion(BK_HostVersion self, bk_string version);

// =========================================
// class BerkeliumFactory
// =========================================

// Creates an HostExecutable Object representing the given executable.
BK_HostExecutable BK_BerkeliumFactory_forExecutable(bk_string pathTo);

// Creates an HostExecutable, the exectuable is searched through system path or system configuration (e.g. registry on windows)
BK_HostExecutable BK_BerkeliumFactory_forSystemInstalled();

// Returns the profile for the given application name.
BK_Profile BK_BerkeliumFactory_forProfile(bk_string application);

// Returns a Profile object representing the Google Chrome profile.
BK_Profile BK_BerkeliumFactory_getChromeProfile();

// Returns a Profile object representing the Chromium profile.
BK_Profile BK_BerkeliumFactory_getChromiumProfile();

// Returns the profile located inside the given path.
BK_Profile BK_BerkeliumFactory_forProfilePath(bk_string path);

// Creates a temporary profile that gets automatically removed after use.
BK_Profile BK_BerkeliumFactory_createTemporaryProfile();

// Creates a HostVersion object representing the given version string.
BK_HostVersion BK_BerkeliumFactory_forVersion(bk_string version);

// Creates a HostVersion object representing the given version number.
BK_HostVersion BK_BerkeliumFactory_forVersion(bk_int32 vMajor, bk_int32 vMinor, bk_int32 vBuild, bk_int32 vPatch);

// Launches a the given berkelium host process using the given profile.
BK_Instance BK_BerkeliumFactory_open(BK_HostExecutable executable, BK_Profile profile);

// =========================================
// interface HostExecutable
//
// Represents a reference to the executable file of the berkelium host process.
// =========================================

// Returns the version of this berkelium host executable.
BK_HostVersion BK_HostExecutable_getVersion(BK_HostExecutable self);

// =========================================
// interface Profile
//
// Represents a berkelium profile on disk.
// =========================================

// Returns true if this profile is already in use.
bk_bool BK_Profile_isInUse(BK_Profile self);

// Returns true if this profile was found on disk.
bk_bool BK_Profile_isFound(BK_Profile self);

// Returns true if this profile can be used without updating this profile to a newer version.
bk_bool BK_Profile_isSameVersion(BK_Profile self);

// Returns true if this profile is from a newer berkelium host version.
bk_bool BK_Profile_isTooNew(BK_Profile self);

// Returns the name of the application or “berkelium” if not specified.
bk_string BK_Profile_getApplicationName(BK_Profile self);

// Returns the full path to the used Profile.
bk_string BK_Profile_getProfilePath(BK_Profile self);

// =========================================
// enum LogType
// =========================================

// Represents the stdout stream of the berkelium host process.
void BK_LogType_HostOut(BK_LogType self);

// Represents the stderr stream of the berkelium host process.
void BK_LogType_HostErr(BK_LogType self);

// Represents debug messages of the berkelium library.
void BK_LogType_Debug(BK_LogType self);

// Represents error messages of the berkelium library.
void BK_LogType_Error(BK_LogType self);

// =========================================
// interface LogDelegate
//
// Handler for log messages. LogAdapter is an abstract class with empty function definitions for all functions in LogDelegate.
// =========================================

// Allows the client application to handle berkelium host console messages.
void BK_LogDelegate_log(BK_LogDelegate self, BK_Instance instance, BK_LogType type, bk_string message);

// =========================================
// interface HostDelegate
//
// Handler for events concerning the berkelium host process.
// =========================================

// Called if the host process was unexpected terminated.
void BK_HostDelegate_onCrashed(BK_HostDelegate self, BK_Instance instance);

// Called if the host process was properly closed.
void BK_HostDelegate_onClosed(BK_HostDelegate self, BK_Instance instance);

// =========================================
// interface Instance
//
// Represents a running berkelium host instance.
// =========================================

// Closes all open Windows/Tabs and the profile, terminates the host.
void BK_Instance_close(BK_Instance self);

// Returns the profile used to launch this instance.
BK_Profile BK_Instance_getProfile(BK_Instance self);

// Returns the executable used to launch this instance.
BK_HostExecutable BK_Instance_getExecutable(BK_Instance self);

// Add the given LogDelegate to this Instance.
void BK_Instance_addLogDelegate(BK_Instance self, BK_LogDelegate delegate);

// Remove the given LogDelegate from this Instance.
void BK_Instance_removeLogDelegate(BK_Instance self, BK_LogDelegate delegate);

// Add the given HostDelegate to this Instance.
void BK_Instance_addHostDelegate(BK_Instance self, BK_HostDelegate delegate);

// Remove the given HostDelegate from this Instance.
void BK_Instance_removeHostDelegate(BK_Instance self, BK_HostDelegate delegate);

// Forwards the given type/message to all log handlers attached to this instance.
void BK_Instance_log(BK_Instance self, BK_LogType type, bk_string message);

// Returns the number of active Windows.
bk_int32 BK_Instance_getWindowCount(BK_Instance self);

// Returns a list of all active windows.
BK_WindowList BK_Instance_getWindowList(BK_Instance self);

// Open a new window.
BK_Window BK_Instance_createWindow(BK_Instance self, bk_bool incognito);

// =========================================
// interface Window
// =========================================

// Returns the current tab count.
bk_int32 BK_Window_getTabCount(BK_Window self);

// Returns an ordered list of all tabs in this window.
BK_TabList BK_Window_getTabList(BK_Window self);

// Creates a new (about:blank) Tab.
BK_Tab BK_Window_createTab(BK_Window self);

// Move this Tab to the given index.
void BK_Window_moveTo(BK_Window self, BK_Tab tab, bk_int32 index);

// Returns true if this is a incognito window.
bk_bool BK_Window_isIncognito(BK_Window self);

// =========================================
// interface WindowDelegate
// =========================================

// =========================================
// interface Tab
// =========================================

// Closes this tab and removes it from the window.
void BK_Tab_close(BK_Tab self);

// Wait until all pending Java Script Events are handled.
void BK_Tab_sync(BK_Tab self);

// All methods called on this tab delegate are forwared to all tab delegates of this tab.
BK_TabDelegate BK_Tab_getTabDelegate(BK_Tab self);

// Add a TabDelegate to this tab.
void BK_Tab_addTabDelegate(BK_Tab self, BK_TabDelegate delegate);

// Remove a TabDelegate from this tab.
void BK_Tab_removeTabDelegate(BK_Tab self, BK_TabDelegate delegate);

// Set the size of this tab.
void BK_Tab_resize(BK_Tab self, bk_int32 width, bk_int32 height);

// Set the URL of this tab. A new tab has the url “about:blank”.
void BK_Tab_navigateTo(BK_Tab self, bk_string url);

// =========================================
// interface TabDelegate
//
// Handler for events concerning tab content.
// =========================================
void BK_TabDelegate_onClosed(BK_TabDelegate self, BK_Tab tab);
void BK_TabDelegate_onTitleChanged(BK_TabDelegate self, BK_Tab tab, bk_string title);
void BK_TabDelegate_onPaint(BK_TabDelegate self, BK_Tab tab);
void BK_TabDelegate_onPaintDone(BK_TabDelegate self, BK_Tab tab, BK_Rect rect);

#ifdef __cplusplus
}
#endif

#endif // BERKELIUM_API_H_
