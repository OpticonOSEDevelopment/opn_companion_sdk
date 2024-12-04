// My OPN DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "My OPN Demo.h"
#include "My OPN DemoDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



    enum symbologie
    {
        Bookland = 0x16,
        Codabar = 0x02,
        Code_11 = 0x0c,
        Code_32 = 0x20,
        Code_128 = 0x03,
        Code_39 = 0x01,
        Code_39_Full_ASCII = 0x13,
        Code_93 = 0x07,
        Composite = 0x1d,
        Coupon = 0x17,
        D25 = 0x04,
        Data_Matrix = 0x1b,
        EAN_128 = 0x0f,
        EAN_13 = 0x0b,
        EAN_13_2 = 0x4b,
        EAN_13_5 = 0x8b,
        EAN_8 = 0x0a,
        EAN_8_2 = 0x4a,
        EAN_8_5 = 0x8a,
        IATA = 0x05,
        ISBT_128 = 0x19,
        ISBT_128_concatenated = 0x21,
        ITF = 0x06,
        Macro_PDF = 0x28,
        MSI = 0x0E,
        PDF_417 = 0x11,
        Postbar_Canada = 0x26,
        Postnet_US = 0x1e,
        Postal_Australia = 0x23,
        Postal_Japan = 0x22,
        Postal_UK = 0x27,
        QR_code = 0x1c,
        RSS_limited = 0x31,
        RSS_14 = 0x30,
        RSS_Expanded = 0x32,
        Signature = 0x24,
        Trioptic_Code_39 = 0x15,
        UPCA = 0x08,
        UPCA_2 = 0x48,
        UPCA_5 = 0x88,
        UPCE = 0x09,
        UPCE_2 = 0x49,
        UPCE_5 = 0x89,
        UPCE1 = 0x10,
        UPCE1_2 = 0x50,
        UPCE1_5 = 0x90
    };

	const SBCD_DEFS bcodedefs[] = 
	{
        L"Bookland",	Bookland,
        L"Codabar",		Codabar,
        L"Code-11",		Code_11,
		L"Code-32",		Code_32,
        L"Code-128",	Code_128,
		L"Code-39",		Code_39,
        L"Code-39 full ASCII", Code_39_Full_ASCII,
        L"Code-93",		Code_93,
        L"Composite",	Composite,
        L"Coupon",		Coupon,
        L"D 2 of 5",	D25,
        L"Data Matrix", Data_Matrix,
        L"EAN-128",		EAN_128,
        L"EAN-13",		EAN_13,
        L"EAN-13 + 2",	EAN_13_2,
        L"EAN-13 + 5",	EAN_13_5,
        L"EAN-8",		EAN_8,
        L"EAN-8 + 2",	EAN_8_2,
        L"EAN-8 + 5",	EAN_8_5,
        L"IATA",		IATA,
        L"ISBT-128",	ISBT_128,
        L"ISBT-128 concatenated", ISBT_128_concatenated,
        L"ITF",			ITF,
		L"Macro PDF",	Macro_PDF,
        L"MSI",			MSI,
        L"PDF-417",		PDF_417,
        L"Postbar (Canada)", Postbar_Canada,
        L"Postnet (US)",Postnet_US,
        L"Postal (Australia)",	Postal_Australia,
        L"Postal (Japan)",	Postal_Japan,
        L"Postal (UK)",	Postal_UK,
        L"QR-code",		QR_code,
        L"RSS-limited",	RSS_limited,
        L"RSS-14",		RSS_14,
        L"RSS-expanded",RSS_Expanded,
        L"Signature",	Signature,
        L"Tri-Optic",	Trioptic_Code_39,
        L"UPC-A",		UPCA,
        L"UPC-A + 2",	UPCA_2,
        L"UPC-A + 5",	UPCA_5,
        L"UPC-E",		UPCE,
        L"UPC-E + 2",	UPCE_2,
        L"UPC-E + 5",	UPCE_5,
        L"UPC-E1",		UPCE1,
        L"UPC-E1 + 2",	UPCE1_2,
        L"UPC-E1 + 5",	UPCE1_5
	};
#define MAX_BCD		( sizeof(bcodedefs) / sizeof(SBCD_DEFS))




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyOPNDemoDlg dialog




