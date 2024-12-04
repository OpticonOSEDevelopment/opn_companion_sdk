// DlgParameters.cpp : implementation file
//

#include "stdafx.h"
#include "My OPN Demo.h"
#include "DlgParameters.h"


typedef struct 
{
	LPCWSTR szParameter;
	short	nTypeMin;	// if nTypeMin is 9999 then combobox or 9998 as special input (scratch pad)
	short	nTypeMax;	// if nTypeMin is 9999 then nTypeMax selects the combobox type	
	short	nOffset;	// Some comboboxes start with another value then zero the use the nOffset value
	BYTE	nParamNr;
}ParamOptions;

ParamOptions paramOptions [] = 
{
	L"Code-39",							9999,	0,	0,	31,
	L"UPC",								9999,	0,	0,	9,
	L"Code-128",						9999,	0,	0,	8,
	L"Code-39 Full ASCII",				9999,	0,	0,	54,
	L"UPC Supps",						9999,	2,	0,	53,
	L"Convert UPC-E to A",				9999,	0,	0,	41,
	L"Convert EAN-8 to EAN-13",			9999,	0,	0,	42,
	L"Convert EAN-8 to EAN-13 Type",	9999,	0,	0,	55,
	L"Send UPC-A Check Digit",			9999,	0,	0,	43,
	L"Send UPC-E Check Digit",			9999,	0,	0,	44,
	L"Code-39 Check Digit",				9999,	0,	0,	46,
	L"Xmit Code-39 Check Digit",		9999,	0,	0,	45,
	L"UPC-E Preamble",					9999,	3,	0,	37,
	L"UPC-A Preamble",					9999,	3,	0,	36,
	L"EAN-128",							9999,	0,	0,	52,
	L"Coupon Code",						9999,	0,	0,	56,
	L"I 2 of 5",						9999,	0,	0,	58,
	L"I 2of5 Check Digit",				9999,	4,	0,	65,
	L"Xmit I 2of5 Check Digit",			9999,	0,	0,	64,
	L"Convert ITF14 to EAN 13",			9999,	0,	0,	63,
	L"I 2of5 Length 1",					0,		30, 0,	59,
	L"I 2of5 Length 2",					0,		30,	0,	60,
	L"D 2of5",							9999,	0,	0,	57,
	L"D 2of5 Length 1",					0,		30,	0,	61,
	L"D 2of5 Length 2",					0,		30,	0,	62,
	L"UPC/EAN Security",				0,		3,	0,	47,
	L"UPC/EAN Supplemental Redundancy (No_supp_max)", 2, 20, 0,	48,
	L"Scanner On-Time",					10,		100,0,	17,
	L"Volume",							9999,	1,	0,	2,
	L"Comm awake time",					1,		6,	0,	32,
	L"Baudrate",						9999,	5,	3,	13,
	L"Baud Switch Delay",				0,		100,0,	29,
	L"Reset Baudrates",					9999,	0,	0,	28,
	L"Reject redundant barcode",		9999,	10,	0,	4,
	L"Host Connect Beep",				9999,	0,	0,	10,
	L"Host Complete Beep",				9999,	0,	0,	11,
	L"Low-battery indication",			9999,	6,	0,	7,
	L"Auto Clear",						9999,	0,	0,	15,
	L"Delete Enable",					9999,	7,	7,	33,
	L"Data Protection",					9999,	0,	0,	49,
	L"Memory full indication",			9999,	0,	0,	50,
	L"Memory Low Indication",			9999,	0,	0,	51,
	L"Max Barcode Length",				1,		30,	0,	34,
	L"Good decode LED on time",			9999,	8,	1,	30,
	L"Store RTC",						9999,	0,	0,	35,
	L"ASCII mode",						9999,	9,	0,	79,
	L"Beeper Toggle",					9999,	1,	0,	85,
	L"Beeper Auto On",					9999,	1,	0,	86,
//	L"Scratch Pad",						9998,	0,	0,	38
};

#define MAX_OPN_PARAMETERS ( sizeof(paramOptions) / sizeof(ParamOptions))



// CDlgParameters dialog

IMPLEMENT_DYNAMIC(CDlgParameters, CDialog)

