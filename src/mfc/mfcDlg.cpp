
// _mfcDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "mfc.h"
#include "mfcDlg.h"
#include "afxdialogex.h"
#include "Node.h"
#include "JsonReader.h"
#include "DijkstraMake.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CmfcDlg 대화 상자



CmfcDlg::CmfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, startBox, mStartBox);
	DDX_Control(pDX, destBox, mDestBox);
	DDX_Control(pDX, IDC_EDIT1, mDeleteIDX);
}

BEGIN_MESSAGE_MAP(CmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcDlg::OnBnClickedButton2)
	ON_EN_CHANGE(startBox, &CmfcDlg::OnEnChangestartbox)
	ON_BN_CLICKED(IDC_BUTTON3, &CmfcDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CmfcDlg 메시지 처리기

BOOL CmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmfcDlg::OnBnClickedButton1()
{
	nodes = DataReader::ReadNode("node.json", 30 * 1024);
	edges = DataReader::ReadEdge("edge.json", 50 * 1024, nodes);
	int num = 0;
	for (unsigned i = 0; i < nodes.size(); ++i) {
		num += edges[i].size();
	}
	minX = INT_MAX;
	maxX = INT_MIN;

	minY = INT_MAX;
	maxY = INT_MIN;
	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		if (nodes[i].x < minX)
			minX = nodes[i].x;
		if (nodes[i].x > maxX)
			maxX = nodes[i].x;

		if (nodes[i].y < minY)
			minY = nodes[i].y;
		if (nodes[i].y > maxY)
			maxY = nodes[i].y;
	}
	CClientDC dc(this);
	CString str;
	width = maxX - minX;
	height = maxY - minY;
	percent = 20;

	dc.MoveTo(minX, minY);
	dc.LineTo(maxX, minY);
	
	dc.MoveTo(10, 10);
	dc.LineTo(10 + width / percent + 40, 10);

	dc.MoveTo(10, 10);
	dc.LineTo(10, 10 + height / percent + 40);

	dc.MoveTo(10, 10 + height / percent + 40);
	dc.LineTo(10 + width / percent + 40, 10 + height / percent + 40);

	dc.MoveTo(10 + width / percent + 40, 10);
	dc.LineTo(10 + width / percent + 40, 10 + height / percent + 40);
	CPen pen;
	pen.CreatePen(PS_DOT, 3, RGB(255, 0, 0));

	for (unsigned i = 0; i < nodes.size(); ++i) {
		int x1 = nodes[i].x / percent - minX / percent + 15, x2 = nodes[i].x / percent + 25 - minX / percent;
		int y1 = nodes[i].y / percent - minY / percent + 15, y2 = nodes[i].y / percent + 25 - minY / percent;
		y1 = 10 + height / percent + 40 - y1;
		y2 = 10 + height / percent + 40 - y2;
		str.Format(_T("%d"), nodes[i].fid);
		dc.Ellipse(x1,y1,x2,y2);
		dc.TextOutW((x1 + x2) / 2, (y1 + y2) / 2, str);
	}
	for (unsigned i = 0; i < edges.size(); ++i) {
		for (unsigned j = 0; j < edges[i].size(); ++j) {
			int s = edges[i][j].getStart();
			int e = edges[i][j].getDest();		
			int x1 = nodes[s].x / percent - minX / percent + 20, x2 = nodes[e].x / percent - minX / percent + 20;
			int y1 = nodes[s].y / percent - minY / percent + 20, y2 = nodes[e].y / percent - minY / percent + 20;
			y1 = 10 + height / percent + 40 - y1;
			y2 = 10 + height / percent + 40 - y2;
			dc.MoveTo(x1, y1);
			dc.LineTo(x2, y2);
		}
	}
}

void CmfcDlg::OnBnClickedButton2() // 경로 생성 버튼
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	drawPath(&pen);
	path.resize(0);
	CString str;
	mStartBox.GetWindowTextW(str);
	int start = StrToInt(str);
	mDestBox.GetWindowTextW(str);
	int dest = StrToInt(str);
	Djikstra algorithm(nodes, edges);
	if (0 > start || (unsigned)start >= nodes.size()){
		MessageBox(L"잘못된 입력입니다");
		return;
	}
	if (0 > dest || (unsigned)dest >= nodes.size()){
		MessageBox(L"잘못된 입력입니다");
		return;
	}

	path = algorithm.findPath(start, dest);
	if (path.size() == 0)
		MessageBox(L"경로가 존재하지 않습니다");
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	drawPath(&pen);
}


void CmfcDlg::OnEnChangestartbox()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CmfcDlg::drawPath(CPen* pen) // route drawing
{	
	CClientDC dc(this);	

	CPen* oldPen;
	oldPen = dc.SelectObject(pen);
	for (unsigned i = 1; i < path.size(); ++i)
	{
		int s = path[i-1];
		int e = path[i];

		int x1 = nodes[s].x / percent - minX / percent + 20, x2 = nodes[e].x / percent - minX / percent + 20;
		int y1 = nodes[s].y / percent - minY / percent + 20, y2 = nodes[e].y / percent - minY / percent + 20;
		y1 = 10 + height / percent + 40 - y1;
		y2 = 10 + height / percent + 40 - y2;
		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y2);
	}
	dc.SelectObject(oldPen);
}


void CmfcDlg::OnBnClickedButton3()//노드 제거에 대한 기능
{
	CClientDC dc(this);
	CString str;
	mDeleteIDX.GetWindowTextW(str);
	int deleteIDX = StrToInt(str);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	CPen* old;
	old = dc.SelectObject(&pen);
	for (unsigned i = 0; i < edges.size(); ++i) {
		for (unsigned j = 0; j < edges[i].size(); ++j) {
			int s = edges[i][j].getStart();
			int e = edges[i][j].getDest();
			int x1 = nodes[s].x / percent - minX / percent + 20, x2 = nodes[e].x / percent - minX / percent + 20;
			int y1 = nodes[s].y / percent - minY / percent + 20, y2 = nodes[e].y / percent - minY / percent + 20;
			y1 = 10 + height / percent + 40 - y1;
			y2 = 10 + height / percent + 40 - y2;
			dc.MoveTo(x1, y1);
			dc.LineTo(x2, y2);
		}
	}
	dc.SelectObject(old);
	edges[deleteIDX].resize(0);
	for (unsigned i = 0; i < edges.size(); ++i) {
		for (unsigned j = 0; j < edges[i].size();) {
			if (edges[i][j].getDest() == deleteIDX) {
				edges[i][j] = edges[i].back();
				edges[i].pop_back();
			}
			else {
				++j;
			}
		}
	}
	for (unsigned i = 0; i < edges.size(); ++i) {
		for (unsigned j = 0; j < edges[i].size(); ++j) {
			int s = edges[i][j].getStart();
			int e = edges[i][j].getDest();
			int x1 = nodes[s].x / percent - minX / percent + 20, x2 = nodes[e].x / percent - minX / percent + 20;
			int y1 = nodes[s].y / percent - minY / percent + 20, y2 = nodes[e].y / percent - minY / percent + 20;
			y1 = 10 + height / percent + 40 - y1;
			y2 = 10 + height / percent + 40 - y2;
			dc.MoveTo(x1, y1);
			dc.LineTo(x2, y2);
		}
	}
}
