
// NetShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetShow.h"
#include "NetShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetShowDlg 对话框




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


// CNetShowDlg 消息处理程序

BOOL CNetShowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码



	DWORD dwStyle=GetWindowLong(m_IpListShow.GetSafeHwnd(),GWL_STYLE);
	dwStyle&=~LVS_TYPEMASK;
	dwStyle|=LVS_REPORT;
	SetWindowLong(m_IpListShow.GetSafeHwnd(),GWL_STYLE,dwStyle);
	m_IpListShow.InsertColumn(0,_T("网卡驱动名"),LVCFMT_LEFT,400);
	m_IpListShow.InsertColumn(0,_T("IP地址"),LVCFMT_LEFT,150);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNetShowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	m_ShowNetMsg.SetWindowText(_T("开始查询。。。"));
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

			index = m_IpListShow.InsertItem(0,ip);//将ip插入ListView
			//m_IpListShow.SetItem(index,1,LVIF_TEXT,name, 0, 0, 0,0); 

		}	
	}
	m_ShowNetMsg.SetWindowText(_T("查询完毕"));

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
