// DlgProxy.h: header file
//

#pragma once

class CMyOPNDemoDlg;


// CMyOPNDemoDlgAutoProxy command target

class CMyOPNDemoDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMyOPNDemoDlgAutoProxy)

	CMyOPNDemoDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CMyOPNDemoDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CMyOPNDemoDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMyOPNDemoDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

