
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

	_chosenShape = FIGURES::RECTANGLE;
	_lastShape = NULL;
	_paintTool = PAINT_TOOL::POINTER;
	_isPressingMouse = false;
	_fillColor = RGB(255, 255, 255); // WHITE
	_penColor = RGB(0, 0, 0); // BLACK
	_penWidth = 1;
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
	ON_BN_CLICKED(BTN_RECT2, &CPaintMFCDlg::OnChooseRectangleClicked)
	ON_BN_CLICKED(BTN_ELLIPSE, &CPaintMFCDlg::OnChooseEllipseClicked)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(BTN_ELLIPSE2, &CPaintMFCDlg::OnChooseTriangleClicked)
	ON_BN_CLICKED(ID_BRDRCLR_CTRL, &CPaintMFCDlg::OnPenColorChanged)
	ON_CBN_SELCHANGE(ID_BRDRWGHT_CTRL, &CPaintMFCDlg::OnPenBorderWidthChanged)
	ON_BN_CLICKED(ID_FILLCLR_CTRL, &CPaintMFCDlg::OnFillColorChanged)
	ON_BN_CLICKED(SAVE_BTN, &CPaintMFCDlg::OnSaveClicked)
	ON_BN_CLICKED(LOAD_BTN, &CPaintMFCDlg::OnLoadClicked)
	ON_BN_CLICKED(ID_CLEAR, &CPaintMFCDlg::OnClearClicked)
	ON_BN_CLICKED(ID_REDO, &CPaintMFCDlg::OnRedoClicked)
	ON_BN_CLICKED(ID_UNDO, &CPaintMFCDlg::OnUndoClicked)
	ON_BN_CLICKED(BTN_LINE, &CPaintMFCDlg::OnChooseLineClicked)
	ON_BN_CLICKED(BTN_HEXAGON, &CPaintMFCDlg::OnChooseHexagonClicked)
	ON_BN_CLICKED(BTN_REMOVE, &CPaintMFCDlg::OnRemoveToolClicked)
	ON_BN_CLICKED(BTN_MOVE, &CPaintMFCDlg::OnMoveToolClicked)
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
	SetWindowText(_T("Paint App by Raz & Lior"));
	borderWeightControl.SetCurSel(0);  // Setting default border weight to 1	
	borderColorControl.SetColor(_penColor); // Setting default border color to Black
	fillColorControl.SetColor(_fillColor); // Setting default fill color to White	

	// Setting bitmaps to buttons
	LoadBitmapToButton(SAVE_BTN, IDB_SAVE_BMP);
	LoadBitmapToButton(LOAD_BTN, IDB_LOAD_BMP);
	LoadBitmapToButton(ID_CLEAR, IDB_BLANK_BMP);
	LoadBitmapToButton(ID_REDO, IDB_REDO_BMP);
	LoadBitmapToButton(ID_UNDO, IDB_UNDO_BMP);
	LoadBitmapToButton(BTN_REMOVE, IDB_REMOVE_TOOL);
	LoadBitmapToButton(BTN_MOVE, IDB_MOVE_BMP);
	LoadBitmapToButton(BTN_LINE, IDB_LINE_BMP);
	LoadBitmapToButton(BTN_HEXAGON, IDB_HEXAGON_BMP);
	LoadBitmapToButton(BTN_TRIANGLE, IDB_TRIANGLE_BMP);
	LoadBitmapToButton(BTN_ELLIPSE, IDB_ELLIPSE_BMP);
	LoadBitmapToButton(BTN_RECT2, IDB_RECT_BMP);
}

void CPaintMFCDlg::LoadBitmapToButton(int btnID, int bitmapID)
{
	CBitmap bitmap;
	CButton* button;
	bitmap.LoadBitmap(bitmapID);
	button = (CButton*)GetDlgItem(btnID);
	button->ModifyStyle(0, BS_BITMAP);
	button->SetBitmap(bitmap);
}

void CPaintMFCDlg::InnerOnPaint()
{
	CPaintDC context(this);

	for (int i = 0; i < static_cast<int>(_shapes.size()); i++)
		_shapes[i]->draw(&context);
}

void CPaintMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// save start cursor point
	_endPoint = _startPoint = point;
	_isPressingMouse = true;

	if (_paintTool == PAINT_TOOL::DRAW) {
		_lastShape = ShapesFactory::createShape(_chosenShape, point.x, point.y, point.x, point.y, _penWidth, _penColor, _fillColor);
	}
	else if (_paintTool == PAINT_TOOL::MOVE) {
		_lastMousePoint = point;
		for (auto iterator = _shapes.rbegin(); iterator != _shapes.rend(); ++iterator) {
			if ((*iterator)->isContains(point)) {
				_movedShape = *iterator;
				break;
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CPaintMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// save end cursor point
	_endPoint = point;
	_isPressingMouse = false;


	if (_paintTool == PAINT_TOOL::DRAW) {
		if (_startPoint == _endPoint) {
			return;
		}

		// save the figure
		_shapes.push_back(_lastShape);
		Invalidate();
	}
	else if (_paintTool == PAINT_TOOL::REMOVE) {
		for (auto iterator = _shapes.rbegin(); iterator != _shapes.rend(); ++iterator) {
			if ((*iterator)->isContains(point)) {
				_shapes.erase((iterator + 1).base());
				Invalidate();
				break;
			}
		}
	}
	else if (_paintTool == PAINT_TOOL::MOVE) {
		// cleaning
		_movedShape = NULL;
		_lastMousePoint = NULL;
	}
}

void CPaintMFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!_isPressingMouse)
		return;

	if (_paintTool == PAINT_TOOL::DRAW)
	{
		CClientDC dc(this);
		dc.SetROP2(R2_NOTXORPEN); // draw the invert color shape for "removing affect"
		_lastShape->draw(&dc);

		_endPoint = point; // update and draw
		_lastShape->setX2(point.x);
		_lastShape->setY2(point.y);
		_lastShape->draw(&dc);

		dc.SetROP2(R2_COPYPEN); // return to default 
	}
	else if (_paintTool == PAINT_TOOL::MOVE) {
		if (!_movedShape)
			return;

		//const auto leftX = min(_movedShape->getX1(), _movedShape->getX2());
		//const auto rightX = max(_movedShape->getX1(), _movedShape->getX2());
		//const auto topY = max(_movedShape->getY1(), _movedShape->getY2());
		//const auto bottomY = min(_movedShape->getY1(), _movedShape->getY2());
	
		const int deltaX = _lastMousePoint.x - point.x;
		const int deltaY = _lastMousePoint.y - point.y;
				
		_movedShape->setX1(_movedShape->getX1() - deltaX);
		_movedShape->setY1(_movedShape->getY1() - deltaY);
		_movedShape->setX2(_movedShape->getX2() - deltaX);
		_movedShape->setY2(_movedShape->getY2() - deltaY);
				
		_lastMousePoint = point;
		/*RECT rect;
		rect.bottom = ;
		rect.top = ;
		rect.left = ;
		rect.right = ;
		InvalidateRect(&rect);*/
		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CPaintMFCDlg::OnChooseRectangleClicked()
{
	_paintTool = PAINT_TOOL::DRAW;
	_chosenShape = FIGURES::RECTANGLE;
	_isPressingMouse = false;
}

void CPaintMFCDlg::OnChooseEllipseClicked()
{
	_paintTool = PAINT_TOOL::DRAW;
	_chosenShape = FIGURES::ELLIPSE;
	_isPressingMouse = false;
}

void CPaintMFCDlg::OnChooseTriangleClicked()
{
	_paintTool = PAINT_TOOL::DRAW;
	_chosenShape = FIGURES::TRIANGLE;
	_isPressingMouse = false;
}

void CPaintMFCDlg::OnChooseHexagonClicked()
{
	_paintTool = PAINT_TOOL::DRAW;
	_chosenShape = FIGURES::HEXAGON;
	_isPressingMouse = false;
}

void CPaintMFCDlg::OnChooseLineClicked()
{
	_paintTool = PAINT_TOOL::DRAW;
	_chosenShape = FIGURES::LINE;
	_isPressingMouse = false;
}

void CPaintMFCDlg::OnPenColorChanged()
{
	_penColor = borderColorControl.GetColor();
}

void CPaintMFCDlg::OnPenBorderWidthChanged()
{
	CString tempWidth;
	borderWeightControl.GetLBText(borderWeightControl.GetCurSel(), tempWidth);
	_penWidth = _wtoi(tempWidth);
}

void CPaintMFCDlg::OnFillColorChanged()
{
	_fillColor = fillColorControl.GetColor();
}

const string STATE_FILE_NAME = "savedState.json";

void CPaintMFCDlg::OnSaveClicked()
{
	// Serialize all shapes to json array, and put it on file stream.	
	vector<json> figuresAsJsons(_shapes.size());
	std::transform(_shapes.begin(), _shapes.end(),
		figuresAsJsons.begin(), [](Figure* figure) -> json { return figure->toJson(); });

	std::remove(STATE_FILE_NAME.c_str());
	ofstream o(STATE_FILE_NAME);
	o << std::setw(4) << figuresAsJsons << std::endl; // write 'pretty' json to the file
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
	_temp.clear();
	for (json const& figureJson : figuresArrJson) {
		Figure* figure = ShapesFactory::createShape(figureJson);
		_shapes.push_back(figure);
	}
	Invalidate();
}

void CPaintMFCDlg::OnClearClicked()
{
	_shapes.clear();
	_temp.clear();
	Invalidate();
}

void CPaintMFCDlg::OnRedoClicked()
{
	if (!_temp.empty())
	{
		Figure* tempfig = _temp.back();
		_temp.pop_back();
		_shapes.push_back(tempfig);
		Invalidate();
	}
}

void CPaintMFCDlg::OnUndoClicked()
{
	if (!_shapes.empty())
	{
		Figure* tempfig = _shapes.back();
		_shapes.pop_back();
		_temp.push_back(tempfig);
		Invalidate();
	}
}

void CPaintMFCDlg::OnRemoveToolClicked()
{
	_paintTool = PAINT_TOOL::REMOVE;
	_isPressingMouse = false;
}

void CPaintMFCDlg::OnMoveToolClicked()
{
	_paintTool = PAINT_TOOL::MOVE;
	_isPressingMouse = false;
}
