// Csheet.cpp: 实现文件
//

#include "stdafx.h"
#include "COS.h"
#include "Csheet.h"


// Csheet

IMPLEMENT_DYNAMIC(Csheet, CMFCPropertySheet)

Csheet::Csheet()
{
	m_psh.pszCaption = _T("计算转移系统");
	m_psh.dwFlags |= PSH_NOAPPLYNOW; //去掉“应用”按钮 
	m_psh.dwFlags &= ~PSH_HASHELP; //去掉“帮助”按钮 
	SetLook(PropSheetLook_Tabs);
	AddPage(&m_local);
	AddPage(&m_server);
	AddPage(&m_work);
}

Csheet::~Csheet()
{
}


BEGIN_MESSAGE_MAP(Csheet, CMFCPropertySheet)
END_MESSAGE_MAP()



// Csheet 消息处理程序


