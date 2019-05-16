// Cwork.cpp: 实现文件
//

#include "stdafx.h"
#include "COS.h"
#include "Cwork.h"
#include "afxdialogex.h"
// Cwork

IMPLEMENT_DYNAMIC(Cwork, CMFCPropertyPage)

Cwork::Cwork()
	: CMFCPropertyPage(IDD_WORK)
	, m_exepath(_T(""))
{

}

Cwork::~Cwork()
{
}

BOOL Cwork::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	return TRUE;
}
void Cwork::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_exepath);
}

BEGIN_MESSAGE_MAP(Cwork, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &Cwork::OnBnClickedButton1)
END_MESSAGE_MAP()

CString Cwork::BootOpenDialog()   //返回选择的文件名称
{
	CString strFile = _T("");

	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Computational Application (*.exe)|*.exe|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}

	return strFile;
}

// Cwork 消息处理程序




void Cwork::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strDescPath = "";        //类的成员变量

  //"打开文件"对话框，选择文件，返回其路径
	m_strDescPath = BootOpenDialog();
	m_exepath = m_strDescPath;
	UpdateData(FALSE);
}