IMPLEMENT_DYNAMIC(CMyOPNDemoDlg, CDialog);

CMyOPNDemoDlg::CMyOPNDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyOPNDemoDlg::IDD, pParent)
    , SaveToFilePath(_T(""))
    , COMPort(0)
    , SelectedCOMPort(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMyOPNDemoDlg::~CMyOPNDemoDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMyOPNDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_ID, DevID);
    DDX_Control(pDX, IDC_OS, SoftVer);
    DDX_Control(pDX, IDC_BARCODE_DATA, BarcodeData);
    DDX_Control(pDX, IDC_SAVE, SaveToFile);
    DDX_Control(pDX, IDC_PORTS, ComboPorts);
    DDX_Control(pDX, IDC_DLL, DLLVersion);
    DDX_Control(pDX, IDC_BN_OPEN_COMPORT, OpenCOMPort);
    DDX_Control(pDX, IDC_BN_CLOSE_COMPORT, CloseCOMPort);
    DDX_Control(pDX, IDC_AUTO, Auto);
    DDX_Control(pDX, IDC_OPNCTL1, OPNControl);
}

BEGIN_MESSAGE_MAP(CMyOPNDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BN_GET_TIME, &CMyOPNDemoDlg::OnBnClickedBnGetTime)
    ON_BN_CLICKED(IDC_BN_SET_TIME, &CMyOPNDemoDlg::OnBnClickedBnSetTime)
    ON_BN_CLICKED(IDC_BN_GET_BARCODE, &CMyOPNDemoDlg::OnBnClickedBnGetBarcode)
    ON_BN_CLICKED(IDC_BN_CLEAR_BARCODE, &CMyOPNDemoDlg::OnBnClickedBnClearBarcode)
    ON_BN_CLICKED(IDC_BN_PARAMETERS, &CMyOPNDemoDlg::OnBnClickedBnParameters)
    ON_BN_CLICKED(IDCANCEL, &CMyOPNDemoDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BN_OPEN_COMPORT, &CMyOPNDemoDlg::OnBnClickedBnOpenComport)
    ON_BN_CLICKED(IDC_BN_CLOSE_COMPORT, &CMyOPNDemoDlg::OnBnClickedBnCloseComport)
    ON_CBN_SELCHANGE(IDC_PORTS, &CMyOPNDemoDlg::OnCbnSelchangePorts)
    ON_BN_CLICKED(IDC_BN_INFORMATION, &CMyOPNDemoDlg::OnBnClickedBnInformation)
    ON_BN_CLICKED(IDC_BN_ABOUT, &CMyOPNDemoDlg::OnBnClickedBnAbout)
    ON_BN_CLICKED(IDC_AUTO, &CMyOPNDemoDlg::OnBnClickedAuto)
    ON_BN_CLICKED(IDCLOSE, &CMyOPNDemoDlg::OnBnClickedClose)
END_MESSAGE_MAP()


// CMyOPNDemoDlg message handlers

BOOL CMyOPNDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon



	// TODO: Add extra initialization here



    //initialize path and filename to save data to
    WCHAR szModulePath[1024 + 1];
	GetModuleFileName( AfxGetInstanceHandle(), szModulePath, 1024 );
	PathRemoveFileSpec( szModulePath );

	SaveToFilePath = szModulePath;
	SaveToFilePath += L"\\Barcodes.txt";

    //initialize DLL version    
    signed char DLLVer[16];
    CString strDLLVer;

    OPNControl.getDLLVersion(DLLVer, 16);
    strDLLVer.Format( _T("%S"), DLLVer );
    DLLVersion.SetWindowText(strDLLVer);

    //OPN Control should not be initialized here; should be initialized when the COM port is chosen and opened
    //So!  Let's do that.  Get the available ports
    CSerialEnum::GetSerialPorts(PortList);
    PortList.sort();
    PortList.unique();

    //Now fill the combobox
	ComboPorts.ResetContent(); // Clear the list in the combobox;
	CString strPort;
	int x;
	for (PortListIter = PortList.begin(), x = 0; PortListIter != PortList.end(); PortListIter++, x++ )
	{
		strPort.Format(_T("COM%d"), *PortListIter );
		ComboPorts.AddString( strPort );
		ComboPorts.SetItemData( x, *PortListIter );
	}
	
    ComboPorts.SetCurSel( 0 );
	OnCbnSelchangePorts(); //set the SelectedCOMPort value

    ComboPorts.EnableWindow();
    OpenCOMPort.EnableWindow();
    CloseCOMPort.EnableWindow(FALSE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyOPNDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyOPNDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyOPNDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CMyOPNDemoDlg::OnClose()
{
	if (CanExit())
    {
		CDialog::OnClose();
	    EndDialog( IDOK );
    }
}

void CMyOPNDemoDlg::OnCancel()
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CMyOPNDemoDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CMyOPNDemoDlg::OnTtnGetDispInfoCustom1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTTDISPINFO pNMTTDI = reinterpret_cast<LPNMTTDISPINFO>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}



