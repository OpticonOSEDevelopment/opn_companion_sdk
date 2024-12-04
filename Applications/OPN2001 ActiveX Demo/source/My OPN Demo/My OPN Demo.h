// My OPN Demo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


#define STATUS_OK                   0
#define COMMUNICATIONS_ERROR        -1 
#define BAD_PARAM                   -2
#define SETUP_ERROR                 -3
#define INVALID_COMMAND_NUMBER      -4
#define COMMAND_LRC_ERROR           -7
#define RECEIVED_CHARACTER_ERROR    -8
#define GENERAL_ERROR               -9
#define FILE_NOT_FOUND              2
#define ACCESS_DENIED               5
#define NO_ERROR_ENCOUNTERED        6

#define PARAM_ON                    1


// CMyOPNDemoApp:
// See My OPN Demo.cpp for the implementation of this class
//

class CMyOPNDemoApp : public CWinApp
{
public:
	CMyOPNDemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMyOPNDemoApp theApp;