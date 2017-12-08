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
	// show web
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

	// find native view
	m_urlEdit = static_cast <CEditUI*>(m_PaintManager.FindControl(_T("urlAddress")));
}

LRESULT BrowserFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_USER + 1)
	{
		int a = 0;
	}
	// 在父类前，处理某些消息
	return __super::HandleMessage(uMsg, wParam, lParam); // 让父类去处理部分消息
}

LRESULT BrowserFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_USER + 1)
	{
		int a = 0;
		Close();
	}
	// 在父类处理常规消息(HandleMessage)之后
	return __super::HandleCustomMessage(uMsg, wParam, lParam, bHandled);
}

void BrowserFrame::Notify(TNotifyUI& msg) {
	CDuiString name = msg.pSender->GetName();
	if (msg.sType == _T("addressChange"))
	{
		LPCTSTR url = _T("a");
		m_urlEdit->SetText(url);
	}
	else {
		return WindowImplBase::Notify(msg);
	}
}

void BrowserFrame::OnClick(TNotifyUI& msg)
{
	CDuiString name = msg.pSender->GetName();
	if (name == _T("jumpUrl"))
	{
		// execute javascript
		m_handler->GetBrowser()->GetMainFrame()->ExecuteJavaScript(_T("alert('jumpUrl');"), m_handler->GetBrowser()->GetMainFrame()->GetURL(), 0);
		CDuiString url = m_urlEdit->GetText();
		if (!url.IsEmpty())
		{
			m_handler->GetBrowser()->GetMainFrame()->LoadURL((CefString)url);
		}
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
		//Close();
		::PostMessage(m_hWnd, WM_USER + 1, NULL, NULL);
	}
	else if (name == _T("scaleBrowser"))
	{
		HWND hwnd = ::FindWindowEx(m_hWnd, NULL, L"CefBrowserWindow", NULL);
		::MoveWindow(hwnd, 3, 100, 1000, 1200, TRUE);
	}

	__super::OnClick(msg);
}
