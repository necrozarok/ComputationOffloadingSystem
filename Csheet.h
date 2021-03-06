#pragma once
#include "Clocal_info.h"
#include "Cserver_info.h"
#include "Cwork.h"

// Csheet

class Csheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(Csheet)

public:
	Csheet();
	virtual ~Csheet();
	 
protected:
	DECLARE_MESSAGE_MAP()
private:
	Clocal_info  m_local;
	Cserver_info m_server;
	Cwork		 m_work;
};


