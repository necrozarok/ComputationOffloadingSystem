// Clocal_info.cpp: 实现文件
//

#include "stdafx.h"
#include "COS.h"
#include "Clocal_info.h"
#include "afxdialogex.h"

// Clocal_info

IMPLEMENT_DYNAMIC(Clocal_info, CMFCPropertyPage)

Clocal_info::Clocal_info()
	: CMFCPropertyPage(IDD_LOCALINFO)
	, m_host(_T(""))
	, m_ipaddr(_T(""))
	, m_ram(_T(""))
	, m_cpu(_T(""))
{

}

Clocal_info::~Clocal_info()
{
}

BOOL Clocal_info::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	return TRUE;
}
void Clocal_info::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER, m_host);
	DDX_Text(pDX, IDC_IPADDR, m_ipaddr);
	DDX_Text(pDX, IDC_RAM, m_ram);
	DDX_Text(pDX, IDC_CPU, m_cpu);
}

BEGIN_MESSAGE_MAP(Clocal_info, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_GETINFO, &Clocal_info::OnBnClickedGetinfo)
END_MESSAGE_MAP()



// Clocal_info 消息处理程序




void Clocal_info::OnBnClickedGetinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	// 以下两行为执行nslookup
	//HINSTANCE hRslt = ShellExecute(NULL, _T("open"),_T("Nslookup.EXE"), NULL, NULL, SW_SHOWNORMAL);
	//assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))   //初始化
	{
		AfxMessageBox("初始化网络环境失败!", MB_YESNO | MB_ICONQUESTION);
		//return TRUE;
	}
	char szHostName[MAX_PATH + 1];
	gethostname(szHostName, MAX_PATH);  //得到计算机名
	hostent *p = gethostbyname(szHostName); //从计算机名得到主机信息
	if (p == NULL)
	{
		AfxMessageBox("得到本机网络信息失败!");
		//return TRUE;
	}
	m_host = szHostName;       //保存主机名
	int nCount = 0;                 //保存主机地址
	char *pIP = inet_ntoa(*(in_addr *)p->h_addr_list[0]);//将32位IP转化为字符串IP
	m_ipaddr = pIP;             //保存主机IP地址
	//从文件中读取CPU，RAM
	::GetPrivateProfileString("Local Info", "CPU", "读取文件失败", m_cpu.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
	::GetPrivateProfileString("Local Info", "RAM", "读取文件失败", m_ram.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
	UpdateData(FALSE);          //显示各个数据
	WSACleanup();               //释放Winsock API
	
}
