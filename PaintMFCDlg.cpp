
// PaintMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PaintMFC.h"
#include "PaintMFCDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iomanip>

#include "ShapesFactory.h"
#include "json.hpp"
using json = nlohmann::json;

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
	DDX_Control(pDX, ID_BRDRCLR_CTRL, borderColorControl);
	DDX_Control(pDX, ID_BRDRWGHT_CTRL, borderWeightControl);
	DDX_Control(pDX, ID_FILLCLR_CTRL, fillColorControl);
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
	ON_BN_CLICKED(ID_BRDRCLR_CTRL, &CPaintMFCDlg::OnBnClickedBrdrclrCtrl)
	ON_CBN_SELCHANGE(ID_BRDRWGHT_CTRL, &CPaintMFCDlg::OnCbnSelchangeBrdrwghtCtrl)
	ON_BN_CLICKED(ID_FILLCLR_CTRL, &CPaintMFCDlg::OnBnClickedFillclrCtrl)
	ON_BN_CLICKED(SAVE_BTN, &CPaintMFCDlg::OnSaveClicked)
	ON_BN_CLICKED(LOAD_BTN, &CPaintMFCDlg::OnLoadClicked)
END_MESSAGE_MAP()


// CPaintMFCDlg message handlers

BOOL CPaintMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	InnerInit();

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

void CPaintMFCDlg::InnerInit() {

	borderWeightControl.SetCurSel(0);  // Setting default border weight to 1
	_penColor = RGB(0, 0, 0);
	borderColorControl.SetColor(_penColor); // Setting default border color to Black
	_fillColor = RGB(255, 255, 255);
	fillColorControl.SetColor(_fillColor); // Setting default fill color to White
}

void CPaintMFCDlg::InnerOnPaint()
{
	CPaintDC context(this);

	for (int i = 0; i < _shapes.size(); i++)
		_shapes[i]->draw(&context);
}

void CPaintMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// save start cursor point
	_endP = _startP = point;
	_isMousePressed = true;

	//CString chosenBorderWeight;
	//borderWeightControl.GetWindowTextW(chosenBorderWeight);
	//_penWidth = _wtof(chosenBorderWeight);
	//_penColor = borderColorControl.GetColor();
	//_fillColor = fillColorControl.GetColor();

	_currentShapeDraw = ShapesFactory::createShape(_chosenShapeType, point.x, point.y, point.x, point.y, _penWidth, _penColor, _fillColor);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPaintMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// save end cursor point
	_endP = point;
	_isMousePressed = false;

	// save the figure in data array
	_shapes.push_back(_currentShapeDraw);

	Invalidate();
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

		_endP = point; // update
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

void CPaintMFCDlg::OnBnClickedBrdrclrCtrl()
{
	_penColor = borderColorControl.GetColor();
}

void CPaintMFCDlg::OnCbnSelchangeBrdrwghtCtrl()
{
	CString tempWidth;
	borderWeightControl.GetLBText(borderWeightControl.GetCurSel(), tempWidth);
	_penWidth = _wtof(tempWidth);
}

void CPaintMFCDlg::OnBnClickedFillclrCtrl()
{
	_fillColor = fillColorControl.GetColor();
}


const string STATE_FILE_NAME = "savedState.json";

void CPaintMFCDlg::OnSaveClicked()
{
	vector<json> figuresAsJsons(_shapes.size());
	std::transform(_shapes.begin(), _shapes.end(),
		figuresAsJsons.begin(), [](Figure* figure) -> json { return figure->toJson(); });

	std::remove(STATE_FILE_NAME.c_str());
	ofstream o(STATE_FILE_NAME);
	o << std::setw(4) << figuresAsJsons << std::endl; // write pretty json to the file
	o.close();
}


void CPaintMFCDlg::OnLoadClicked()
{
	ifstream file(STATE_FILE_NAME);
	if (!file) {
		return; // there is no save state file
	}

	json figuresArrJson;
	file >> figuresArrJson;
	file.close();

	if (figuresArrJson.empty())
		return; // don't load on nothing	

	_shapes.clear();
	for (json const& figureJson : figuresArrJson) {
		Figure* figure = ShapesFactory::createShape(figureJson);
		_shapes.push_back(figure);
	}
	Invalidate();
}
