#include "stdafx.h"

#include "include/cef_browser.h"
#include "include/views/cef_window.h"

#include "simple_handler.h"
#include "MainDuiFrame.h"
#include "BrowserFrame.h"

CefRefPtr<SimpleHandler> m_handler(new SimpleHandler(false));

void MainDuiFrame::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

CDuiString MainDuiFrame::GetSkinFile() {
	return _T("browser.xml");
}

void MainDuiFrame::InitWindow()
{
	// 为List动态添加内容
	CDuiString str;
	CListUI* pList = static_cast <CListUI*>(m_PaintManager.FindControl(_T("list1")));
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
	if (msg.sType == _T("click"))
	{
		if (name == _T("closebtn"))
		{
			Close(); // 关闭按钮
		}
		else if (name == _T("hello"))
		{
			::MessageBox(NULL, _T("I'm button"), _T("You clicked!"), NULL); // 欢迎按钮
		}
		else if (name == _T("openBrowser"))
		{
			BrowserFrame pFrame(m_handler);
			pFrame.Create(NULL, _T("Browser"), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_ACCEPTFILES);
			pFrame.InitWindow();
			pFrame.ShowModal();
		}
	}
	else if (msg.sType == _T("selectchanged"))
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
}

LRESULT MainDuiFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CREATE:
	{
		// 加载xml文件
		m_PaintManager.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("menu.xml"), (UINT)0, NULL, &m_PaintManager);
		ASSERT(pRoot && "Failed to parse XML");
		m_PaintManager.AttachDialog(pRoot);
		m_PaintManager.AddNotifier(this);
		return 0;
	}
	case WM_NCCALCSIZE: return 0;
	case WM_NCACTIVATE:
	{
		if (!::IsIconic(m_hWnd))
		{
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	case WM_DESTROY:
	{
		::PostQuitMessage(0);
		break;
	}
	case WM_NCPAINT: return 0;
	default:
		break;
	}

	LRESULT result = 0;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, result)) {
		return result;
	}

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
