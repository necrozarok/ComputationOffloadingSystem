#pragma once


// Cwork

class Cwork : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(Cwork)

public:
	Cwork();
	CString BootOpenDialog();
	CString m_strDescPath;
	virtual ~Cwork();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORK
	};
#endif
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_exepath;
};


