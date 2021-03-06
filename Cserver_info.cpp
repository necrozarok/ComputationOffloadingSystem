// Cserver_info.cpp: 实现文件
//

#include "stdafx.h"
#include "COS.h"
#include "Cserver_info.h"
#include "afxdialogex.h"
// Cserver_info





IMPLEMENT_DYNAMIC(Cserver_info, CMFCPropertyPage)

Cserver_info::Cserver_info()
	: CMFCPropertyPage(IDD_SERVERINFO)
	, m_pingshow(_T(""))
{
	
}

Cserver_info::~Cserver_info()
{
}
BOOL Cserver_info::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_serverlist.AddString(_T("Amazon"));

	m_serverlist.AddString(_T("Baidu"));

	m_serverlist.InsertString(2, _T("Tencent"));

	m_serverlist.InsertString(3, _T("Aliyun"));
	// 默认选择第一项   
	m_serverlist.SetCurSel(0);
	// 编辑框中默认显示第一项的文字“鸡啄米”   
	SetDlgItemText(IDC_TESTRESULT, _T("请选择云计算服务器类型"));
	return TRUE;
}
void Cserver_info::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SERVERLIST, m_serverlist);
	DDX_Text(pDX, IDC_TESTRESULT, m_pingshow);
}

BEGIN_MESSAGE_MAP(Cserver_info, CMFCPropertyPage)
	ON_EN_CHANGE(IDC_TESTRESULT, &Cserver_info::OnEnChangeTestresult)
	ON_CBN_SELCHANGE(IDC_SERVERLIST, &Cserver_info::OnCbnSelchangeServerlist)
	ON_BN_CLICKED(IDC_TEST, &Cserver_info::OnBnClickedTest)
END_MESSAGE_MAP()



// Cserver_info 消息处理程序




void Cserver_info::OnEnChangeTestresult()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Cserver_info::OnCbnSelchangeServerlist()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWeb;
	int nSel;

	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_serverlist.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_serverlist.GetLBText(nSel, strWeb);
	// 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中 
	CString report = _T("您选择了 ") + strWeb + _T(" 云服务器");
	SetDlgItemText(IDC_TESTRESULT, report);
}

void Cserver_info::OnBnClickedTest()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_TESTRESULT, _T("测试中.... "));
	MessageBox("校准测试结果");
	CString strWeb, target,cpu_info,ram_info,price_info;
	int nSel;
	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_serverlist.GetCurSel();
	// 根据选中项索引获取该项字符串并读取配置文件中的服务器ram,cpu,价格信息  
	m_serverlist.GetLBText(nSel, strWeb);
	if ("Baidu" == strWeb) {
		target = "ping.exe -n 2 baidu.com";
		::GetPrivateProfileString("Server Info","RAM","云计算服务器RAM读取失败", ram_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "CPU", "云计算服务器读取CPU失败", cpu_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "BaiduPrice", "云计算服务器价格读取失败", price_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
	}
	else if ("Aliyun" == strWeb) {
		target = "ping.exe -n 2 aliyun.com";
		::GetPrivateProfileString("Server Info", "RAM", "云计算服务器RAM读取失败", ram_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "CPU", "云计算服务器读取CPU失败", cpu_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "AliyunPrice", "云计算服务器价格读取失败", price_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
	}
	else if ("Amazon" == strWeb) {
		target = "ping.exe -n 2 amazon.com";
		::GetPrivateProfileString("Server Info", "RAM", "云计算服务器RAM读取失败", ram_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "CPU", "云计算服务器读取CPU失败", cpu_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "AmazonPrice", "云计算服务器价格读取失败", price_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
	}
	else if ("Tencent" == strWeb) {
		target = "ping.exe -n 2 cloud.tencent.com";
		::GetPrivateProfileString("Server Info", "RAM", "云计算服务器RAM读取失败", ram_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "CPU", "云计算服务器读取CPU失败", cpu_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
		::GetPrivateProfileString("Server Info", "TencentPrice", "云计算服务器价格读取失败", price_info.GetBuffer(MAX_PATH), MAX_PATH, "D:\\CTSS.ini");
	}
	else
	{
		MessageBox("请选择服务器!");
		return;
	}
	CString target2 = _T("c:\\windows\\system32\\") + target;
	unsigned int a;// 保存平均延迟整形数据
	CString str;
	//从结果中正则匹配平均延迟
	sscanf_s(ExecuteCmd(target2), "%*[^=]=%*[^=]=%*[^=]=%*[^=]=%*[^=]=%*[^=]=\
%*[^=]=%*[^=]=%*[^=]=%*[^=]=%*[^=]=%*[^=]=%d",&a);
	str.Format(_T("%d"), a);
	m_pingshow = _T("平均延迟：") + str + _T("ms\r\n")+_T("云计算服务器RAM大小：")+ StringToChar(ram_info) + _T("\r\n") + _T("云计算服务器CPU：")+ StringToChar(cpu_info) + _T("\r\n")+_T("云计算服务价格:")+ StringToChar(price_info) + _T("\r\n");//打印结果
	UpdateData(FALSE);
}