void CMyOPNDemoDlg::OnBnClickedBnGetTime()
{
	BYTE buf[10];
	CString strTemp;
	signed long lRet;

    OPNControl.getTimeCmd(buf, &lRet);
	if (lRet == STATUS_OK)
	{
		strTemp.Format( L"%d:%02d:%02d \r\n%d/%0d/%02d", buf[ 2 ],  buf[ 1 ], buf[ 0 ], buf[ 4 ], buf[ 3 ], buf[ 5 ]);
		::MessageBox( m_hWnd, strTemp, L"Information", MB_OK | MB_ICONINFORMATION );
	}
	else
	{
		ShowErrorMessage( lRet );
	}
}

void CMyOPNDemoDlg::OnBnClickedBnSetTime()
{
	BYTE buf[10];	
	SYSTEMTIME sysTime;
	signed long lRet;

	GetLocalTime(&sysTime);

	buf[0] = static_cast<BYTE>(sysTime.wSecond);	    // seconds
	buf[1] = static_cast<BYTE>(sysTime.wMinute);	    // minutes
	buf[2] = static_cast<BYTE>(sysTime.wHour);		    // hours

	buf[3] = static_cast<BYTE>(sysTime.wDay);		    // day
	buf[4] = static_cast<BYTE>(sysTime.wMonth);	        // Month
	buf[5] = static_cast<BYTE>(sysTime.wYear % 100);    // year

    OPNControl.setTimeCmd(buf, &lRet);
	if (lRet == STATUS_OK)
	{
		::MessageBox( m_hWnd, L"Time is set", L"Information", MB_OK | MB_ICONINFORMATION );
	}
	else
	{
		ShowErrorMessage(lRet);
	}
}

void CMyOPNDemoDlg::OnBnClickedBnGetBarcode()
{
	LONG lAsciiMode, lRTC, lNumCodes, lLength;
    signed long lRet;
	signed char szBarcode[ 256 + 1 ];
	INT len;
	CString strTemp;
	
	OPNControl.readData(&lNumCodes, &lRet);
	if (lRet == S_OK)
	{
        if (lNumCodes != 0)
        {
		    // Get packet type (ASCII/Binary)
		    OPNControl.getASCIIMode(&lAsciiMode, &lRet);
            if (lRet != S_OK)
            {
                ShowErrorMessage(lRet);
                return;
            }

		    // Get TimeStamp setting (on/off)
		    OPNControl.getRTCMode(&lRTC, &lRet);
            if (lRet != S_OK)
            {
                ShowErrorMessage(lRet);
                return;
            }

		    // lRet contains the number of barcodes in the OPN-2001
		    LONG lTotalBarcodes = lNumCodes;

		    BarcodeData.ResetContent();
		    strTemp.Format(L"Read %ld Barcodes", lTotalBarcodes );
		    BarcodeData.AddString(strTemp);

		    HANDLE hFile = INVALID_HANDLE_VALUE;
            if (SaveToFile.GetCheck())
		    {
			    hFile = CreateFile( SaveToFilePath,		// path + filename 
					    GENERIC_READ | GENERIC_WRITE,	// open for reading and writing
					    0,								// do not share 
					    NULL,							// no security 
					    OPEN_ALWAYS,					// Open the file create new when not existing
					    FILE_ATTRIBUTE_NORMAL,			// normal file 
					    NULL);							// no attr. template 
		    }
		    if (hFile != INVALID_HANDLE_VALUE)
            {
			    SetFilePointer( hFile, 0, NULL, FILE_END); // set file pointer to end for appending
            }

		    for (LONG lCount = 0; lCount < lTotalBarcodes; lCount++)
		    {
			    //lRet = csp2GetPacket( szBarcode, lCount, sizeof( szBarcode ));
                lLength = static_cast<LONG>(sizeof(szBarcode));
                OPNControl.getBarcode(szBarcode, lCount, &lLength, &lRet);
			    if (lRet == S_OK)
			    {
				    ConvertBarcode2String(reinterpret_cast<CHAR*>(szBarcode), strTemp, lAsciiMode, lRTC );
				    BarcodeData.AddString( strTemp );
				    if (hFile != INVALID_HANDLE_VALUE)
				    {
					    DWORD dwWr;
					    len = sprintf_s(reinterpret_cast<CHAR*>(szBarcode), sizeof( szBarcode ) -1, "%S\r\n", strTemp );
					    WriteFile( hFile, szBarcode, len, &dwWr, NULL );
				    }
			    }
                else
                {
                    ShowErrorMessage(lRet);
                    if (hFile != INVALID_HANDLE_VALUE)
                    {
                        CloseHandle(hFile);
                    }
                    return;
                }
		    }
		    if (hFile != INVALID_HANDLE_VALUE)
            {
			    CloseHandle( hFile );
            }
        }
        else
        {
            BarcodeData.ResetContent();
		    BarcodeData.AddString( L"No barcodes available" );
        }
	}
    else
    {
        ShowErrorMessage(lRet);
    }
}