CDlgParameters::CDlgParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParameters::IDD, pParent)
{
	// Enable disable string options
	ParamStringOptions[ 0 ].Add(L"0 - Disable");
	ParamStringOptions[ 0 ].Add(L"1 - Enable");

	// On off string options
	ParamStringOptions[ 1 ].Add( L"0 - Off");
	ParamStringOptions[ 1 ].Add( L"1 - On");

	// UPC Supps string options
	ParamStringOptions[ 2 ].Add( L"0 - No Supps");
	ParamStringOptions[ 2 ].Add( L"1 - Supps only");
	ParamStringOptions[ 2 ].Add( L"2 - Auto-D");

	// UPC-A and UPC-E preamble string options
	ParamStringOptions[ 3 ].Add( L"0 - None");
	ParamStringOptions[ 3 ].Add( L"1 - System char");
	ParamStringOptions[ 3 ].Add( L"2 - Sys char & country code");

	// I 2of5 Check Digit string options
	ParamStringOptions[ 4 ].Add( L"0 - Disabled");
	ParamStringOptions[ 4 ].Add( L"1 - USS check digit");
	ParamStringOptions[ 4 ].Add( L"2 - OPCC check digit");

	// Baudrate string options
	ParamStringOptions[ 5 ].Add( L"3 - 300");
	ParamStringOptions[ 5 ].Add( L"4 - 600");
	ParamStringOptions[ 5 ].Add( L"5 - 1200");
	ParamStringOptions[ 5 ].Add( L"6 - 2400");
	ParamStringOptions[ 5 ].Add( L"7 - 4800");
	ParamStringOptions[ 5 ].Add( L"8 - 9600");
	ParamStringOptions[ 5 ].Add( L"9 - 19200");

	// Low-Battery Indication string options
	ParamStringOptions[ 6 ].Add( L"0 - No indication / No operation");
	ParamStringOptions[ 6 ].Add( L"1 - No Indication / Allow operation");
	ParamStringOptions[ 6 ].Add( L"2 - Indicate / No operation");
	ParamStringOptions[ 6 ].Add( L"3 - Indicate / Allow operation.");

	// Delete enable string options
	ParamStringOptions[ 7 ].Add( L"0 - All Disabled");
	ParamStringOptions[ 7 ].Add( L"1 - Clear All Enabled");
	ParamStringOptions[ 7 ].Add( L"2 - Delete Key Enabled");
	ParamStringOptions[ 7 ].Add( L"3 - Delete Key / Clear All Enabled");
	ParamStringOptions[ 7 ].Add( L"4 - Set Defaults Enabled");
	ParamStringOptions[ 7 ].Add( L"5 - Set Defaults / Clear All Enabled");
    ParamStringOptions[ 7 ].Add( L"6 - Set Defaults / Delete Key Enabled");
    ParamStringOptions[ 7 ].Add( L"7 - All Enabled");

	// Good Decode LED On Time string options
	ParamStringOptions[ 8 ].Add( L"1 - 250 ms");
	ParamStringOptions[ 8 ].Add( L"2 - 500 ms");
	ParamStringOptions[ 8 ].Add( L"3 - 750 ms");
	ParamStringOptions[ 8 ].Add( L"4 - 1000 ms");

	// ASCII mode string options
	ParamStringOptions[ 9 ].Add( L"0 - Like encrypted data");
	ParamStringOptions[ 9 ].Add( L"1 - As ASCII strings");

    ParamStringOptions[ 10 ].Add( L"0 - Disable");
    ParamStringOptions[ 10 ].Add( L"1 - Enable Mode 1");
    ParamStringOptions[ 10 ].Add( L"2 - Enable Mode 2");

    OPNControl = NULL;
    ProgWnd = NULL;
}

CDlgParameters::~CDlgParameters()
{
}

void CDlgParameters::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_GRID_PARAMETERS, GridParam);
}


BEGIN_MESSAGE_MAP(CDlgParameters, CDialog)
    ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID_PARAMETERS, OnGridEndEdit)
    ON_NOTIFY(GVN_SELCHANGED, IDC_GRID_PARAMETERS, OnGridEndSelChange)
    ON_BN_CLICKED(IDC_BN_DEFAULT, &CDlgParameters::OnBnClickedBnDefault)
    ON_BN_CLICKED(IDC_BN_SETTINGS, &CDlgParameters::OnBnClickedBnSettings)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgParameters message handlers

