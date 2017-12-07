#include "stdafx.h"

#include "include/cef_browser.h"
#include "include/views/cef_window.h"

#include "simple_handler.h"
#include "BrowserFrame.h"

BrowserFrame::BrowserFrame(CefRefPtr<SimpleHandler> handler) {
	m_handler = handler;
}

BrowserFrame::~BrowserFrame() {}

void BrowserFrame::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
}

CDuiString BrowserFrame::GetSkinFile() {
	return _T("browser.xml");
}

void BrowserFrame::InitWindow()
{
	// 显示网页
	RECT _rt;
	GetClientRect(this->m_hWnd, &_rt);
	int nCx = GetSystemMetrics(SM_CXFULLSCREEN);
	int nCy = GetSystemMetrics(SM_CYFULLSCREEN);
	RECT rt;
	rt.left = _rt.left + 0;
	rt.top = _rt.top + 60;
	rt.bottom = rt.top + 540;
	rt.right = rt.left + 800;
	CefWindowInfo info;
	info.SetAsChild(m_hWnd, rt);
	CefBrowserSettings settings;

	BOOL successed = CefBrowserHost::CreateBrowser(info, m_handler, L"http://www.baidu.com", settings, NULL);
}

void BrowserFrame::Notify(TNotifyUI& msg) {
	CDuiString name = msg.pSender->GetName();
	CEditUI* pUrlEdit = static_cast <CEditUI*>(m_PaintManager.FindControl(_T("urlAddress")));
	if (msg.sType == _T("click"))
	{
		if (name == _T("jumpUrl"))
		{
			CDuiString url = pUrlEdit->GetText();
			m_handler->GetBrowser()->GetMainFrame()->LoadURL((CefString)url);
		}
		else if (name == _T("goback"))
		{
			m_handler->GetBrowser()->GoBack();
		}
		else if (name == _T("goforward"))
		{
			m_handler->GetBrowser()->GoForward();
		}
		else if (name == _T("refresh"))
		{
			m_handler->GetBrowser()->Reload();
		}
		else if (name == _T("close"))
		{
			Close();
		}
		else if (name == _T("scaleBrowser"))
		{
			HWND hwnd = ::FindWindowEx(m_hWnd, NULL, L"CefBrowserWindow", NULL);
			::MoveWindow(hwnd, 3, 100, 1000, 1200, TRUE);
		}
	}
	else if (msg.sType == _T("addressChange"))
	{
		LPCTSTR url = _T("a");
		pUrlEdit->SetText(url);
	}
}

LRESULT BrowserFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CREATE:
	{
		// 加载xml文件
		m_PaintManager.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("browser.xml"), (UINT)0, NULL, &m_PaintManager);
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
