// My OPN DemoDlg.h : header file
//

#pragma once
//#include "opnctl1.h"
#include "afxwin.h"
#include "shlwapi.h"
#include <list>
#include "SerialEnum.h"
#include "dlgparameters.h"
#include "opnctl1.h"

using namespace std;


typedef struct 
{
	LPCWSTR szSymbolName;
	long	lSymbol;
} SBCD_DEFS;


class CMyOPNDemoDlgAutoProxy;


// CMyOPNDemoDlg dialog
class CMyOPNDemoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyOPNDemoDlg);
	friend class CMyOPNDemoDlgAutoProxy;

// Construction
public:
	CMyOPNDemoDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CMyOPNDemoDlg();

// Dialog Data
	enum { IDD = IDD_MYOPNDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CMyOPNDemoDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
    void ConvertBarcode2String(CHAR* szBarcode, CString& strTemp, LONG lAsciiMode, LONG lRTC);
    void ShowErrorMessage(signed long ErrorCode);
    BOOL StartAutomaticDownload(void);
    BOOL StopAutomaticDownload(void);
    afx_msg void OnBnClickedBnGetTime();
    afx_msg void OnBnClickedBnSetTime();
    afx_msg void OnBnClickedBnGetBarcode();
    afx_msg void OnBnClickedBnClearBarcode();
    afx_msg void OnBnClickedBnParameters();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedBnOpenComport();
    afx_msg void OnBnClickedBnCloseComport();
    afx_msg void OnBnClickedBnInformation();
    afx_msg void OnBnClickedBnAbout();
    afx_msg void OnBnClickedAuto();
    afx_msg void OnBnClickedSave();
    afx_msg void OnTtnGetDispInfoCustom1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCbnSelchangePorts();
private:
    CStatic DevID;
    CStatic SoftVer;
    CStatic DLLVersion;
    CListBox BarcodeData;
    CComboBox ComboPorts;
    CButton OpenCOMPort;
    CButton CloseCOMPort;
    CButton Auto;
    CButton SaveToFile;
    CDlgParameters DlgParams;

    CString SaveToFilePath;
    LONG COMPort;
    LONG SelectedCOMPort;
    list<int> PortList;
    list<int>::iterator PortListIter;
public:
    afx_msg void OnBnClickedClose();
    COpnctl1 OPNControl;
    DECLARE_EVENTSINK_MAP()
    void handleCallBackOpnctl1();
};
