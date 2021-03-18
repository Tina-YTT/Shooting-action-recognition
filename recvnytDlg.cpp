
// recvnytDlg.cpp : 实现文件
//
//添加的程序均按以下格式
/*****		XXXXX1022@NUST			***********/
/*		内容			*/
/**********************************************/

#include "stdafx.h"
#include "recvnyt.h"
#include "recvnytDlg.h"
#include "afxdialogex.h"

/***	需要的库1022@NUST			****/
#include<opencv2/opencv.hpp> // 主要是opencv，要用到其中的机器学习分类算法api
#include<opencv2/ml/ml.hpp>
#include <iostream>
#include <fstream>
# include <conio.h>
using namespace std; //  命名空间
using namespace cv;
using namespace ml;
/********************/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum NeuronBones
{
	Hips = 0,
	RightUpLeg = 1,
	RightLeg = 2,
	RightFoot = 3,
	LeftUpLeg = 4,
	LeftLeg = 5,
	LeftFoot = 6,
	Spine = 7,
	Spine1 = 8,
	Spine2 = 9,
	Spine3 = 10,
	Neck = 11,
	Head = 12,
	RightShoulder = 13,
	RightArm = 14,
	RightForeArm = 15,
	RightHand = 16,
	RightHandThumb1 = 17,
	RightHandThumb2 = 18,
	RightHandThumb3 = 19,
	RightInHandIndex = 20,
	RightHandIndex1 = 21,
	RightHandIndex2 = 22,
	RightHandIndex3 = 23,
	RightInHandMiddle = 24,
	RightHandMiddle1 = 25,
	RightHandMiddle2 = 26,
	RightHandMiddle3 = 27,
	RightInHandRing = 28,
	RightHandRing1 = 29,
	RightHandRing2 = 30,
	RightHandRing3 = 31,
	RightInHandPinky = 32,
	RightHandPinky1 = 33,
	RightHandPinky2 = 34,
	RightHandPinky3 = 35,
	LeftShoulder = 36,
	LeftArm = 37,
	LeftForeArm = 38,
	LeftHand = 39,
	LeftHandThumb1 = 40,
	LeftHandThumb2 = 41,
	LeftHandThumb3 = 42,
	LeftInHandIndex = 43,
	LeftHandIndex1 = 44,
	LeftHandIndex2 = 45,
	LeftHandIndex3 = 46,
	LeftInHandMiddle = 47,
	LeftHandMiddle1 = 48,
	LeftHandMiddle2 = 49,
	LeftHandMiddle3 = 50,
	LeftInHandRing = 51,
	LeftHandRing1 = 52,
	LeftHandRing2 = 53,
	LeftHandRing3 = 54,
	LeftInHandPinky = 55,
	LeftHandPinky1 = 56,
	LeftHandPinky2 = 57,
	LeftHandPinky3 = 58,

	NumOfBones
};

//消息头
#pragma pack(1)
typedef struct _BvhDataHeader
{
	unsigned short Token1;               // Package start token: 0xDDFF
	char DataVersion[4];     // Version of community data format: 1.1.0.0
	unsigned short DataCount;            // Values count
	byte bWithDisp;              // With/out displacement
	byte bWithReference;         // With/out reference bone data at first
	unsigned int AvatarIndex;            // Avatar index
	char AvatarName[32];           // Avatar name
	unsigned int FrameIndex;             // Frame data index
	unsigned int Reserved;               // Reserved, only enable this package has 64bytes length
	unsigned int Reserved1;              // Reserved, only enable this package has 64bytes length
	unsigned int Reserved2;              // Reserved, only enable this package has 64bytes length
	unsigned short Token2;               // Package end token: 0xEEFF
}BvhDataHeader;
#pragma pack()

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CrecvnytDlg 对话框




CrecvnytDlg::CrecvnytDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CrecvnytDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CrecvnytDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CrecvnytDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CrecvnytDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CrecvnytDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK2, &CrecvnytDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CrecvnytDlg 消息处理程序

