
// TetrisDlg.cpp : implementation file
//
#pragma once
#include "stdafx.h"
#include "Tetris.h"
#include "TetrisDlg.h"
#include "afxdialogex.h"
#include "Field.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Field* field = 0;


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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTetrisDlg dialog



CTetrisDlg::CTetrisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TETRIS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTetrisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CTetrisDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CTetrisDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTetrisDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTetrisDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CTetrisDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CTetrisDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTetrisDlg message handlers

BOOL CTetrisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

void CTetrisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTetrisDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(0, 0, 0));
	CPen myPen1;
	myPen1.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	dc.SelectObject(myPen1);
	dc.MoveTo(WIDTH*DELTA, 0);
	dc.LineTo(WIDTH*DELTA, HEIGHT*DELTA);
	dc.MoveTo(0, HEIGHT*DELTA);
	dc.LineTo(WIDTH*DELTA, HEIGHT*DELTA);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CTetrisDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if(CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	srand(time(0));
	return 0;
}

void CTetrisDlg::OnTimer(UINT_PTR nIDEvent) {
	// TODO: Add your message handler code here and/or call default
	CDC* cdc = CWnd::GetDC();
	if(field) {
		field->draw(cdc);
		if(!field->update()) {
			delete field;
			field = 0;
			MessageBox(L"YOU DIED");
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTetrisDlg::OnBnClickedButton1() {
	SetTimer(1, 500, 0);
	if(!field)
		field = new Field();
	// TODO: Add your control notification handler code here
}


void CTetrisDlg::OnBnClickedButton2() {
	KillTimer(1);
	// TODO: Add your control notification handler code here
}


void CTetrisDlg::OnBnClickedButton3() {
	if(field && field->getFigure())
		field->getFigure()->rotare();
	// TODO: Add your control notification handler code here
}


void CTetrisDlg::OnBnClickedButton6() {
	if(field && field->getFigure())
		field->getFigure()->move(true);
	// TODO: Add your control notification handler code here
}


void CTetrisDlg::OnBnClickedButton5() {
	if(field && field->getFigure())
		field->getFigure()->move(false);
	// TODO: Add your control notification handler code here
}

void CTetrisDlg::OnBnClickedButton4() {
	if(field) delete field;
	field = new Field;
	// TODO: Add your control notification handler code here
}
