
// PaintMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PaintMFC.h"
#include "PaintMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CPaintMFCDlg dialog



CPaintMFCDlg::CPaintMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAINTMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaintMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPaintMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

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
		InnerOnPaint();

// CPaintMFCDlg message handlers

BOOL CPaintMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPaintMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPaintMFCDlg::OnPaint()
{
		CDialogEx::OnPaint();		
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaintMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Our Code:


void CPaintMFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((isPressed) && (ShapePressed == false) && (shapeMovingMode == false))
	{
		CClientDC dc(this);
		//CBrush myBrush,*oldBrush;
		//myBrush.CreateSolidBrush(curColor);
		//oldBrush=dc.SelectObject( &myBrush );  
		CPen myPen1(PS_SOLID, m_PenWidth, curColor);
		CPen* oldPen;
		oldPen = dc.SelectObject(&myPen1);
		switch (ChosenShape)
		{
		case RECTANGLE:
			dc.SetROP2(R2_NOTXORPEN);
			//dc.SelectStockObject(NULL_BRUSH);
			dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
			endP = point;
			dc.Rectangle(startP.x, startP.y, endP.x, endP.y);
			break;
		case ELLIPSE:
			dc.SetROP2(R2_NOTXORPEN);
			//dc.SelectStockObject(NULL_BRUSH);
			dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
			endP = point;
			dc.Ellipse(startP.x, startP.y, endP.x, endP.y);
			break;
		}
		dc.SelectObject(oldPen);
		dc.SetROP2(R2_COPYPEN);
	}
	else if ((isPressed) && (shapeMovingMode) && (ShapePressed))
	{
		RECT r;
		int x, y;
		int xx, yy;
		xx = TLX.x, yy = TLX.y;
		TLX = point;
		x = (TLX.x - xx);
		y = (TLX.y - yy);
		_shapes[chosenFigure]->setx1(_shapes[chosenFigure]->getx1() + x);
		_shapes[chosenFigure]->sety1(_shapes[chosenFigure]->gety1() + y);
		_shapes[chosenFigure]->setx2(_shapes[chosenFigure]->getx2() + x);
		_shapes[chosenFigure]->sety2(_shapes[chosenFigure]->gety2() + y);
		r.left = min(sh[chosenFigure]->getx1(), sh[chosenFigure]->getx2()) - 50;
		r.right = max(sh[chosenFigure]->getx1(), sh[chosenFigure]->getx2()) + 50;
		r.top = min(sh[chosenFigure]->gety1(), sh[chosenFigure]->gety2()) - 50;
		r.bottom = max(sh[chosenFigure]->gety1(), sh[chosenFigure]->gety2()) + 50;
		InvalidateRect(&r);


	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}
