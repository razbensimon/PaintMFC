
// PaintMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PaintMFC.h"
#include "PaintMFCDlg.h"
#include "afxdialogex.h"
#include "ShapesFactory.h"

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
	ON_BN_CLICKED(BTN_RECT2, &CPaintMFCDlg::OnBnClickedRectangle)
	ON_BN_CLICKED(BTN_ELLIPSE, &CPaintMFCDlg::OnBnClickedEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(BTN_ELLIPSE2, &CPaintMFCDlg::OnBnClickedTriangle)
END_MESSAGE_MAP()


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
		this->InnerOnPaint();
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPaintMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/* #### Our CODE: ### */

void CPaintMFCDlg::InnerOnPaint()
{
	_penColor = RGB(255, 0, 0);
	_penWidth = 5.0;

	CPaintDC context(this);
	for (int i = 0; i < _shapes.GetSize(); i++)
		_shapes[i]->draw(&context);
}


void CPaintMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// save start cursor point
	_endP = _startP = point;
	_isMousePressed = true;

	_currentShapeDraw = ShapesFactory::createShape(_chosenShapeType, point.x, point.y, point.x, point.y, _penWidth, _penColor);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPaintMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// save end cursor point
	_endP = point;
	_isMousePressed = false;

	// save the figure in data array

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPaintMFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!_isMousePressed)
		return;


	if (_drawMode == false)// && _shapeMovingMode == false)
	{
		CClientDC dc(this);
		CPen pen(PS_SOLID, _penWidth, _penColor);
		CPen* oldPen;
		oldPen = dc.SelectObject(&pen);

		dc.SetROP2(R2_NOTXORPEN);
		_currentShapeDraw->draw(&dc);

		_endP = point; // update to the new end point
		_currentShapeDraw->setX2(point.x);
		_currentShapeDraw->setY2(point.y);
		_currentShapeDraw->draw(&dc);
		
		dc.SelectObject(oldPen);
		dc.SetROP2(R2_COPYPEN);
	}
	/*else if ((_isMousePressed) && (_shapeMovingMode) && (_drawMode))
	{
		RECT r;
		int x, y;
		int xx, yy;
		xx = _TLX.x, yy = _TLX.y;
		_TLX = point;
		x = (_TLX.x - xx);
		y = (_TLX.y - yy);
		_shapes[chosenFigure]->setX1(_shapes[chosenFigure]->getX1() + x);
		_shapes[chosenFigure]->setY1(_shapes[chosenFigure]->getY1() + y);
		_shapes[chosenFigure]->setX2(_shapes[chosenFigure]->getX2() + x);
		_shapes[chosenFigure]->setY2(_shapes[chosenFigure]->getY2() + y);
		r.left = min(_shapes[chosenFigure]->getX1(), _shapes[chosenFigure]->getX2()) - 50;
		r.right = max(_shapes[chosenFigure]->getX1(), _shapes[chosenFigure]->getX2()) + 50;
		r.top = min(_shapes[chosenFigure]->getY1(), _shapes[chosenFigure]->getY2()) - 50;
		r.bottom = max(_shapes[chosenFigure]->getY1(), _shapes[chosenFigure]->getY2()) + 50;
		InvalidateRect(&r);
	}*/

	CDialogEx::OnMouseMove(nFlags, point);
}


void CPaintMFCDlg::OnBnClickedRectangle()
{
	_chosenShapeType = RECTANGLE;
	_isMousePressed = false;
	_drawMode = false;
	_shapeMovingMode = false;
}


void CPaintMFCDlg::OnBnClickedEllipse()
{
	_chosenShapeType = ELLIPSE;
	_isMousePressed = false;
	_drawMode = false;
	_shapeMovingMode = false;
}

void CPaintMFCDlg::OnBnClickedTriangle()
{
	_chosenShapeType = TRIANGLE;
	_isMousePressed = false;
	_drawMode = false;
	_shapeMovingMode = false;
}