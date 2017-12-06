// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
#include "stdafx.h"
#include "simple_app.h"

#include <string>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"
#include "simple_handler.h"

SimpleApp::SimpleApp() {}

void SimpleApp::OnContextInitialized() {}
//void SimpleApp::OnContextInitialized() {
//	CEF_REQUIRE_UI_THREAD();
//
//	CefRefPtr<CefCommandLine> command_line =
//		CefCommandLine::GetGlobalCommandLine();
//
//#if defined(OS_WIN) || defined(OS_LINUX)
//	// Create the browser using the Views framework if "--use-views" is specified
//	// via the command-line. Otherwise, create the browser using the native
//	// platform framework. The Views framework is currently only supported on
//	// Windows and Linux.
//	const bool use_views = command_line->HasSwitch("use-views");
//#else
//	const bool use_views = false;
//#endif
//
//	// SimpleHandler implements browser-level callbacks.
//	CefRefPtr<SimpleHandler> handler(new SimpleHandler(use_views));
//
//	// Specify CEF browser settings here.
//	CefBrowserSettings browser_settings;
//
//	std::string url;
//
//	// Check if a "--url=" value was provided via the command-line. If so, use
//	// that instead of the default URL.
//	url = command_line->GetSwitchValue("url");
//	if (url.empty())
//		url = "http://www.jd.com";
//
//	if (use_views) {
//		// Create the BrowserView.
//		CefRefPtr<CefBrowserView> browser_view = CefBrowserView::CreateBrowserView(
//			handler, url, browser_settings, NULL, NULL);
//
//		// Create the Window. It will show itself after creation.
//		CefWindow::CreateTopLevelWindow(new SimpleWindowDelegate(browser_view));
//	}
//	else {
//		// Information used when creating the native window.
//		CefWindowInfo window_info;
//
//#if defined(OS_WIN)
//		// On Windows we need to specify certain flags that will be passed to
//		// CreateWindowEx().
//		window_info.SetAsPopup(NULL, "cefsimple");
//#endif
//
//		// create browser window
//		CefBrowserHost::CreateBrowser(window_info, handler, url, browser_settings,
//			NULL);
//		// create native window
//	}
//}