BOOL CDlgParameters::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GridParam.SetColumnCount( 2 );
	GridParam.SetRowCount( MAX_OPN_PARAMETERS );
	GridParam.SetFixedColumnCount();
	GridParam.GetClientRect( &rect );
	GridParam.SetColumnWidth( 0, ((rect.Width() / 5) *4)-14);
	GridParam.SetColumnWidth( 1, (rect.Width() / 5 )+18); 
	GridParam.SetFixedColumnSelection( FALSE );
	GridParam.SetFixedRowSelection( FALSE );
	GridParam.EnableTitleTips( FALSE );

	// Create a progress window
	if( ProgWnd == NULL )
		ProgWnd = new CProgressWnd( this, _T("Progress"), 0 );
	if( ProgWnd != NULL )
		ProgWnd->Hide();

	// Fill the list control
	FillListControl(); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgParameters::OnBnClickedBnDefault()
{
	LONG lRet;

	//lRet = csp2SetDefaults();
    OPNControl->setDefaultsCmd(&lRet);
	if( lRet != STATUS_OK )
	{
		ShowErrorMessage( lRet );
		return;
	}
	FillListControl();
}

void CDlgParameters::OnBnClickedBnSettings()
{
	LONG lRet;
	INT nPercentage;
	signed char szParam[ 2 ];   //NOTE: as opposed to getting parameter values, the first byte here, when sending parameters, is the parameter value
	CString strItem;

	ProgWnd->Show();
	for( int x = 0; x < MAX_OPN_PARAMETERS; x++ )
	{
		ProgWnd->SetText( paramOptions[ x ].szParameter );
		nPercentage = ((x + 1)*100) / MAX_OPN_PARAMETERS; 
		ProgWnd->SetPos( (int) nPercentage );

		if( paramOptions[ x ].nTypeMin == 9999 )
		{
			szParam[ 0 ] = 0;
			// combobox type
			for( int itemnr = 0; itemnr < ParamStringOptions[ paramOptions[ x ].nTypeMax ].GetCount(); itemnr++ )
			{
				CString strData = ParamStringOptions[ paramOptions[ x ].nTypeMax ].ElementAt( itemnr ) ;
				if( ParamStringOptions[ paramOptions[ x ].nTypeMax ].ElementAt( itemnr ).Compare( GridParam.GetCell( x, 1 )->GetText() ) == 0)
				{
					szParam[ 0 ] = itemnr + paramOptions[ x ].nOffset;
					break;
				}
			}
		}
		else if( paramOptions[ x ].nTypeMin == 9998 )
		{
			// special options, e.g. scratch pad
		}
		else
		{
			szParam[ 0 ] = _ttoi( GridParam.GetCell( x, 1)->GetText());
		}
		/* if( (lRet = csp2SetParam( paramOptions[ x ].nParamNr, szParam, 1L )) != STATUS_OK ) */
        OPNControl->setParamCmd(static_cast<LONG>(paramOptions[x].nParamNr), szParam, 1, &lRet);
        if (lRet != STATUS_OK)
        {
			ShowErrorMessage( lRet );
        }
	}
	ProgWnd->Hide();
}


void CDlgParameters::SetControlObject(COpnctl1 *opncon)
{
    if (opncon != NULL)
    {
        OPNControl = opncon;
    }
}


void CDlgParameters::ShowErrorMessage( long lErrorCode )
{
	CString strMessage;

	switch( lErrorCode )
	{
	case STATUS_OK:
		strMessage = _T("Status OK");
		break;
	case COMMUNICATIONS_ERROR:
		strMessage = _T("Communication error!");
		break;
	case BAD_PARAM:       
		strMessage = _T("Bad parameter!");
		break;
	case SETUP_ERROR:
		strMessage = _T("Setup error!");
		break;
	case INVALID_COMMAND_NUMBER:
		strMessage = _T("Invalid command number!");
		break;
	case COMMAND_LRC_ERROR:
		strMessage = _T("Checksum error!");
		break;
	case RECEIVED_CHARACTER_ERROR:
		strMessage = _T("Wrong character received!");
		break;
	case GENERAL_ERROR:
		strMessage = _T("General error!");
		break;
	case FILE_NOT_FOUND:
		strMessage = _T("File not found!");
		break;
	case ACCESS_DENIED:
		strMessage = _T("Access denied!");
		break;
	default:
		strMessage = _T("Unknown error!!!");
		break;
	}
    ::MessageBoxW(NULL, strMessage, _T("Error"), MB_OK | MB_ICONERROR );
}


