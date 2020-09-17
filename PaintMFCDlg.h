
// PaintMFCDlg.h : header file
//

#pragma once
#include "Figure.h"


// CPaintMFCDlg dialog
class CPaintMFCDlg : public CDialogEx
{

private:
	/*For dialog*/
	//CToolBar m_ToolBar;
	//CMFCColorButton m_Color; //Color Taking from the button
	//CComboBox m_ComboPenWidth;
	//CEdit test;			//For tasting only,need to remove

/*For painting....*/
	int _penWidth;
	COLORREF _penColor;
	enum FIGURES { RECTANGLE = 0, ELLIPSE };
	FIGURES _chosenShape;
	//int chosenFigure;

	CTypedPtrArray< CObArray, Figure*> _shapes;
	CTypedPtrArray< CObArray, Figure*> _tempShapes; // for Undo & Redo
/*Boolian*/

	bool isMousePressed = false;
	bool shapeMovingMode;
	bool drawMode; // checking if i'm still on shape
	//bool ShapeType1;
	//bool ShapeType2;
	//bool ShapeType3;

	/*Points*/
	CPoint startP;
	CPoint endP;
	CPoint TLX; //TOP LEFT Point,for Proportion to moving


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
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	void InnerOnPaint();
public:
	afx_msg void OnBnClickedRectangle();
	afx_msg void OnBnClickedEllipse();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
