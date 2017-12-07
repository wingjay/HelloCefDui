#pragma once
#include "UIlib.h"

using namespace DuiLib;

class MainDuiFrame : public WindowImplBase
{
public:
	virtual CDuiString GetSkinFile();
	virtual void InitWindow();
	void Notify(TNotifyUI& msg);
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("MainDuiFrame"); }
	virtual CDuiString GetSkinFolder() { return _T(""); };
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	void OnFinalMessage(HWND hWnd);
};