void CDlgParameters::FillListControl( void )
{
	LONG lRet;
	INT nPercentage;
	signed char szParam[ 2 ];   //NOTE: the parameter is the first byte, the parameter value is the second byte
	CString strItem;

	ProgWnd->Show();
	for( int x = 0; x < MAX_OPN_PARAMETERS; x++ )
	{
		GridParam.SetItemText( x, 0, paramOptions[ x ].szParameter );
		ProgWnd->SetText( paramOptions[ x ].szParameter );
		nPercentage = ((x + 1)*100) / MAX_OPN_PARAMETERS; 
		ProgWnd->SetPos( (int) nPercentage );

		/* if( (lRet =  csp2GetParam( paramOptions[ x ].nParamNr, szParam, 1L )) != STATUS_OK ) */
        OPNControl->getParamCmd(static_cast<LONG>(paramOptions[x].nParamNr), szParam, 2, &lRet);
        if (lRet != STATUS_OK)
        {
			ShowErrorMessage( lRet );
        }

//		if( lRet == STATUS_OK )
//		{
//			strItem.Format(L"%d", szParam[ 0 ]);
//		}

		if( paramOptions[ x ].nTypeMin == 9999 )
		{
			szParam[ 1 ] -= (char)paramOptions[ x ].nOffset;
			// Combobox type 
			GridParam.SetCellType( x, 1, RUNTIME_CLASS(CGridCellCombo));

			if( szParam[ 1 ] < 0 || szParam[ 1 ] >= ParamStringOptions[ paramOptions[ x ].nTypeMax ].GetCount())
				szParam[ 1 ] = 0;

			GridParam.SetItemText( x, 1, ParamStringOptions[ paramOptions[ x ].nTypeMax ].ElementAt( szParam[ 1 ] ));
			CGridCellCombo *pCell = (CGridCellCombo*) GridParam.GetCell( x, 1 );
			pCell->SetOptions( ParamStringOptions[ paramOptions[ x ].nTypeMax ] );
			pCell->SetStyle( CBS_DROPDOWNLIST );
			
		}
		else if( paramOptions[ x ].nTypeMin == 9998 )
		{
			// Special option
			GridParam.SetItemState( x, 1, GridParam.GetItemState( x, 1) | GVIS_READONLY);
		}
		else
		{
			// Min max options
			GridParam.SetCellType( x, 1, RUNTIME_CLASS( CGridCellNumeric ));
			if( szParam[ 1 ] < (char)paramOptions[ x ].nTypeMin || szParam[ 1 ] > (char)paramOptions[ x ].nTypeMax )
				szParam[ 1 ] = (char)paramOptions[ x ].nTypeMin;

			strItem.Format( L"%d", (int)szParam[ 1 ] );
			GridParam.SetItemText( x, 1, strItem );
			CGridCellNumeric *pCell = (CGridCellNumeric*) GridParam.GetCell( x, 1 );
		}
	}
	GridParam.UpdateData();
	GridParam.Invalidate();
	ProgWnd->Hide();
}


void CDlgParameters::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nValue;
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	CGridCellNumeric *pCell = (CGridCellNumeric*)GridParam.GetCell( pItem->iRow, pItem->iColumn );
	nValue = _ttoi( pCell->GetText());

	if( paramOptions[ pItem->iRow ].nTypeMin == 9999 || paramOptions[ pItem->iRow ].nTypeMin == 9998 )
	{
		*pResult = 0;
	}
	else
	{
		if( nValue < paramOptions[ pItem->iRow ].nTypeMin || nValue > paramOptions[ pItem->iRow ].nTypeMax )
			*pResult = -1; // Wrong value
		else
			*pResult = 0; // OK
	}
}


void CDlgParameters::OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	if( pItem->iColumn == 1 && paramOptions[ pItem->iRow ].nTypeMin == 9998 )
	{
		if( paramOptions[ pItem->iRow ].nTypeMax == 0 )
		{
			// scratch pad option
			::MessageBox( NULL, L"Scratch pad", L"Information", MB_OK);
			return;
		}
	}
}


void CDlgParameters::OnClose()
{
	if( ProgWnd != NULL )
		delete ProgWnd;
	ProgWnd = NULL;
	CDialog::OnClose();
	EndDialog( IDOK );
}