#pragma once


// Cserver_info

class Cserver_info : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(Cserver_info)

public:
	Cserver_info();
	virtual ~Cserver_info();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERINFO
	};
#endif
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnEnChangeTestresult();
	afx_msg void OnCbnSelchangeServerlist();
	CComboBox  m_serverlist;
	afx_msg void OnBnClickedTest();
	CString m_pingshow;
};


