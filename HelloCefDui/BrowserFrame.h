#pragma once
#include "UIlib.h"

using namespace DuiLib;

class BrowserFrame : public WindowImplBase
{
public:
	BrowserFrame(CefRefPtr<SimpleHandler>);
	~BrowserFrame();
	virtual CDuiString GetSkinFile();
	virtual void InitWindow();
	void Notify(TNotifyUI& msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("BrowserFrame"); }
	virtual CDuiString GetSkinFolder() { return _T(""); };
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	void OnFinalMessage(HWND hWnd);
private:
	CefRefPtr<SimpleHandler> m_handler;
};