void CMyOPNDemoDlg::OnBnClickedBnClearBarcode()
{
	signed long lRet;

    lRet = ::MessageBox(m_hWnd, _T("This will erase every collected barcode on the device.  Are you sure you want to do this?"), _T("Warning"), MB_YESNO | MB_ICONWARNING);

    if (lRet == IDOK)
    {
	    OPNControl.clearDataCmd(&lRet);
	    if (lRet != STATUS_OK)
	    {
		    ShowErrorMessage(lRet);
	    }
    }
}

void CMyOPNDemoDlg::OnBnClickedBnParameters()
{
    signed long lRet;

	if (OpenCOMPort.IsWindowEnabled())
	{
		::MessageBox(m_hWnd, _T("Please establish a connection to an OPN first!"), _T("Error"), MB_OK | MB_ICONERROR);
		return; 
	}

    OPNControl.interrogateCmd(&lRet);
    if (lRet == S_OK)
    {
        DlgParams.SetControlObject(&OPNControl);
	    DlgParams.DoModal();
    }
    else
    {
        ShowErrorMessage(lRet);
    }
}


void CMyOPNDemoDlg::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here
    OnCancel();
}

void CMyOPNDemoDlg::OnBnClickedBnOpenComport()
{
    signed long lRet;

    COMPort = SelectedCOMPort;

    OPNControl.init(COMPort, &lRet);
    if (lRet != STATUS_OK)
	{
		ShowErrorMessage(lRet);
		return;
	}
	OpenCOMPort.EnableWindow(FALSE);
	ComboPorts.EnableWindow(FALSE);
    CloseCOMPort.EnableWindow();

/*
	m_bAutoNotClicked = TRUE;
	OnBnClickedCheckAuto();
	m_bAutoNotClicked = FALSE;
*/
}

void CMyOPNDemoDlg::OnBnClickedBnCloseComport()
{
     signed long lRet;

    OPNControl.cleanUp(&lRet);
    if (lRet != S_OK)
    {
        ShowErrorMessage(lRet);
        return;
    }
	OpenCOMPort.EnableWindow();
	ComboPorts.EnableWindow();
    CloseCOMPort.EnableWindow(FALSE);
	if(Auto.GetCheck() )
	{
		Auto.SetCheck(FALSE);
		StopAutomaticDownload();
		CButton* pBtn;
		pBtn = (CButton*)GetDlgItem( IDC_BN_INFORMATION );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_GET_TIME );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_SET_TIME );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_GET_BARCODE );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_CLEAR_BARCODE );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_PARAMETERS );
		pBtn->EnableWindow();
	}
	
