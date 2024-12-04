// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "My OPN Demo.h"
#include "DlgProxy.h"
#include "My OPN DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyOPNDemoDlgAutoProxy

IMPLEMENT_DYNCREATE(CMyOPNDemoDlgAutoProxy, CCmdTarget)

CMyOPNDemoDlgAutoProxy::CMyOPNDemoDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMyOPNDemoDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMyOPNDemoDlg)))
		{
			m_pDialog = reinterpret_cast<CMyOPNDemoDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMyOPNDemoDlgAutoProxy::~CMyOPNDemoDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMyOPNDemoDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMyOPNDemoDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMyOPNDemoDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IMyOPNDemo to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {1C37E8C7-EA05-4EEC-8BAA-1E4315684020}
static const IID IID_IMyOPNDemo =
{ 0x1C37E8C7, 0xEA05, 0x4EEC, { 0x8B, 0xAA, 0x1E, 0x43, 0x15, 0x68, 0x40, 0x20 } };

BEGIN_INTERFACE_MAP(CMyOPNDemoDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMyOPNDemoDlgAutoProxy, IID_IMyOPNDemo, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {E3B1C89C-34FC-4067-BF3C-6BEE46581C7C}
IMPLEMENT_OLECREATE2(CMyOPNDemoDlgAutoProxy, "MyOPNDemo.Application", 0xe3b1c89c, 0x34fc, 0x4067, 0xbf, 0x3c, 0x6b, 0xee, 0x46, 0x58, 0x1c, 0x7c)


// CMyOPNDemoDlgAutoProxy message handlers
