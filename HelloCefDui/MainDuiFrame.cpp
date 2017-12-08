#include "stdafx.h"

#include "include/cef_browser.h"
#include "include/views/cef_window.h"

#include "simple_handler.h"
#include "MainDuiFrame.h"
#include "BrowserFrame.h"

#define WM_USER_MY_MESSAGE WM_USER + 1 // my message

int receivedMsgCountNum = 0;
CefRefPtr<SimpleHandler> m_handler(new SimpleHandler(false));

void MainDuiFrame::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

CDuiString MainDuiFrame::GetSkinFile() {
	return _T("menu.xml");
}

LRESULT MainDuiFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 在父类前，处理某些消息
	return __super::HandleMessage(uMsg, wParam, lParam); // 让父类去处理部分消息
}

LRESULT MainDuiFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_USER_MY_MESSAGE)
	{
		receivedMsgCountNum++;
		CDuiString str;
		str.Format(_T("Received Message: %d"), receivedMsgCountNum);
		receivedMsgCount->SetText(str);
	}
	// 在父类处理常规消息(HandleMessage)之后
	return __super::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
}

void MainDuiFrame::InitWindow()
{
	// find controls
	pList = static_cast <CListUI*>(m_PaintManager.FindControl(_T("list1")));
	receivedMsgCount = static_cast <CTextUI*>(m_PaintManager.FindControl(_T("receiveMsgCount")));

	// insert content into list.
	CDuiString str;
	for (int i = 0; i < 100; i++)
	{
		CHorizontalLayoutUI* group = new CHorizontalLayoutUI;
		group->SetFixedWidth(200);
		group->SetFixedHeight(20);
		CButtonUI* button1 = new CButtonUI;
		button1->SetBkImage(_T("button_down.bmp"));
		button1->SetFixedWidth(50);
		group->Add(button1);

		CLabelUI* label = new CLabelUI;
		RECT rect;
		rect.left = 10;
		rect.right = 0;
		rect.bottom = 0;
		rect.top = 0;
		label->SetPadding(rect);
		str.Format(_T("%d"), i);
		label->SetText(str);
		label->SetFixedWidth(100);
		group->Add(label);

		pList->Add(group);
	}
}

void MainDuiFrame::Notify(TNotifyUI& msg) {
	CDuiString name = msg.pSender->GetName();
	if (msg.sType == _T("selectchanged"))
	{
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tablayout")));

		if (name == _T("Option1"))
		{
			pControl->SelectItem(0);
		}
		else if (name == _T("Option2"))
		{
			pControl->SelectItem(1);
		}
		else if (name == _T("Option3"))
		{
			pControl->SelectItem(2);
		}
	}
	else {
		return WindowImplBase::Notify(msg);
	}
}


void MainDuiFrame::OnClick(TNotifyUI& msg) {
	CDuiString name = msg.pSender->GetName();
	if (name == _T("closebtn"))
	{
		Close();
	}
	else if (name == _T("hello"))
	{
		::MessageBox(NULL, _T("I'm button"), _T("You clicked!"), NULL); // welcome button
	}
	else if (name == _T("openBrowser"))
	{
		BrowserFrame pFrame(m_handler);
		pFrame.Create(NULL, _T("Browser"), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_ACCEPTFILES);
		pFrame.ShowModal();
	}
	else if (name == _T("postMsg"))
	{
		::PostMessage(m_hWnd, WM_USER_MY_MESSAGE, NULL, NULL);
	}
}

LRESULT MainDuiFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnCreate(uMsg, wParam, lParam, bHandled);
}
LRESULT MainDuiFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

LRESULT MainDuiFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnDestroy(uMsg, wParam, lParam, bHandled);
}

LRESULT MainDuiFrame::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnKeyDown(uMsg, wParam, lParam, bHandled);
}

LRESULT MainDuiFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	return __super::OnSize(uMsg, wParam, lParam, bHandled);
}
//LRESULT MainDuiFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	switch (uMsg)
//	{
//	case WM_CREATE:
//	{
//		// 加载xml文件
//		m_PaintManager.Init(m_hWnd);
//		CDialogBuilder builder;
//		CControlUI* pRoot = builder.Create(_T("menu.xml"), (UINT)0, NULL, &m_PaintManager);
//		ASSERT(pRoot && "Failed to parse XML");
//		m_PaintManager.AttachDialog(pRoot);
//		m_PaintManager.AddNotifier(this);
//		return 0;
//	}
//	case WM_NCCALCSIZE: return 0;
//	case WM_NCACTIVATE:
//	{
//		if (!::IsIconic(m_hWnd))
//		{
//			return (wParam == 0) ? TRUE : FALSE;
//		}
//	}
//	case WM_DESTROY:
//	{
//		::PostQuitMessage(0);
//		break;
//	}
//	case WM_NCPAINT: return 0;
//	default:
//		break;
//	}
//
//	LRESULT result = 0;
//	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, result)) {
//		return result;
//	}
//
//	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
//}
