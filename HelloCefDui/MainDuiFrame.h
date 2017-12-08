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
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
public:
	virtual void OnClick(TNotifyUI& msg);
	virtual LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	virtual LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	virtual LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	virtual LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	virtual LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
public:
	virtual LPCTSTR GetWindowClassName() const { return _T("MainDuiFrame"); }
	virtual CDuiString GetSkinFolder() { return _T(""); };
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	void OnFinalMessage(HWND hWnd);
private:
	CTextUI* receivedMsgCount;
	CListUI* pList;
};