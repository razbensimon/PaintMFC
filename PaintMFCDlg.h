
// PaintMFCDlg.h : header file
//

#pragma once
#include <vector>

#include "Figure.h"
#include "FIGURES.h"
#include "PAINT_TOOL.h"

using namespace shapes;
using namespace std;

// CPaintMFCDlg dialog
class CPaintMFCDlg : public CDialogEx
{

private:
	int _penWidth;
	COLORREF _penColor;
	COLORREF _fillColor;
	FIGURES _chosenShapeType;
	Figure* _currentShapeDraw;

	vector<Figure*> _shapes;
	vector<Figure*> _temp;  // for Redo and Undo

	bool _isMousePressed;
	PAINT_TOOL _drawMode;
	
	CPoint _startP;
	CPoint _endP;
	//CPoint _TLX; //TOP LEFT Point,for Proportion to moving


/* MFC Generated Code: */
// Construction
public:
	CPaintMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINTMFC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);	
	void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()

	CMFCColorButton borderColorControl;
	CComboBox borderWeightControl;
	CMFCColorButton fillColorControl;
private:
	void InnerOnPaint();
	void InnerInit();
	void LoadBitmapToButton(int btnID, int bitmapID);
public:
	afx_msg void OnChooseRectangleClicked();
	afx_msg void OnChooseEllipseClicked();
	afx_msg void OnChooseTriangleClicked();
	afx_msg void OnChooseLineClicked();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPenColorChanged();
	afx_msg void OnPenBorderWidthChanged();
	afx_msg void OnFillColorChanged();
	afx_msg void OnSaveClicked();
	afx_msg void OnLoadClicked();
	afx_msg void OnUndoClicked();
	afx_msg void OnRedoClicked();
	afx_msg void OnClearClicked();
	afx_msg void OnChooseHexagonClicked();	
	afx_msg void OnRemoveToolClicked();
};
