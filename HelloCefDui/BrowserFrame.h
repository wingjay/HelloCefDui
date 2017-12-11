#pragma once
#include "UIlib.h"

using namespace DuiLib;

#define WM_USER_TEST WM_USER + 1
#define WM_USER_ASYNC_GET_USER_INFO WM_USER + 2

class BrowserFrame : public WindowImplBase
{
public:
	explicit BrowserFrame(CefRefPtr<SimpleHandler> handler);
	~BrowserFrame();
	virtual CDuiString GetSkinFile();
	virtual void InitWindow();
public:
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
public:
	void Notify(TNotifyUI& msg);
	virtual void OnClick(TNotifyUI& msg);
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("BrowserFrame"); }
	virtual CDuiString GetSkinFolder() { return _T(""); };
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	void OnFinalMessage(HWND hWnd);
private:
	CefRefPtr<SimpleHandler> m_handler;
	CEditUI* m_urlEdit;
};