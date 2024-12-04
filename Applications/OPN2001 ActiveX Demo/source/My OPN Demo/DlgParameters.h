#pragma once
#include ".\gridctrl\gridctrl.h"
#include ".\gridctrl\gridcellcombo.h"
#include ".\gridctrl\gridcellnumeric.h"
#include "ProgressWnd.h"
#include "opnctl1.h"

// CDlgParameters dialog

class CDlgParameters : public CDialog
{
	DECLARE_DYNAMIC(CDlgParameters)

public:
	CDlgParameters(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgParameters();

// Dialog Data
	enum { IDD = IDD_DLG_PARAMETERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void ShowErrorMessage( long lErrorCode );
    void FillListControl( void );
    afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
    CGridCtrl GridParam;
    COpnctl1* OPNControl;
    CProgressWnd *ProgWnd;
	CStringArray ParamStringOptions[ 11 ];
public:
    afx_msg void OnBnClickedBnDefault();
    afx_msg void OnBnClickedBnSettings();
    afx_msg void OnClose();
    void SetControlObject(COpnctl1* opncon);
};