/*	m_bAutoNotClicked = TRUE;
	OnBnClickedCheckAuto();
	// disable automatic download mode
	StopAutomaticDownload();
	m_bAutoNotClicked = FALSE; */
}

void CMyOPNDemoDlg::ShowErrorMessage(signed long ErrorCode)
{
   	CString strMessage;

	switch (ErrorCode)
	{
	case STATUS_OK:
		strMessage = L"Status OK";
		break;
	case COMMUNICATIONS_ERROR:
		strMessage = L"Communication error!";
		break;
	case BAD_PARAM:       
		strMessage = L"Bad parameter!";
		break;
	case SETUP_ERROR:
		strMessage = L"Setup error!";
		break;
	case INVALID_COMMAND_NUMBER:
		strMessage = L"Invalid command number!";
		break;
	case COMMAND_LRC_ERROR:
		strMessage = L"Checksum error!";
		break;
	case RECEIVED_CHARACTER_ERROR:
		strMessage = L"Wrong character received!";
		break;
	case GENERAL_ERROR:
		strMessage = L"General error!";
		break;
	case FILE_NOT_FOUND:
		strMessage = L"File not found!";
		break;
	case ACCESS_DENIED:
		strMessage = L"Access denied!";
		break;
	default:
		strMessage = L"Unknow error!!!";
		break;
	}
	MessageBox( strMessage, L"Error", MB_OK | MB_ICONERROR );
}

void CMyOPNDemoDlg::ConvertBarcode2String(CHAR* szBarcode, CString& strTemp, LONG lAsciiMode, LONG lRTC)
{
    int length;
	int nBcdLength;
	int nBarcodeType;
	signed char szTimeStamp[ 30 + 1]	= {0};
    signed long lRet;

	length = szBarcode[ 0 ];
	nBarcodeType = (long)(szBarcode[ 1 ] & 0x000000FF);
	// Clear the ouput string;
	strTemp.Empty();

	if ((length > 0) && (lAsciiMode == PARAM_ON))
	{
		nBcdLength = length + 1 - ((lRTC == PARAM_ON)?6:2);
		
		// Store the barcode
		strTemp.Format( L"%*.*S,", nBcdLength, nBcdLength, szBarcode + 2 );

		// Append the barcode type
		int nIndex;
		for( nIndex = 0; nIndex < MAX_BCD; nIndex++ )
		{
			if( bcodedefs[ nIndex ].lSymbol == (long) nBarcodeType )
			{
				strTemp.AppendFormat( L"%s", bcodedefs[ nIndex ].szSymbolName );
				break;
			}
		}
		if( nIndex == MAX_BCD )
			strTemp.Append( L"Unknown barcode" );

		// Append timestamp if available
		if (lRTC == PARAM_ON)
		{
			OPNControl.timeStamp2String(szTimeStamp, static_cast<LONG>(sizeof(szTimeStamp)), reinterpret_cast<BYTE*>(szBarcode + (length - 3)), &lRet);
            if (lRet != S_OK)
            {
                ShowErrorMessage(lRet);
                return;
            }

			strTemp.AppendFormat( L",%S", szTimeStamp );
		}
	}
	else
	{
		// binary mode 
		// Not supported on OPN-2001
	}
}

void CMyOPNDemoDlg::OnCbnSelchangePorts()
{
	int Selected = ComboPorts.GetCurSel();

	if (Selected == -1)
    {
		return;
    }

	SelectedCOMPort = static_cast<LONG>(ComboPorts.GetItemData(Selected));
}

