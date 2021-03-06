
// COSDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "COS.h"
#include "COSDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCTSDlg 对话框



CCTSDlg::CCTSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CTS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCTSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCTSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENTER, &CCTSDlg::OnBnClickedEnter)
END_MESSAGE_MAP()


// CCTSDlg 消息处理程序

BOOL CCTSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//使用正则表达式提取本地信息
	CString str_SystemInfo =ExecuteCmd("systeminfo"),ramtest;//得到本地信息
	char *char_SystemInfo, cpuinfo[200], raminfo[200];//保存所有本地信息，cpu信息，RAM信息
	char_SystemInfo = StringToChar(str_SystemInfo);
	//另一种CString to char 方案
	/*char_SystemInfo = str_SystemInfo.GetBuffer(str_SystemInfo.GetLength();
	str_SystemInfo.ReleaseBuffer();*/
	sscanf(str_SystemInfo, "%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n\
%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n\
%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^M]M%*[^M]Mhz%s", raminfo);
	sscanf(str_SystemInfo, "%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n\
%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^\n]\n%*[^:]:%[^\r]", cpuinfo);
	LPCWSTR CPUP, RAMP;
	CPUP = CharToWchar(cpuinfo);
	RAMP = CharToWchar(raminfo);
	//MessageBox(str_SystemInfo);
	
	//建立配置文件
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用
	BOOL ifFind = finder.FindFile(_T("D:\\CTSS.ini"));
	if (!ifFind)
	{
	::WritePrivateProfileStringW(L"Local Info", L"CPU", CPUP, L"D:\\CTSS.ini");
	::WritePrivateProfileStringW(L"Local Info", L"RAM", RAMP, L"D:\\CTSS.ini");
	::WritePrivateProfileStringW(L"Server Info", L"RAM", L"32GB", L"D:\\CTSS.ini");
	::WritePrivateProfileStringW(L"Server Info", L"CPU", L"16核", L"D:\\CTSS.ini");
	::WritePrivateProfileStringW(L"Server Info", L"BaiduPrice", L"15￥/次", L"D:\\CTSS.ini");
	::WritePrivateProfileStringW(L"Server Info", L"AmazonPrice", L"20￥/次", L"D:\\CTSS.ini");
	::WritePrivateProfileStringW(L"Server Info", L"TencentPrice", L"25￥/次", L"D:\\CTSS.ini");
	::WritePrivateProfileStringW(L"Server Info", L"AliyunPrice", L"30￥/次", L"D:\\CTSS.ini");
	}

	//将RAM值存入RamSize
	unsigned int ram1000, ram1;
	sscanf(raminfo, "%d%*[^0-9]%d", &ram1000, &ram1);
	RamSize = ram1000 * 1000 + ram1;
	//ramtest.Format(_T("%d"), RamSize);
	//MessageBox(ramtest);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCTSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCTSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCTSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCTSDlg::OnBnClickedEnter()
{
	// TODO: 在此添加控件通知处理程序代码
	// 创建属性表对象   
	Csheet m_sheet;
	// 打开模态向导对话框   
	m_sheet.DoModal();
}
