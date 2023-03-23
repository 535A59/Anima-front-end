// MFCRecordName.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication.h"
#include "afxdialogex.h"
#include "MFCRecordName.h"


// MFCRecordName 对话框

IMPLEMENT_DYNAMIC(MFCRecordName, CDialogEx)

MFCRecordName::MFCRecordName(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECORDNAME, pParent)
{

}

MFCRecordName::~MFCRecordName()
{
}

void MFCRecordName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MFCRecordName, CDialogEx)
END_MESSAGE_MAP()


// MFCRecordName 消息处理程序
