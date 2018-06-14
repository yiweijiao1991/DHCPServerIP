
// NetShowDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "SearchNet.h"
#include "afxcmn.h"
// CNetShowDlg 对话框
class CNetShowDlg : public CDialog
{
// 构造
public:
	CNetShowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETSHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ShowNetMsg;
	CSearchNet *m_searchnet;
	afx_msg void OnBnClickedOk();
	CListCtrl m_IpListShow;
};