void CMyOPNDemoDlg::OnBnClickedBnInformation()
{
    signed long lRet;
    LONG Length = 0;
	signed char SoftwareVersion[ 9 + 1 ];
	signed char DeviceID[ 9 + 1 ];
	CString strTemp;
	
	OPNControl.interrogateCmd(&lRet);
	if (lRet != STATUS_OK)
	{
		ShowErrorMessage( lRet );
		return;
	}

    Length = 8;
    OPNControl.getDeviceID(DeviceID, &Length, &lRet);
    if (lRet != STATUS_OK)
    {
        ShowErrorMessage(lRet);
        return;
    }
	strTemp.Format( _T("%02X%02X%02X%02X%02X%02X%02X%02X"), DeviceID[ 0 ] & 0xFF, 
															DeviceID[ 1 ] & 0xFF,
															DeviceID[ 2 ] & 0xFF,
															DeviceID[ 3 ] & 0xFF,
															DeviceID[ 4 ] & 0xFF,
															DeviceID[ 5 ] & 0xFF,
															DeviceID[ 6 ] & 0xFF,
															DeviceID[ 7 ] & 0xFF);
	DevID.SetWindowText( strTemp );

	// szDeviceID need now to be converted to a real number
	
    //csp2GetSwVersion( szSwVersion, 9 );
    Length = 8;
    OPNControl.getSoftwareVersion(SoftwareVersion, &Length, &lRet);
    if (lRet != STATUS_OK)
    {
        ShowErrorMessage(lRet);
        return;
    }
	strTemp.Format(_T("%S"), SoftwareVersion );
	SoftVer.SetWindowText( strTemp );
}

void CMyOPNDemoDlg::OnBnClickedBnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CMyOPNDemoDlg::OnBnClickedAuto()
{
	CButton* pBtn;
	if( Auto.GetCheck() )
	{
		// enable automatic download mode
		if( !StartAutomaticDownload())
		{
			Auto.SetCheck( FALSE );
		}
		else
		{
			// disable the other button options
			pBtn = (CButton*)GetDlgItem( IDC_BN_INFORMATION );
			pBtn->EnableWindow( FALSE );
			pBtn = (CButton*)GetDlgItem( IDC_BN_GET_TIME );
			pBtn->EnableWindow( FALSE );
			pBtn = (CButton*)GetDlgItem( IDC_BN_SET_TIME );
			pBtn->EnableWindow( FALSE );
			pBtn = (CButton*)GetDlgItem( IDC_BN_GET_BARCODE );
			pBtn->EnableWindow( FALSE );
			pBtn = (CButton*)GetDlgItem( IDC_BN_CLEAR_BARCODE );
			pBtn->EnableWindow( FALSE );
			pBtn = (CButton*)GetDlgItem( IDC_BN_PARAMETERS );
			pBtn->EnableWindow( FALSE );
		}
	}
	else
	{
		// disable automatic download mode
		StopAutomaticDownload();
		// Enable the other button options
		pBtn = (CButton*)GetDlgItem( IDC_BN_INFORMATION );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_GET_TIME );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_SET_TIME );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_GET_BARCODE );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_CLEAR_BARCODE );
		pBtn->EnableWindow();
		pBtn = (CButton*)GetDlgItem( IDC_BN_PARAMETERS );
		pBtn->EnableWindow();
	}
}


BOOL CMyOPNDemoDlg::StartAutomaticDownload(void)
{
	signed long lRet;
    BOOL Success = FALSE;

    OPNControl.startPolling(&lRet);
    if (lRet == STATUS_OK)
    {
        Success = TRUE;
    }
    else
    {
        ShowErrorMessage(lRet);
    }

	return Success;
}


BOOL CMyOPNDemoDlg::StopAutomaticDownload(void)
{
	signed long lRet;
    BOOL Success = FALSE;

    OPNControl.stopPolling(&lRet);
    if (lRet == STATUS_OK)
    {
        Success = TRUE;
    }
    else
    {
        ShowErrorMessage(lRet);
    }

	return Success;
}
void CMyOPNDemoDlg::OnBnClickedClose()
{
    // TODO: Add your control notification handler code here
    OnClose();
}
BEGIN_EVENTSINK_MAP(CMyOPNDemoDlg, CDialog)
    ON_EVENT(CMyOPNDemoDlg, IDC_OPNCTL1, 1, CMyOPNDemoDlg::handleCallBackOpnctl1, VTS_NONE)
END_EVENTSINK_MAP()

