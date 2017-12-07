#pragma once
#include "UILib.h" /*必须放在最后一行include*/

using namespace DuiLib;
class TestWindow : public WindowImplBase {
public:
	virtual CDuiString GetSkinFile() { return _T("menu.xml"); };
	virtual void Notify(TNotifyUI& msg);
	virtual void OnClick(TNotifyUI& msg);
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("TestWindow"); }
	virtual CDuiString GetSkinFolder() { return _T(""); };
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
};