
// Exercise_2_1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExercise_2_1App:
// �йش����ʵ�֣������ Exercise_2_1.cpp
//

class CExercise_2_1App : public CWinApp
{
public:
	CExercise_2_1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExercise_2_1App theApp;