void CMyOPNDemoDlg::handleCallBackOpnctl1()
{
	long lAsciiMode, lRTC, lNumCodes, lLength;
    signed long lRet;
	signed char szBarcode[ 256 + 1 ];
	signed char szSwVersion[ 9 + 1 ];
	signed char szDeviceID[ 9 + 1 ];
	int len;
	CString strTemp;
	TRACE(L"handleCallBackOpnctl1() \n");
	
    OPNControl.readData(&lNumCodes, &lRet);
	if (lRet == S_OK)
	{
		// Get packet type (ASCII/Binary)
		OPNControl.getASCIIMode(&lAsciiMode, &lRet);
        if (lRet != S_OK)
        {
            ShowErrorMessage(lRet);
            return;
        }

		// Get TimeStamp setting (on/off)
		OPNControl.getRTCMode(&lRTC, &lRet);
        if (lRet != S_OK)
        {
            ShowErrorMessage(lRet);
            return;
        }

		//csp2GetDeviceId( szDeviceID, 9); 
        lLength = 8;
        OPNControl.getDeviceID(szDeviceID, &lLength, &lRet);
        if (lRet != S_OK)
        {
            ShowErrorMessage(lRet);
            return;
        }
		strTemp.Format( _T("%02X%02X%02X%02X%02X%02X%02X%02X"), szDeviceID[ 0 ], 
															szDeviceID[ 1 ],
															szDeviceID[ 2 ],
															szDeviceID[ 3 ],
															szDeviceID[ 4 ],
															szDeviceID[ 5 ],
															szDeviceID[ 6 ],
															szDeviceID[ 7 ]);
		DevID.SetWindowText( strTemp );

		//csp2GetSwVersion( szSwVersion, 9 );
        lLength = 8;
        OPNControl.getSoftwareVersion(szSwVersion, &lLength, &lRet);
        if (lRet != S_OK)
        {
            ShowErrorMessage(lRet);
            return;
        }
		strTemp.Format(_T("%S"), szSwVersion );
		SoftVer.SetWindowText( strTemp );

		// lRet contains the number of barcodes in the OPN-2001
		long lTotalBarcodes = lNumCodes;

		BarcodeData.ResetContent();
		strTemp.Format( L"Read %ld Barcodes", lTotalBarcodes );
		BarcodeData.AddString( strTemp );
		HANDLE hFile = INVALID_HANDLE_VALUE;
        if( SaveToFile.GetCheck() )
		{
			hFile = CreateFile( SaveToFilePath,		// path + filename 
					GENERIC_READ | GENERIC_WRITE,	// open for reading and writing
					0,								// do not share 
					NULL,							// no security 
					OPEN_ALWAYS,					// Open the file create new when not existing
					FILE_ATTRIBUTE_NORMAL,			// normal file 
					NULL);							// no attr. template 
		}
		if( hFile != INVALID_HANDLE_VALUE )
			SetFilePointer( hFile, 0, NULL, FILE_END); // set file pointer to end for appending

		for( long lCount = 0L; lCount < lTotalBarcodes; lCount++ )
		{
			//lRet = csp2GetPacket( szBarcode, lCount, sizeof( szBarcode ));
            lLength = static_cast<LONG>(sizeof(szBarcode));
            OPNControl.getBarcode(szBarcode, lCount, &lLength, &lRet);
			if (lRet == S_OK)
			{
				ConvertBarcode2String(reinterpret_cast<CHAR*>(szBarcode), strTemp, lAsciiMode, lRTC);
				BarcodeData.AddString( strTemp );
				if( hFile != INVALID_HANDLE_VALUE )
				{
					DWORD dwWr;
					len = sprintf_s( reinterpret_cast<CHAR*>(szBarcode), sizeof( szBarcode ) -1, "%S\r\n", strTemp );
					WriteFile( hFile, szBarcode, len, &dwWr, NULL );
				}
			}
            else
            {
                ShowErrorMessage(lRet);
                if (hFile != INVALID_HANDLE_VALUE)
                {
                    CloseHandle(hFile);
                }
                return;
            }
		}
		if( hFile != INVALID_HANDLE_VALUE )
			CloseHandle( hFile );

		// remove the barcode data from the OPN
		OPNControl.clearDataCmd(&lRet);
        if (lRet != S_OK)
        {
            ShowErrorMessage(lRet);
            return;
        }
	}
	else
	{
        ShowErrorMessage(lRet);
		// Do not show error message possibly the OPN is unplugged
		TRACE( L"csp2ReadData failed!!! %ld \n", lRet);
        return;
	}
}
