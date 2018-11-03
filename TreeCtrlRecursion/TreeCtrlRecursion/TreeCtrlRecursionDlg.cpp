
// TreeCtrlRecursionDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TreeCtrlRecursion.h"
#include "TreeCtrlRecursionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeCtrlRecursionDlg 对话框



CTreeCtrlRecursionDlg::CTreeCtrlRecursionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TREECTRLRECURSION_DIALOG, pParent)
    , m_nOption(0)
    , m_strFind(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlRecursionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE1, m_tree);
    DDX_Control(pDX, IDC_EDIT_LOG, m_editlogger);
    DDX_Radio(pDX, IDC_RD_FIND, m_nOption);
    DDX_Text(pDX, IDC_EDIT_FIND, m_strFind);
}

BEGIN_MESSAGE_MAP(CTreeCtrlRecursionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_RESET, &CTreeCtrlRecursionDlg::OnBnClickedBtnReset)
    ON_BN_CLICKED(IDC_BTN_EXECUTE, &CTreeCtrlRecursionDlg::OnBnClickedBtnExecute)
END_MESSAGE_MAP()


// CTreeCtrlRecursionDlg 消息处理程序

BOOL CTreeCtrlRecursionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    InitTree();

    GetDlgItem(IDC_EDIT_FIND)->SetFocus();
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTreeCtrlRecursionDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTreeCtrlRecursionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTreeCtrlRecursionDlg::InitTree()
{
    auto hRoot1 = m_tree.InsertItem(_T("Root1"));
    auto hRoot2 = m_tree.InsertItem(_T("Root2"));
    m_tree.InsertItem(_T("Root3"));

    auto hSubRoot1 = m_tree.InsertItem(_T("SubRoot1"), hRoot1);
    auto hSubRoot2 = m_tree.InsertItem(_T("SubRoot2"), hSubRoot1);
    auto hSubRoot3 = m_tree.InsertItem(_T("SubRoot3"), hRoot2);

    m_tree.InsertItem(_T("Leaf1"), hRoot1);
    m_tree.InsertItem(_T("Leaf2"), hSubRoot1);
    m_tree.InsertItem(_T("Leaf3"), hSubRoot2);
    m_tree.InsertItem(_T("Leaf4"), hSubRoot3);

    m_tree.Expand(hRoot1, TVE_EXPAND);
    m_tree.Expand(hRoot2, TVE_EXPAND);
    m_tree.Expand(hSubRoot1, TVE_EXPAND);
    m_tree.Expand(hSubRoot2, TVE_EXPAND);
    m_tree.Expand(hSubRoot3, TVE_EXPAND);
}

HTREEITEM CTreeCtrlRecursionDlg::findItem(LPCTSTR szItemName, HTREEITEM hBegin, HTREEITEM hEnd)
{
    auto hItem = hBegin;
    HTREEITEM hFind = NULL;

    while (hItem && hItem != hEnd) {
        
        auto strText = m_tree.GetItemText(hItem);
        putLog(_T("当前节点：") + strText);

        if (!strText.Compare(szItemName)) {
            hFind = hItem;
            break;
        }

        if (m_tree.ItemHasChildren(hItem)) {
            auto hChild = m_tree.GetChildItem(hItem);
            hFind = findItem(szItemName, hChild, hEnd);
        }

        hItem = m_tree.GetNextSiblingItem(hItem);
    }

    return hFind;
}

void CTreeCtrlRecursionDlg::deleteItems(HTREEITEM hBegin, HTREEITEM hEnd)
{
    auto hItem = hBegin;

    while (hItem && hItem != hEnd) {
        
        if (m_tree.ItemHasChildren(hItem)) {
            auto hChild = m_tree.GetChildItem(hItem);
            deleteItems(hChild, hEnd);
        }

        auto hDel = hItem; // 暂存要删除的节点

        hItem = m_tree.GetNextSiblingItem(hItem);

        auto strText = m_tree.GetItemText(hDel);
        putLog(_T("正在删除节点：") + strText);
        m_tree.DeleteItem(hDel);
    }
}


void CTreeCtrlRecursionDlg::OnBnClickedBtnReset()
{
    // TODO: 在此添加控件通知处理程序代码
    m_tree.DeleteAllItems();
    InitTree();
}


void CTreeCtrlRecursionDlg::OnBnClickedBtnExecute()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData();

    if (m_nOption == 0) {

        putLog(_T("正在查找：") + m_strFind);
        
    } else {
        

    }
}
