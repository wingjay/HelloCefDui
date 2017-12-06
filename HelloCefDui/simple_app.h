#pragma once

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_

#include "include/cef_app.h"

// Implement application-level callbacks for the browser process.
class SimpleApp : public CefApp, public CefBrowserProcessHandler {
public:
	SimpleApp();

	enum ProcessType {
		BrowserProcess,
		RendererProcess,
		OtherProcess,
	};

	// Detemine the process tyep from command_line
	static ProcessType GetProcessType(CefRefPtr<CefCommandLine> command_line);

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE {
		return this;
	}

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(SimpleApp);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_APP_H_
