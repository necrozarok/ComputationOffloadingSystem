
// stdafx.cpp : 只包括标准包含文件的源文件
// CTS.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

//将CString转Char
TCHAR* StringToChar(CString& str)
{
	int len = str.GetLength();
	TCHAR* tr = str.GetBuffer(len);
	str.ReleaseBuffer();
	return tr;
}
//将单字节cha转成Wchar
wchar_t* CharToWchar(char pszMultiByte[])
{
	int iSize;
	wchar_t* pwszUnicode;

	//返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
	iSize = MultiByteToWideChar(CP_ACP, 0, pszMultiByte, -1, NULL, 0); //iSize =wcslen(pwsUnicode)+1=6
	pwszUnicode = (wchar_t *)malloc(iSize * sizeof(wchar_t)); //不需要 pwszUnicode = (wchar_t *)malloc((iSize+1)*sizeof(wchar_t))
	MultiByteToWideChar(CP_ACP, 0, pszMultiByte, -1, pwszUnicode, iSize);
	return pwszUnicode;
}
//利用导管技术得到cmd执行命令后的输出
CString ExecuteCmd(CString str)
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		//MessageBox(_T("Error on CreatePipe()!"));
		return NULL;
	}
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	TCHAR* cmdline = StringToChar(str);
	if (!CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		//MessageBox("Error on CreateProcess()!");
		return NULL;
	}
	CloseHandle(hWrite);

	char buffer[4096];
	memset(buffer, 0, 4096);
	CString output;
	DWORD byteRead;
	while (true)
	{
		if (ReadFile(hRead, buffer, 4095, &byteRead, NULL) == NULL)
		{
			break;
		}
		output += buffer;
	}
	return output;
}
