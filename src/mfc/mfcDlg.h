
// _mfcDlg.h: 헤더 파일
//

#pragma once
#include<vector>
#include"Edge.h"
#include"Node.h"
using namespace std;

// CmfcDlg 대화 상자
class CmfcDlg : public CDialogEx
{
// 생성입니다.
public:
	CmfcDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD__MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

private:
	vector<Node> nodes;
	vector<vector<Edge>> edges;
	vector<int> path;
public:
	int percent;
	int minX, minY, maxX, maxY;
	int width, height;
	afx_msg void OnEnChangestartbox();
	CEdit mStartBox;
	CEdit mDestBox;


private:
	void drawPath(CPen*);
public:
	CEdit mDeleteIDX;
	afx_msg void OnBnClickedButton3();
};
