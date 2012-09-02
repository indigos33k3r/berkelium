// Copyright (c) 2012 The Berkelium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Window.hpp"
#include "Berkelium.hpp"

#include <stdio.h>

namespace Berkelium {

Window::Window() {
	Berkelium::send("new Window");
}

Window::~Window() {
	Berkelium::send("delete Window");
}

bool Window::OnMessageReceived(const IPC::Message& msg) {
	bool msg_is_ok = true;
	IPC_BEGIN_MESSAGE_MAP_EX(Window, msg, msg_is_ok)
	IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateRect, OnMsgUpdateRect)
	IPC_MESSAGE_HANDLER(ViewHostMsg_UpdateTitle, OnMsgUpdateTitle)
	IPC_MESSAGE_HANDLER(ViewHostMsg_ContextMenu, OnMsgContextMenu)
	IPC_END_MESSAGE_MAP_EX()
	;
	return false;
}

void Window::OnMsgUpdateRect(const ViewHostMsg_UpdateRect_Params& params) {
	Berkelium::send("OnMsgUpdateRect");
	//window_delegate.onPaint(NULL, NULL, Rect(), 0, NULL, 0, 0, Rect());
}

void Window::OnMsgUpdateTitle(int32 page_id, string16 title, WebKit::WebTextDirection) {
	Berkelium::send("OnMsgUpdateTitle");
	//window_delegate.onTitleChanged((Window*)this, UTF16ToUTF8(title));
}

void Window::OnMsgContextMenu(const content::ContextMenuParams& params) {
	Berkelium::send("OnMsgContextMenu");
}

} // namespace Berkelium
