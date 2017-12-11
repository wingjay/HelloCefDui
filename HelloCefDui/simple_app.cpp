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

#include "BrowserFrame.h"

int _count = 10;
// manually register callback
CefRefPtr<CefV8Value> callback_func_;
CefRefPtr<CefV8Context> callback_context_;
HWND browser_hwnd;

// Map of js callbacks.
// use functionName + browserId as key, value is context + callbackFunction
typedef std::map < std::pair<std::string, int>, std::pair<CefRefPtr<CefV8Context>, CefRefPtr<CefV8Value> > > CallbackMap;
CallbackMap callback_map_;

SimpleApp::SimpleApp() {}

//// The browser process UI thread has been initialized...
void SimpleApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();
}
// send startup information to a new render process
void SimpleApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) {
	int a = 1;
}



// The render process main thread has been initialized...
// Receive startup information in the new render process...
void SimpleApp::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) {
	CEF_REQUIRE_RENDERER_THREAD();
}
void SimpleApp::OnWebKitInitialized() {
	// WebKit has been initialized, register V8 extensions...
	int a = 1;
}
void SimpleApp::OnBrowserCreated(CefRefPtr<CefBrowser> browser) {
	int a = 1;
}
bool SimpleApp::OnBeforeNavigation(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefRequest> request,
	NavigationType navigation_type,
	bool is_redirect) {
	// Allow or block different types of navigation...
	return false;
}
void SimpleApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context) {
	// JavaScript context created, add V8 bindings here
	CEF_REQUIRE_RENDERER_THREAD();
	CefRefPtr<CefV8Value> object = context->GetGlobal();
	CefRefPtr<CefV8Handler> myHandler = this;

	// transfer k-v
	CefRefPtr<CefV8Value> str = CefV8Value::CreateString("wingjay");
	object->SetValue("user_name", str, V8_PROPERTY_ATTRIBUTE_NONE);
	// provide c++ function to js
	CefRefPtr<CefV8Value> getCountFun = CefV8Value::CreateFunction("getCountFromJs", myHandler);
	object->SetValue("getCountFromJs", getCountFun, V8_PROPERTY_ATTRIBUTE_NONE);

	// async function
	object->SetValue("asyncGetUserInfo", CefV8Value::CreateFunction("asyncGetUserInfo", myHandler), V8_PROPERTY_ATTRIBUTE_NONE);
	// register js callback
	CefRefPtr<CefV8Value> myRegister = CefV8Value::CreateFunction("register", myHandler);
	object->SetValue("registerFunction", myRegister, V8_PROPERTY_ATTRIBUTE_NONE);

	// asyncGetUserById
	object->SetValue("asyncGetUserById", CefV8Value::CreateFunction("asyncGetUserById", myHandler), V8_PROPERTY_ATTRIBUTE_NONE);
}



void SimpleApp::OnContextReleased(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context) {
	// JavaScript context released, release V8 references.
	// empty callback_map
	if (!callback_map_.empty())
	{
		CallbackMap::iterator it = callback_map_.begin();
		for (; it != callback_map_.end();)
		{
			if (it->second.first->IsSame(context))
			{
				callback_map_.erase(it++);
			}
			else {
				it++;
			}
		}
	}
}
void SimpleApp::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_RENDERER_THREAD();
}

// Render process receiving IPC message
bool SimpleApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
	CefProcessId source_process,
	CefRefPtr<CefProcessMessage> message) {
	// Handle IPC messages from browser process.
	CEF_REQUIRE_RENDERER_THREAD();
	CefString name = message->GetName();
	if (name == "user_info")
	{
		CefRefPtr<CefListValue> data = message->GetArgumentList();
		// use callback to return data.
		CefV8ValueList args;
		args.push_back(CefV8Value::CreateString(data->GetString(0)));
		args.push_back(CefV8Value::CreateInt(data->GetInt(1)));
		callback_func_->ExecuteFunctionWithContext(callback_context_, NULL, args);
		return true;
	} 
	else if (name == "asyncGetUserById")
	{
		if (callback_map_.empty()) return false;
		CefRefPtr<CefListValue> result = message->GetArgumentList();
		// convert result to CefV8Value
		CefV8ValueList args;
		args.push_back(CefV8Value::CreateString(result->GetString(0)));
		args.push_back(CefV8Value::CreateInt(result->GetInt(1)));

		// find callback from callback_map_

		CallbackMap::const_iterator it = callback_map_.find(std::make_pair(name, browser->GetIdentifier()));
		if (it != callback_map_.end())
		{
			CefRefPtr<CefV8Context> context = it->second.first;
			CefRefPtr<CefV8Value> callback = it->second.second;

			callback->ExecuteFunctionWithContext(context, NULL, args);
			return true;
		}
	}
	return false;
}


// js function entry
bool SimpleApp::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception) {
	CEF_REQUIRE_RENDERER_THREAD();
	if (name == "getCountFromJs")
	{
		retval = CefV8Value::CreateInt((int32)_count);
		return true;
	}
	else if (name == "asyncGetUserInfo")
	{
		// fetch data from BrowserWindow.
		browser_hwnd = FindWindow(L"BrowserFrame", NULL);
		::SendMessage(browser_hwnd, WM_USER_ASYNC_GET_USER_INFO, NULL, NULL);
		return true;
	}
	else if (name == "asyncGetUserById")
	{
		CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
		if (arguments.size() == 2 && arguments[0]->IsInt() && arguments[1]->IsFunction())
		{
			// stored callback map
			int browser_id = context->GetBrowser()->GetIdentifier();
			callback_map_.insert(std::make_pair(std::make_pair(name, browser_id), 
				std::make_pair(context, arguments[1])));
			// fecth data from Browser Process by simpleHandler::OnProcessMessageReceived
			CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(name);
			CefRefPtr<CefListValue> args = msg->GetArgumentList();
			args->SetInt(0, arguments[0]->GetIntValue());
			context->GetBrowser()->SendProcessMessage(PID_BROWSER, msg);
			return true;
		}
	}
	else if (name == "register")
	{
		// manually register a callback
		if (arguments.size() == 1 && arguments[0]->IsFunction())
		{
			callback_func_ = arguments[0];
			callback_context_ = CefV8Context::GetCurrentContext();
			return true;
		}
	}
	return false;
}