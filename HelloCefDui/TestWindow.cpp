#include "stdafx.h"
#include "TestWindow.h"

void TestWindow::OnClick(TNotifyUI& msg)
{
	int a = 1;
}

void TestWindow::Notify(TNotifyUI &msg)
{
	return WindowImplBase::Notify(msg);
}

