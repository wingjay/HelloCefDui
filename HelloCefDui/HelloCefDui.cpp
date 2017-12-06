//HelloCefDui.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "HelloCefDui.h"
#include <windows.h>

#include "include/base/cef_scoped_ptr.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"

#include "simple_app.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	// start CEF
	// Enable High-DPI support on Windows 7 or newer.
	CefEnableHighDPISupport();

	void* sandbox_info = NULL;

#if defined(CEF_USE_SANDBOX)
	// Manage the life span of the sandbox information object. This is necessary
	// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
	CefScopedSandboxInfo scoped_sandbox;
	sandbox_info = scoped_sandbox.sandbox_info();
#endif

	// Provide CEF with command-line arguments.
	CefMainArgs main_args(hInstance);

	// Specify CEF global settings here.
	CefSettings settings;
#if !defined(CEF_USE_SANDBOX)
	settings.no_sandbox = true;
#endif

	// command-line arguments
	CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
	command_line->InitFromString(::GetCommandLineW());

	CefRefPtr<CefApp> app;
	SimpleApp::ProcessType process_type = SimpleApp::GetProcessType(command_line);
	if (process_type == SimpleApp::ProcessType::BrowserProcess)
		app = new SimpleApp();
	else if (process_type == SimpleApp::ProcessType::RendererProcess)
		app = new SimpleApp();
	else if (process_type == SimpleApp::ProcessType::OtherProcess)
		app = new SimpleApp();

	// Execute the secondary process, if any.
	int exit_code = CefExecuteProcess(main_args, app, sandbox_info);
	if (exit_code >= 0) {
		// The sub-process has completed so return here.
		return exit_code;
	}

	// Initialize CEF.
	CefInitialize(main_args, settings, app.get(), sandbox_info);

	// create first window


	// Run the CEF message loop. This will block until CefQuitMessageLoop() is
	// called.
	CefRunMessageLoop();

	// Shut down CEF.
	CefShutdown();

	return 0;
} 
