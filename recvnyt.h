
// recvnyt.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CrecvnytApp:
// �йش����ʵ�֣������ recvnyt.cpp
//

class CrecvnytApp : public CWinApp
{
public:
	CrecvnytApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CrecvnytApp theApp;