BOOL CrecvnytDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CrecvnytDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CrecvnytDlg::OnPaint()
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
HCURSOR CrecvnytDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//recv data thread
char tcpRecvBuff[6000] = { 0 };
float nidata[180];  //根节点的位置 + 59个关节的欧拉角：一共 3 + 59* 3 = 180个浮点数
//右手坐标系，正方向：X向右，Y向上，Z向后
//180个浮点数 前3个是人物盆骨位置，单位厘米，顺序XYZ
//从第4个浮点数开始是关节欧拉角，关节欧拉角顺序：ZYX：翻滚 方向 俯仰
BvhDataHeader g_NitDataHeader = { 0 };
SOCKET sockClient;
bool g_start = false;

CStdioFile g_logfile;
CString Alllogs, oneFrameLog;
int recvtimes = 0;
DWORD WINAPI NYTThread(PVOID args)
{
	/******	 先利用提供的数据训练分类器1022@NUST    *************/
	float trainingData[3811][42];
	ifstream readFileT("qugan.txt");
	for (int m = 0; m < 3811; m++) {
		for (int n = 0; n < 42; n++) {
			readFileT >> trainingData[m][n];
		}
		//cout << trainingData[m][2] << endl;
	}

	/*******************    训练三个动作的分类器    *****************************/
	Mat traindataMat(3811, 42, CV_32FC1, trainingData);
	int labels[3811]; //= { '1','1', '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','3','3','3','3','3','3','3','3','3','3','3','3','3','3','3','3','3','3','3' };
	for (int i = 0; i < 367; i++) {
		labels[i] = 1;
	}
	for (int i = 367; i < 742; i++) {
		labels[i] = 2;
	}
	for (int i = 742; i < 1096; i++) {
		labels[i] = 3;
	}
	for (int i = 1096; i < 2441; i++) {
		labels[i] = 1;
	}
	for (int i = 2441; i < 2913; i++) {
		labels[i] = 3;
	}
	for (int i = 2913; i < 3811; i++) {
		labels[i] = 2;
	}
	Mat labelsMat(3811, 1, CV_32SC1, labels);
	////Ptr<TrainData> tData = TrainData::create(traindataMat, ROW_SAMPLE, labelsMat);	//组织训练数据

	/* 随机森林 */
	// 创建分类器
	Ptr<RTrees> model;
	model = RTrees::create();
	//树的最大可能深度
	model->setMaxDepth(10);
	//节点最小样本数量
	model->setMinSampleCount(20);
	//回归树的终止标准
	model->setRegressionAccuracy(0);
	//是否建立替代分裂点
	model->setUseSurrogates(false);
	//最大聚类簇数
	model->setMaxCategories(15);
	//先验类概率数组
	model->setPriors(Mat());
	//计算的变量重要性
	model->setCalculateVarImportance(true);
	//树节点随机选择的特征子集的大小
	model->setActiveVarCount(4);
	//终止标准
	model->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + (0.01f > 0 ? TermCriteria::EPS : 0), 100, 0.01f));

	model->train(traindataMat, ROW_SAMPLE, labelsMat);

	/*******************           蹲姿射击与非射击的分类器        **************************/
	float trainingData1[400][24];//856
	ifstream readFileT1("shoubi_dunzi_4.txt");
	for (int m = 0; m < 400; m++) {
		for (int n = 0; n < 24; n++) {
			readFileT1 >> trainingData1[m][n];
		}
	}
	Mat traindataMat1(400, 24, CV_32FC1, trainingData1);

	int labels1[400];
	for (int i = 0; i < 200; i++) {
		labels1[i] = 4;
	}
	for (int i = 200; i < 400; i++) {
		labels1[i] = 5;
	}
	Mat labelsMat1(400, 1, CV_32SC1, labels1);

	Ptr<RTrees> model1;
	model1 = RTrees::create();
	model1->setMaxDepth(10);
	model1->setMinSampleCount(20);
	model1->setRegressionAccuracy(0);
	model1->setUseSurrogates(false);
	model1->setMaxCategories(15);
	model1->setPriors(Mat());
	model1->setCalculateVarImportance(true);
	model1->setActiveVarCount(4);
	model1->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + (0.01f > 0 ? TermCriteria::EPS : 0), 100, 0.01f));
	model1->train(traindataMat1, ROW_SAMPLE, labelsMat1);
	/*****************************************************************************************************************/

	/*******************           站姿射击与非射击的分类器        **************************/
	float trainingData2[632][24];//632
	ifstream readFileT2("shoubi_zhanzi_4.txt");
	for (int m = 0; m < 632; m++) {
		for (int n = 0; n < 24; n++) {
			readFileT2 >> trainingData2[m][n];
		}
	}
	Mat traindataMat2(632, 24, CV_32FC1, trainingData2);

	int labels2[632];
	for (int i = 0; i < 221; i++) {
		labels2[i] = 4;
	}
	for (int i = 221; i < 632; i++) {
		labels2[i] = 5;
	}
	Mat labelsMat2(632, 1, CV_32SC1, labels2);

	Ptr<RTrees> model2;
	model2 = RTrees::create();
	model2->setMaxDepth(10);
	model2->setMinSampleCount(20);
	model2->setRegressionAccuracy(0);
	model2->setUseSurrogates(false);
	model2->setMaxCategories(15);
	model2->setPriors(Mat());
	model2->setCalculateVarImportance(true);
	model2->setActiveVarCount(4);
	model2->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + (0.01f > 0 ? TermCriteria::EPS : 0), 100, 0.01f));
	model2->train(traindataMat2, ROW_SAMPLE, labelsMat2);
	/*****************************************************************************************************************/

	/*******************           卧姿射击与非射击的分类器        **************************/
	float trainingData3[414][24];
	ifstream readFileT3("shoubi_wozi_4.txt");
	for (int m = 0; m < 414; m++) {
		for (int n = 0; n < 24; n++) {
			readFileT3 >> trainingData3[m][n];
		}
		//cout << trainingData[m][2] << endl;
	}
	Mat traindataMat3(414, 24, CV_32FC1, trainingData3);

	int labels3[414];
	for (int i = 0; i < 201; i++) {
		labels3[i] = 4;
	}
	for (int i = 201; i < 414; i++) {
		labels3[i] = 5;
	}
	Mat labelsMat3(414, 1, CV_32SC1, labels3);

	Ptr<RTrees> model3;
	model3 = RTrees::create();
	model3->setMaxDepth(10);
	model3->setMinSampleCount(20);
	model3->setRegressionAccuracy(0);
	model3->setUseSurrogates(false);
	model3->setMaxCategories(15);
	model3->setPriors(Mat());
	model3->setCalculateVarImportance(true);
	model3->setActiveVarCount(4);
	model3->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + (0.01f > 0 ? TermCriteria::EPS : 0), 100, 0.01f));
	model3->train(traindataMat3, ROW_SAMPLE, labelsMat3);
	/*****************************************************************************************************************/


	AllocConsole();
	_cprintf("the results listed below\n");
	/*************************************************************/

	/****	创建分类器，使用机器学习算法随机森林1022@NUST	****/
	/* 随机森林 */

	/*****************************************************************/

	int iRecvLeng = 0;
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		return 0;
	}

	SOCKADDR_IN addrSrv;
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(7001);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//向服务器发出连接
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	/*
	int ret = connect(sockClient, (struct sockaddr *)&addrSrv, sizeof(addrSrv));
	if(INVALID_SOCKET == ret)
	{
		return 0;
	}*/
	g_start = true;

	g_logfile.Open("D:\\log.txt", CFile::modeCreate | CFile::modeReadWrite);
	while (g_start)
	{

		memset(tcpRecvBuff, 0, sizeof(tcpRecvBuff));
		iRecvLeng = recv(sockClient, tcpRecvBuff, sizeof(tcpRecvBuff), 0);
		if (iRecvLeng <= 0)
		{
			continue;
		}

		memcpy(&g_NitDataHeader, tcpRecvBuff, sizeof(BvhDataHeader));
		if (g_NitDataHeader.Token1 != 0xDDFF || g_NitDataHeader.Token2 != 0xEEFF)
		{
			continue;
		}

		int dataLength = 4 * g_NitDataHeader.DataCount;
		if (iRecvLeng % (sizeof(BvhDataHeader) + dataLength) != 0)
		{
			continue;
		}
		recvtimes++;
		if (recvtimes % 60 != 0)   //1秒录制一次数据
			continue;

		memcpy(&nidata, tcpRecvBuff + sizeof(BvhDataHeader), dataLength); //赋值数据区

		/***	利用训练好的随机森林分类器 识别 1022@NUST		***/
		float txtdata1[42]; float txtdata2[24];

		for (int d = 0; d < 42; d++) {
			txtdata1[d] = nidata[d];
		}
		for (int d = 42; d < 54; d++) {
			txtdata2[d - 42] = nidata[d];
		}
		for (int d = 112; d < 124; d++) {
			txtdata2[d - 100] = nidata[d - 1];
		}

		int ZiTai = 0;
		Mat txtdatamat1(42, 1, CV_32FC1, txtdata1);
		//cout << txtdatamat1 << endl;
		double rr = model->predict(txtdatamat1);
		int flagq = 0;
		if (rr == 1) {
			//_cprintf("dun__");
			Mat txtdatamat2(24, 1, CV_32FC1, txtdata2);
			//cout << txtdatamat2 << endl;
			double rrr = model1->predict(txtdatamat2);
			if (rrr == 4) 
			{
				
				_cprintf("squating shooting\n");
				ZiTai = 1;
			}
			//else _cprintf("others\n");
		}
		if (rr == 2) {
			//_cprintf("zhan__");
			Mat txtdatamat2(24, 1, CV_32FC1, txtdata2);
			//cout << txtdatamat2 << endl;
			double rrr = model2->predict(txtdatamat2);
			if (rrr == 4) 
			{
				_cprintf("standing shooting\n");
				ZiTai = 2;
			}
			//else _cprintf("others\n");
		}
		if (rr == 3) {
			//_cprintf("wo__");
			Mat txtdatamat2(24, 1, CV_32FC1, txtdata2);
			//cout << txtdatamat1 << endl;
			double rrr = model3->predict(txtdatamat2);
			if (rrr == 4)
			{
				_cprintf("lying shooting\n");
				ZiTai = 3;
			}
			//else _cprintf("others\n");
		}
		
		HWND g_VBS3Handle = 0;
		COPYDATASTRUCT cd = { 0 };
		cd.lpData = NULL;
		cd.cbData = 0;
		g_VBS3Handle = ::FindWindow(NULL, "VRK");
		if (g_VBS3Handle != 0)
		{
			::SendMessage(g_VBS3Handle,WM_COPYDATA,ZiTai,(LPARAM)&cd);
		}
	}
	/**********************************************************/
	/*
	oneFrameLog = "";
	for (int i = 0; i < 180; i++)
	{
		CString oneData = "";
		oneData.Format("%f ", nidata[i]);
		oneFrameLog += oneData;
	}
	Alllogs += (oneFrameLog + "\n");   //1帧数据一行
	
	CString logs;
	float fx = nidata[0], fy = nidata[1], fz = nidata[2];
	logs.Format("QQQ, index= %d, pos = %f, %f, %f", 0, nidata[0], nidata[1], nidata[2]);
	for (int i = Hips; i < NumOfBones; i++)
	{
		int index = 3 + i * 3;
		//每个关节的欧拉角
		logs.Format("QQQ, index= %d, float = %f, %f, %f", i, nidata[index], nidata[index + 1], nidata[index + 2]);
		OutputDebugString(logs);
	}
	*/


	return 0;
}

void CrecvnytDlg::OnBnClickedOk()//确定
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwThreadID = 0;
	CreateThread(NULL, 0, NYTThread, 0, NULL, &dwThreadID);
	//CDialogEx::OnOK();
}


void CrecvnytDlg::OnBnClickedCancel()//取消
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_start)
	{
		g_start = false;
		closesocket(sockClient);
	}

	CDialogEx::OnCancel();
}


void CrecvnytDlg::OnBnClickedOk2()// 停止
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_start)
	{
		g_start = false;
		closesocket(sockClient);
	}
	g_logfile.WriteString(Alllogs);
	g_logfile.Close();
}
