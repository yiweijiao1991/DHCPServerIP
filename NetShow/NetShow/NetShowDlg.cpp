
// NetShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetShow.h"
#include "NetShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetShowDlg �Ի���




CNetShowDlg::CNetShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetShowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_searchnet =new CSearchNet();
}

void CNetShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_NET, m_ShowNetMsg);
	DDX_Control(pDX, IDC_LIST1, m_IpListShow);
}

BEGIN_MESSAGE_MAP(CNetShowDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CNetShowDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNetShowDlg ��Ϣ�������

BOOL CNetShowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������



	DWORD dwStyle=GetWindowLong(m_IpListShow.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_IpListShow.GetSafeHwnd(),GWL_STYLE,dwStyle);
	m_IpListShow.InsertColumn(0,_T("����������"),LVCFMT_LEFT,400);
	m_IpListShow.InsertColumn(0,_T("IP��ַ"),LVCFMT_LEFT,150);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetShowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNetShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNetShowDlg::OnBnClickedOk()
{
	SNetMsg *net[10];
	int count = 0;
	int num = 0;
	int i = 0;
	int index = 0;
	m_ShowNetMsg.SetWindowText(_T("��ʼ��ѯ������"));
	m_IpListShow.DeleteAllItems();
	int t = 0;
	for (t=0;t<10;t++)
	{
		net[t] = (SNetMsg*)malloc(sizeof(SNetMsg));
		memset(net[t],0,sizeof(SNetMsg));
	}
	count = m_searchnet->SearchNet(net,&num);
	if (num > 0)
	{
		for (i=0;i<num;i++)
		{
			CString ip(net[i]->ip);
			//CString name(net[i].name);

			index = m_IpListShow.InsertItem(0,ip);//��ip����ListView
			//m_IpListShow.SetItem(index,1,LVIF_TEXT,name, 0, 0, 0,0); 

		}	
	}
	m_ShowNetMsg.SetWindowText(_T("��ѯ���"));

	for (t=0;t<10;t++)
	{
		if (net[t] != NULL)
		{
			free(net[t]);
			net[t] = NULL;
		}
		
	}
	//OnOK();
}
