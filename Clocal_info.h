#pragma once


// Clocal_info

class Clocal_info : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(Clocal_info)

public:
	Clocal_info();
	virtual ~Clocal_info();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOCALINFO
	};
#endif
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGetinfo();
	CString m_host;
	CString m_ipaddr;
	CString m_ram;
	CString m_cpu;
};


