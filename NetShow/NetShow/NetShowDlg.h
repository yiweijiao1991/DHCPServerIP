
// NetShowDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#include "SearchNet.h"
#include "afxcmn.h"
// CNetShowDlg �Ի���
class CNetShowDlg : public CDialog
{
// ����
public:
	CNetShowDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETSHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
