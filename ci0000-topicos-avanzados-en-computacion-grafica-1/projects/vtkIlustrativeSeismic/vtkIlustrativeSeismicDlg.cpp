// vtkIlustrativeSeismicDlg.cpp : implementation file
//

// INCLUDES *******************************************************************

#include "stdafx.h"
#include "vtkIlustrativeSeismic.h"
#include "vtkIlustrativeSeismicDlg.h"

// DEFINES & MACROS ***********************************************************

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// GLOBAL VARIABLES ***********************************************************

static char   g_pattern[5][10] = { "g:\\p1.bmp", "g:\\p2.bmp", "g:\\p3.bmp", "g:\\p4.bmp", "g:\\p5.bmp" };
static double g_color[6][3]    = {{1.0, 1.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };


// STATIC FUNCTIONS ***********************************************************

static void
OnVtkDblClick(vtkObject* obj, unsigned long, void*, void*)
{
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);

	if(iren && iren->GetRepeatCount())
	{
		AfxMessageBox("Double Click");
	}
}

// CAboutDlg CLASS IMPLEMENTATION *********************************************

//
// CAboutDlg dialog used for App About
//
class CAboutDlg : public CDialog
{
	enum { IDD = IDD_ABOUTBOX };

	public:

		CAboutDlg();

	protected:

		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRenderDlg CLASS IMPLEMENTATION ********************************************

BEGIN_MESSAGE_MAP(CRenderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LOADDATA, &CRenderDlg::OnBnClickedLoaddata)
	ON_BN_CLICKED(IDC_LOADHORIZON, &CRenderDlg::OnBnClickedLoadhorizon)
	ON_BN_CLICKED(IDC_CHECK_VOL, &CRenderDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_IL, &CRenderDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_XL, &CRenderDlg::OnBnClickedCheck)
	ON_BN_CLICKED(IDC_CHECK_TS, &CRenderDlg::OnBnClickedCheck)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOL_MINX, &CRenderDlg::OnNMReleasedcaptureVolCrop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOL_MAXX, &CRenderDlg::OnNMReleasedcaptureVolCrop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOL_MINY, &CRenderDlg::OnNMReleasedcaptureVolCrop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOL_MAXY, &CRenderDlg::OnNMReleasedcaptureVolCrop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOL_MINZ, &CRenderDlg::OnNMReleasedcaptureVolCrop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOL_MAXZ, &CRenderDlg::OnNMReleasedcaptureVolCrop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_IL, &CRenderDlg::OnNMReleasedcaptureInline)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_XL, &CRenderDlg::OnNMReleasedcaptureXline)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TS, &CRenderDlg::OnNMReleasedcaptureTimeSlice)
	ON_LBN_SELCHANGE(IDC_HORZLIST, &CRenderDlg::OnLbnSelchangeHorzlist)
	ON_CLBN_CHKCHANGE(IDC_HORZLIST, &CRenderDlg::OnLbnChkchangeHorzlist)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_ILOP, &CRenderDlg::OnNMReleasedcaptureSliderSliceOpacity)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_XLOP, &CRenderDlg::OnNMReleasedcaptureSliderSliceOpacity)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TSOP, &CRenderDlg::OnNMReleasedcaptureSliderSliceOpacity)
END_MESSAGE_MAP()

CRenderDlg::CRenderDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRenderDlg::IDD, pParent)
, m_pRenderer(vtkRenderer::New())
, m_pMFCWindow(NULL)
, m_pReader(NULL)
, m_pVolume(NULL)
, m_pVolumeMapper(NULL)
, m_pInlineActor(NULL)
, m_pXlineActor(NULL)
, m_pTimeActor(NULL)
, m_bShowIl(FALSE)
, m_bShowXl(TRUE)
, m_bShowTs(FALSE)
, m_bShowVolume(FALSE)
, m_nIlSlice(0)
, m_nXlSlice(0)
, m_nTsSlice(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for(int i = 0; i < 6; ++i)
		m_pVolumeCrop[i] = 0;

	m_pSeismicPalette = vtkColorTransferFunction::New();
	srand(time(NULL));
}

CRenderDlg::~CRenderDlg()
{
	if(m_pReader)
		m_pReader->Delete();

	if(m_pRenderer)
		m_pRenderer->Delete();

	m_pSeismicPalette->Delete();
}

void CRenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_IL, m_bShowIl);
	DDX_Check(pDX, IDC_CHECK_XL, m_bShowXl);
	DDX_Check(pDX, IDC_CHECK_TS, m_bShowTs);
	DDX_Check(pDX, IDC_CHECK_VOL, m_bShowVolume);

	DDX_Control(pDX, IDC_SLIDER_IL, m_CtrlIlSlider);
	DDX_Control(pDX, IDC_SLIDER_XL, m_CtrlXlSlider);
	DDX_Control(pDX, IDC_SLIDER_TS, m_CtrlTsSlider);

	DDX_Control(pDX, IDC_SLIDER_VOL_MINX, m_CtrlMinXSlider);
	DDX_Control(pDX, IDC_SLIDER_VOL_MAXX, m_CtrlMaxXSlider);
	DDX_Control(pDX, IDC_SLIDER_VOL_MINY, m_CtrlMinYSlider);
	DDX_Control(pDX, IDC_SLIDER_VOL_MAXY, m_CtrlMaxYSlider);
	DDX_Control(pDX, IDC_SLIDER_VOL_MINZ, m_CtrlMinZSlider);
	DDX_Control(pDX, IDC_SLIDER_VOL_MAXZ, m_CtrlMaxZSlider);

	DDX_Slider(pDX, IDC_SLIDER_IL, m_nIlSlice);
	DDX_Slider(pDX, IDC_SLIDER_XL, m_nXlSlice);
	DDX_Slider(pDX, IDC_SLIDER_TS, m_nTsSlice);
	DDX_Slider(pDX, IDC_SLIDER_VOL_MINX, m_pVolumeCrop[0]);
	DDX_Slider(pDX, IDC_SLIDER_VOL_MAXX, m_pVolumeCrop[1]);
	DDX_Slider(pDX, IDC_SLIDER_VOL_MINY, m_pVolumeCrop[2]);
	DDX_Slider(pDX, IDC_SLIDER_VOL_MAXY, m_pVolumeCrop[3]);
	DDX_Slider(pDX, IDC_SLIDER_VOL_MINZ, m_pVolumeCrop[4]);
	DDX_Slider(pDX, IDC_SLIDER_VOL_MAXZ, m_pVolumeCrop[5]);
	DDX_Control(pDX, IDC_HORZLIST, m_CtrlHorizonList);
	DDX_Control(pDX, IDC_SLIDER_ILOP, m_CtrlILOpacitySlider);
	DDX_Control(pDX, IDC_SLIDER_XLOP, m_CtrlXLOpacitySlider);
	DDX_Control(pDX, IDC_SLIDER_TSOP, m_CtrlTSOpacitySlider);
}

BOOL CRenderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rct;
	CRect rctClient;

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// adjust dialog & window size
	m_pMFCWindow = new vtkMFCWindow(this->GetDlgItem(IDC_VTK_RENDER));

	// get double click events
	vtkCallbackCommand* pCallback = vtkCallbackCommand::New();
	pCallback->SetCallback(OnVtkDblClick);
	m_pMFCWindow->GetInteractor()->AddObserver(vtkCommand::LeftButtonPressEvent, pCallback, 1.0);
	pCallback->Delete();

	m_pMFCWindow->GetClientRect(&rct);
	GetClientRect(&rctClient);

	// set the vtk renderer, windows, etc
	m_pMFCWindow->GetRenderWindow()->AddRenderer(m_pRenderer);
	ExecutePipeline();

	return TRUE; // return TRUE  unless you set the focus to a control
}

void CRenderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRenderDlg::OnPaint()
{
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRenderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRenderDlg::ExecutePipeline()
{
	if(!m_pReader)
	{
		vtkTextMapper* pTextMapper = vtkTextMapper::New();
		pTextMapper->SetInput("Ilustrative Seismic Data Project");
		pTextMapper->GetTextProperty()->SetFontSize(24);

		vtkActor2D* pActor = vtkActor2D::New();
		pActor->SetMapper(pTextMapper);

		m_pRenderer->SetBackground(0.1, 0.2, 0.4);
		m_pRenderer->AddActor(pActor);

		m_pRenderer->ResetCamera();

		pActor->Delete();
		pTextMapper->Delete();
		return;
	}

	double* pRange  = m_pReader->GetOutput()->GetScalarRange();
	double* pCenter = m_pReader->GetOutput()->GetCenter();
	double* pBounds = m_pReader->GetOutput()->GetBounds();

	std::cout << pCenter[0] << " " << pCenter[1] << " " << pCenter[2] << "\n";
	std::cout << pBounds[0] << " " << pBounds[1] << " " << pBounds[2] << pBounds[3] << " " << pBounds[4] << " " << pBounds[5] << "\n";
	std::cout << pRange[0] << " " << pRange[1] << "\n";

	// Opacity Function
	vtkPiecewiseFunction* pOpacity = vtkPiecewiseFunction::New();
	pOpacity->AddSegment(-10000.0, 0.0,  3000.0, 0.0);
	pOpacity->AddSegment(-3000.0,  1.0,    -1.0, 1.0);
	pOpacity->AddSegment(-1000.0,  0.0,  1000.0, 0.0);
	pOpacity->AddSegment( 1000.0,  0.0,  3000.0, 0.0);
	pOpacity->AddSegment( 3000.0,  0.0, 10000.0, 0.0);

	// Volume Property (reflection seismic cube)
	vtkVolumeProperty* pProperty = vtkVolumeProperty::New();
	pProperty->SetAmbient(0.5);
	pProperty->SetColor(m_pSeismicPalette);
	pProperty->SetScalarOpacity(pOpacity);
	pProperty->SetInterpolationTypeToLinear();
	pProperty->ShadeOn();

	// Volume Mapper
	if(m_pVolumeMapper)
		m_pVolumeMapper->Delete();

	m_pVolumeMapper = vtkVolumeTextureMapper3D::New();
	m_pVolumeMapper->SetSampleDistance(0.01);
	m_pVolumeMapper->SetPreferredMethodToFragmentProgram();
	m_pVolumeMapper->SetInput((vtkImageData*)m_pReader->GetOutput());
	m_pVolumeMapper->CroppingOn();
	m_pVolumeMapper->SetCroppingRegionPlanes(m_pVolumeCrop[0], m_pVolumeCrop[1], m_pVolumeCrop[2], m_pVolumeCrop[3], m_pVolumeCrop[4], m_pVolumeCrop[5]);

	// Volume Object
	if(m_pVolume)
		m_pVolume->Delete();

	m_pVolume = vtkVolume::New();
	m_pVolume->SetMapper(m_pVolumeMapper);
	m_pVolume->SetProperty(pProperty);
	m_pVolume->SetVisibility(m_bShowVolume);

	m_pVolumeMapper->Delete();
	pProperty->Delete();
	pOpacity->Delete();

	// Outline Filter
	vtkOutlineFilter* pOutline = vtkOutlineFilter::New();
	pOutline->SetInput((vtkDataObject*)m_pReader->GetOutput());

	vtkPolyDataMapper* pOutlineMapper = vtkPolyDataMapper::New();
	pOutlineMapper->SetInput(pOutline->GetOutput());

	vtkActor* pOutlineActor = vtkActor::New();
	pOutlineActor->SetMapper(pOutlineMapper);
	pOutlineActor->GetProperty()->SetColor(1.0, 1.0, 1.0);

	m_pRenderer->AddVolume(m_pVolume);
	m_pRenderer->AddActor(pOutlineActor);

	pOutlineActor->Delete();
	pOutlineMapper->Delete();
	pOutline->Delete();

	// Create Slices
	UpdateInlineSlice();
	UpdateXlineSlice();
	UpdateTimeSlice();

	// Setup Renderer
	m_pRenderer->SetBackground(0.1, 0.2, 0.4);

	m_pRenderer->GetActiveCamera()->Azimuth(20.0);
	m_pRenderer->GetActiveCamera()->Dolly(0.005);
	m_pRenderer->GetActiveCamera()->SetFocalPoint(pCenter[0], pCenter[1], pCenter[2]);
	m_pRenderer->ResetCameraClippingRange();

	UpdateLights();
}

void CRenderDlg::OnBnClickedLoaddata()
{
	static char BASED_CODE szFilter[] = "VTK Files (*.vtk)|*.vtk|All Files (*.*)|*.*||";
	CFileDialog fileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(fileDialog.DoModal() == IDOK)
	{
		ClearHorizons();

		if(m_pRenderer)
		{
			m_pMFCWindow->GetRenderWindow()->RemoveRenderer(m_pRenderer);
			m_pRenderer->Delete();
		}

		m_pRenderer = vtkRenderer::New();
		m_pMFCWindow->GetRenderWindow()->AddRenderer(m_pRenderer);

		if(!m_pReader)
			m_pReader = vtkStructuredPointsReader::New();

		m_pReader->SetFileName(fileDialog.GetPathName());
		m_pReader->Update();

		double* pBounds = m_pReader->GetOutput()->GetBounds();
		double* pRange  = m_pReader->GetOutput()->GetScalarRange();

		m_CtrlIlSlider.SetRange(pBounds[0], pBounds[1]);
		m_CtrlXlSlider.SetRange(pBounds[2], pBounds[3]);
		m_CtrlTsSlider.SetRange(pBounds[4], pBounds[5]);
		m_CtrlMinXSlider.SetRange(pBounds[0], pBounds[1]);
		m_CtrlMaxXSlider.SetRange(pBounds[0], pBounds[1]);
		m_CtrlMinYSlider.SetRange(pBounds[2], pBounds[3]);
		m_CtrlMaxYSlider.SetRange(pBounds[2], pBounds[3]);
		m_CtrlMinZSlider.SetRange(pBounds[4], pBounds[5]);
		m_CtrlMaxZSlider.SetRange(pBounds[4], pBounds[5]);

		m_nIlSlice = pBounds[0];
		m_nXlSlice = pBounds[2];
		m_nTsSlice = pBounds[4];

		m_pSeismicPalette->RemoveAllPoints();
		m_pSeismicPalette->AddRGBPoint(pRange[0] , 1.0 , 0.0 , 0.0);
		m_pSeismicPalette->AddRGBPoint(      0.0 , 0.8 , 0.8 , 0.8);
		m_pSeismicPalette->AddRGBPoint(pRange[1] , 0.0 , 0.0 , 1.0);

		for(int i = 0; i < 6; ++i)
			m_pVolumeCrop[i] = pBounds[i];

		UpdateData(FALSE);

		ExecutePipeline();

		if(m_pMFCWindow)
			m_pMFCWindow->RedrawWindow();
	}
}

void CRenderDlg::OnBnClickedLoadhorizon()
{
	static char BASED_CODE szFilter[] = "VTK Files (*.vtk)|*.vtk|All Files (*.*)|*.*||";
	CFileDialog fileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(fileDialog.DoModal() == IDOK)
	{
		if(!m_pRenderer)
		{
			m_pRenderer = vtkRenderer::New();
			m_pMFCWindow->GetRenderWindow()->AddRenderer(m_pRenderer);
		}

		HORIZONINFO h;
		h.bPicked  = false;
		h.bVisible = true;

		h.pReader = vtkStructuredPointsReader::New();
		h.pReader->SetFileName(fileDialog.GetPathName());
		h.pReader->Update();

		double* pHorizonRange = h.pReader->GetOutput()->GetScalarRange();

		vtkImageDataGeometryFilter* pHorizonGeometry = vtkImageDataGeometryFilter::New();
		pHorizonGeometry->SetInput(h.pReader->GetOutput());

		vtkWarpScalar* pHorizonWarp = vtkWarpScalar::New();
		pHorizonWarp->SetInput(pHorizonGeometry->GetOutput());
		//pHorizonWarp->SetScaleFactor(0.2);

		h.pDepthPalette = vtkColorTransferFunction::New();
		h.pDepthPalette->AddRGBPoint(pHorizonRange[0] , 1.0 , 0.0 , 0.0);
		h.pDepthPalette->AddRGBPoint(             0.0 , 1.0 , 1.0 , 1.0);
		h.pDepthPalette->AddRGBPoint(pHorizonRange[1] , 0.0 , 0.0 , 1.0);

		vtkMergeFilter* pHorizonMerge = vtkMergeFilter::New();
		pHorizonMerge->SetGeometry(pHorizonWarp->GetOutput());
		pHorizonMerge->SetScalars(h.pReader->GetOutput());

		h.pMapper = vtkDataSetMapper::New();
		h.pMapper->SetInput(pHorizonMerge->GetOutput());
		h.pMapper->SetLookupTable(h.pDepthPalette);
		h.pMapper->SetColorMode(VTK_COLOR_MODE_MAP_SCALARS);

		h.pActor = vtkActor::New();
		h.pActor->SetMapper(h.pMapper);
		h.pActor->AddPosition(0.0, 0.0, /*-675.0*/0.0);
		h.pActor->SetScale(1.0, 1.0, 0.25);

		m_pRenderer->AddActor(h.pActor);
		m_horizonList.push_back(h);

		int nItem = m_CtrlHorizonList.AddString(fileDialog.GetFileName());
		m_CtrlHorizonList.SetItemData(nItem, m_horizonList.size()-1);
		m_CtrlHorizonList.SetCheck(nItem, TRUE);

		if(m_horizonList.size() > 1)
		{
			STRATAINFO strata;
			strata.nColor       = rand()%6;
			strata.nPattern     = rand()%5;
			strata.pXlineActor  = CreateXlineStrataSection(strata.nPattern, strata.nColor, *(m_horizonList.end()-2), *(m_horizonList.end()-1));
			strata.pInlineActor = CreateInlineStrataSection(strata.nPattern, strata.nColor, *(m_horizonList.end()-2), *(m_horizonList.end()-1));

			m_ilustrativeActors.push_back( strata );
		}

		if(m_pMFCWindow)
			m_pMFCWindow->RedrawWindow();
	}
}

void CRenderDlg::OnBnClickedCheck()
{
	UpdateData();

	if(m_pVolume)
		m_pVolume->SetVisibility(m_bShowVolume);

	if(m_pInlineActor)
		m_pInlineActor->SetVisibility(m_bShowIl);

	if(m_pXlineActor)
		m_pXlineActor->SetVisibility(m_bShowXl);

	if(m_pTimeActor)
		m_pTimeActor->SetVisibility(m_bShowTs);

	m_pMFCWindow->Invalidate();
}

void CRenderDlg::OnNMReleasedcaptureVolCrop(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	m_pVolumeMapper->SetCroppingRegionPlanes(m_pVolumeCrop[0], m_pVolumeCrop[1], m_pVolumeCrop[2], m_pVolumeCrop[3], m_pVolumeCrop[4], m_pVolumeCrop[5]);
	m_pVolumeMapper->Update();

	m_pMFCWindow->Invalidate();
	*pResult = 0;
}

void CRenderDlg::OnNMReleasedcaptureInline(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	UpdateInlineSlice();
	m_pMFCWindow->Invalidate();
	*pResult = 0;
}

void CRenderDlg::OnNMReleasedcaptureXline(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	UpdateXlineSlice();
	m_pMFCWindow->Invalidate();
	*pResult = 0;
}

void CRenderDlg::OnNMReleasedcaptureTimeSlice(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData();
	UpdateTimeSlice();
	m_pMFCWindow->Invalidate();
	*pResult = 0;
}

void CRenderDlg::UpdateInlineSlice()
{
	double* pRange  = m_pReader->GetOutput()->GetScalarRange();
	double* pCenter = m_pReader->GetOutput()->GetCenter();
	double* pBounds = m_pReader->GetOutput()->GetBounds();

	vtkPlane*         pSlicePlane  = vtkPlane::New();
	vtkCutter*        pSliceCutter = vtkCutter::New();
	vtkDataSetMapper* pSliceMapper = vtkDataSetMapper::New();

	pSlicePlane->SetOrigin(pBounds[0] + m_nIlSlice + 0.01, pCenter[1], pCenter[2]);
	pSlicePlane->SetNormal(1.0, 0.0, 0.0);

	pSliceCutter->SetInputConnection(m_pReader->GetOutputPort());
	pSliceCutter->SetCutFunction(pSlicePlane);
	pSliceCutter->Update();

	pSliceMapper->SetInput(pSliceCutter->GetOutput());
	pSliceMapper->SetLookupTable(m_pSeismicPalette);
	pSliceMapper->SetScalarRange(pRange);

	if(m_pInlineActor)
		m_pRenderer->RemoveActor(m_pInlineActor);

	m_pInlineActor = vtkActor::New();
	m_pInlineActor->SetMapper(pSliceMapper);
	m_pInlineActor->SetVisibility(m_bShowIl);
	m_pRenderer->AddActor(m_pInlineActor);

	m_pInlineActor->Delete();
	pSlicePlane->Delete();
	pSliceCutter->Delete();
	pSliceMapper->Delete();

	UpdateInlineStrataColumn();
}

void CRenderDlg::UpdateXlineSlice()
{
	double* pRange  = m_pReader->GetOutput()->GetScalarRange();
	double* pCenter = m_pReader->GetOutput()->GetCenter();
	double* pBounds = m_pReader->GetOutput()->GetBounds();

	vtkPlane*         pSlicePlane  = vtkPlane::New();
	vtkCutter*        pSliceCutter = vtkCutter::New();
	vtkDataSetMapper* pSliceMapper = vtkDataSetMapper::New();

	pSlicePlane->SetOrigin(pCenter[0], pBounds[2]  + m_nXlSlice + 0.01, pCenter[2]);
	pSlicePlane->SetNormal(0.0, 1.0, 0.0);

	pSliceCutter->SetInputConnection(m_pReader->GetOutputPort());
	pSliceCutter->SetCutFunction(pSlicePlane);
	pSliceCutter->Update();

	pSliceMapper->SetInput(pSliceCutter->GetOutput());
	pSliceMapper->SetLookupTable(m_pSeismicPalette);
	pSliceMapper->SetScalarRange(pRange);

	if(m_pXlineActor)
		m_pRenderer->RemoveActor(m_pXlineActor);

	m_pXlineActor = vtkActor::New();
	m_pXlineActor->SetMapper(pSliceMapper);
	m_pXlineActor->SetVisibility(m_bShowXl);
	m_pRenderer->AddActor(m_pXlineActor);

	m_pXlineActor->Delete();
	pSlicePlane->Delete();
	pSliceCutter->Delete();
	pSliceMapper->Delete();

	UpdateXlineStrataColumn();
}

void CRenderDlg::UpdateTimeSlice()
{
	double* pRange  = m_pReader->GetOutput()->GetScalarRange();
	double* pCenter = m_pReader->GetOutput()->GetCenter();
	double* pBounds = m_pReader->GetOutput()->GetBounds();

	vtkPlane*         pSlicePlane  = vtkPlane::New();
	vtkCutter*        pSliceCutter = vtkCutter::New();
	vtkDataSetMapper* pSliceMapper = vtkDataSetMapper::New();

	pSlicePlane->SetOrigin(pCenter[0], pCenter[1], pBounds[2]  + m_nTsSlice + 0.1);
	pSlicePlane->SetNormal(0.0, 0.0, 1.0);

	pSliceCutter->SetInputConnection(m_pReader->GetOutputPort());
	pSliceCutter->SetCutFunction(pSlicePlane);
	pSliceCutter->Update();

	pSliceMapper->SetInput(pSliceCutter->GetOutput());
	pSliceMapper->SetLookupTable(m_pSeismicPalette);
	pSliceMapper->SetScalarRange(pRange);

	if(m_pTimeActor)
		m_pRenderer->RemoveActor(m_pTimeActor);

	m_pTimeActor = vtkActor::New();
	m_pTimeActor->SetMapper(pSliceMapper);
	m_pTimeActor->SetVisibility(m_bShowTs);
	m_pRenderer->AddActor(m_pTimeActor);

	m_pTimeActor->Delete();
	pSlicePlane->Delete();
	pSliceCutter->Delete();
	pSliceMapper->Delete();
}

void CRenderDlg::UpdateLights()
{
	double* pRange  = m_pReader->GetOutput()->GetScalarRange();
	double* pCenter = m_pReader->GetOutput()->GetCenter();
	double* pBounds = m_pReader->GetOutput()->GetBounds();

	vtkLight* pLight = vtkLight::New();
	pLight->SetPosition(pCenter[0] - 2*pBounds[1], pCenter[1], pCenter[2]);
	pLight->SetFocalPoint(0.0, 0.0, 0.0);
	pLight->SetColor(1.0, 1.0, 1.0);
	pLight->SetIntensity(1.0);
	m_pRenderer->AddLight(pLight);
	pLight->Delete();

 	pLight = vtkLight::New();
	pLight->SetPosition(pCenter[0], pCenter[1] - 2*pBounds[3], pCenter[2]);
	pLight->SetFocalPoint(0.0, 0.0, 0.0);
	pLight->SetColor(1.0, 1.0, 1.0);
	pLight->SetIntensity(1.0);
	m_pRenderer->AddLight(pLight);
	pLight->Delete();

	pLight = vtkLight::New();
	pLight->SetPosition(pCenter[0], pCenter[1], pCenter[2] - 2*pBounds[5]);
	pLight->SetFocalPoint(0.0, 0.0, 0.0);
	pLight->SetColor(1.0, 1.0, 1.0);
	pLight->SetIntensity(1.0);
	m_pRenderer->AddLight(pLight);
	pLight->Delete();

	pLight = vtkLight::New();
	pLight->SetPosition(pCenter[0] + 2*pBounds[1], pCenter[1], pCenter[2]);
	pLight->SetFocalPoint(0.0, 0.0, 0.0);
	pLight->SetColor(1.0, 1.0, 1.0);
	pLight->SetIntensity(1.0);
	m_pRenderer->AddLight(pLight);
	pLight->Delete();

// 	pLight = vtkLight::New();
// 	pLight->SetPosition(pCenter[0], pCenter[1] + 2*pBounds[3], pCenter[2]);
// 	pLight->SetFocalPoint(0.0, 0.0, 0.0);
// 	pLight->SetColor(1.0, 1.0, 1.0);
// 	pLight->SetIntensity(1.0);
// 	m_pRenderer->AddLight(pLight);
// 	pLight->Delete();

// 	pLight = vtkLight::New();
// 	pLight->SetPosition(pCenter[0], pCenter[1], pCenter[2] + 2*pBounds[5]);
// 	pLight->SetFocalPoint(0.0, 0.0, 0.0);
// 	pLight->SetColor(1.0, 1.0, 1.0);
// 	pLight->SetIntensity(1.0);
// 	m_pRenderer->AddLight(pLight);
// 	pLight->Delete();
}

void CRenderDlg::OnLbnSelchangeHorzlist()
{
	int nItem = m_CtrlHorizonList.GetCurSel();

	for(size_t i = 0; i < m_horizonList.size(); ++i)
	{
		HORIZONINFO& h = m_horizonList[i];
		h.pMapper->SetLookupTable(h.pDepthPalette);
	}

	if(nItem == LB_ERR)
		return;

	vtkColorTransferFunction* pDepthPalette = vtkColorTransferFunction::New();
	pDepthPalette->AddRGBPoint(0.0, 0.0 , 0.0 , 1.0);

	HORIZONINFO& h = m_horizonList[m_CtrlHorizonList.GetItemData(nItem)];
	h.pMapper->SetLookupTable(pDepthPalette);
	h.pMapper->Update();
	m_pMFCWindow->RedrawWindow();
}

void CRenderDlg::ClearHorizons()
{
	while(!m_horizonList.empty())
	{
		HORIZONINFO& h = m_horizonList.back();

		h.pReader->Delete();
		h.pMapper->Delete();
		h.pActor->Delete();
		h.pDepthPalette->Delete();

		m_horizonList.pop_back();
	}

	m_CtrlHorizonList.ResetContent();
}

vtkActor* CRenderDlg::CreateXlineStrataSection( int nPattern, int nColor, const HORIZONINFO& top, const HORIZONINFO& bottom )
{
	vtkImageData* pTopData   = (vtkImageData*)top.pReader->GetOutput();
	double*       pTopBounds = pTopData->GetBounds();

	vtkImageData* pBottomData   = (vtkImageData*)bottom.pReader->GetOutput();
	double*       pBottomBounds = pBottomData->GetBounds();

	vtkPoints* pPolyPoints = vtkPoints::New();
	vtkIdType nIndex, nPtId;
	int       i;
	int       ijk[3];
	double*   xyz;

	for(i = (int)pTopBounds[0], nIndex = 0; i <= (int)pTopBounds[1]; ++i, ++nIndex)
	{
		ijk[0] = i;
		ijk[1] = m_nXlSlice;
		ijk[2] = 0;

		nPtId  = pTopData->ComputePointId(ijk);
		xyz    = pTopData->GetPoint(nPtId);
		xyz[2] = *((float*)pTopData->GetScalarPointer(ijk));
		pPolyPoints->InsertPoint(nIndex, xyz[0], xyz[1], xyz[2]);

		nPtId  = pBottomData->ComputePointId(ijk);
		xyz    = pBottomData->GetPoint(nPtId);
		xyz[2] = *((float*)pBottomData->GetScalarPointer(ijk));
		pPolyPoints->InsertPoint((pTopBounds[1] - pTopBounds[0]) + nIndex + 1, xyz[0], xyz[1], xyz[2]);
	}

	vtkCellArray* pPolys = vtkCellArray::New();

	for(i = (int)pTopBounds[0], nIndex = 0; i < (int)pTopBounds[1]; ++i, ++nIndex)
	{
		vtkIdType quad[4];
		quad[0] = nIndex;
		quad[1] = quad[0] + 1;
		quad[2] = (pTopBounds[1] - pTopBounds[0]) + nIndex + 2;
		quad[3] = quad[2] - 1;

		pPolys->InsertNextCell(4, quad);
	}

	vtkPolyData* pPolyData = vtkPolyData::New();
	pPolyData->SetPoints(pPolyPoints);
	pPolyData->SetPolys(pPolys);

	vtkTextureMapToPlane* pTextureMap = vtkTextureMapToPlane::New();
	pTextureMap->SetInput(pPolyData);
	pTextureMap->AutomaticPlaneGenerationOn();

	vtkTransformTextureCoords* pTextCoord = vtkTransformTextureCoords::New();
	pTextCoord->SetInput(pTextureMap->GetOutput());
	pTextCoord->SetScale(10.0, 10.0, 100.0);

	vtkDataSetMapper* pMapper = vtkDataSetMapper::New();
	pMapper->SetInput(pTextCoord->GetOutput());

	vtkBMPReader* pBMPReader = vtkBMPReader::New();
	pBMPReader->SetFileName(g_pattern[nPattern]);

	vtkTexture* pTexture = vtkTexture::New();
	pTexture->SetInput(pBMPReader->GetOutput());
	pTexture->InterpolateOn();

	vtkActor* pActor = vtkActor::New();
	pActor->GetProperty()->SetColor(g_color[nColor]);
	pActor->GetProperty()->SetPointSize(3.0);
	pActor->SetMapper(pMapper);
	pActor->SetTexture(pTexture);
	pActor->AddPosition(0.0, 0.1, /*-675.0*/0.0);
	pActor->SetScale(1.0, 1.0, 0.25);

	m_pRenderer->AddActor(pActor);

	pPolyPoints->Delete();
	pPolys->Delete();
	pPolyData->Delete();
	pMapper->Delete();

	return pActor;
}

void CRenderDlg::UpdateXlineStrataColumn()
{
	for(size_t i = 0; i < m_ilustrativeActors.size(); ++i)
	{
		m_pRenderer->RemoveActor(m_ilustrativeActors[i].pXlineActor);
		//m_ilustrativeActors[i].pXlineActor->Delete();
	}

	for(size_t j = 1; j < m_horizonList.size(); ++j)
	{
		STRATAINFO& strata = m_ilustrativeActors[j-1];

		strata.pXlineActor = CreateXlineStrataSection(strata.nPattern, strata.nColor, m_horizonList[j-1], m_horizonList[j]);
	}
}

vtkActor* CRenderDlg::CreateInlineStrataSection( int nPattern, int nColor, const HORIZONINFO& top, const HORIZONINFO& bottom )
{
	vtkImageData* pTopData   = (vtkImageData*)top.pReader->GetOutput();
	double*       pTopBounds = pTopData->GetBounds();

	vtkImageData* pBottomData   = (vtkImageData*)bottom.pReader->GetOutput();
	double*       pBottomBounds = pBottomData->GetBounds();

	vtkPoints* pPolyPoints = vtkPoints::New();
	vtkIdType nIndex, nPtId;
	int       i;
	int       ijk[3];
	double*   xyz;

	for(i = (int)pTopBounds[2], nIndex = 0; i <= (int)pTopBounds[3]; ++i, ++nIndex)
	{
		ijk[0] = m_nIlSlice;
		ijk[1] = i;
		ijk[2] = 0;

		nPtId  = pTopData->ComputePointId(ijk);
		xyz    = pTopData->GetPoint(nPtId);
		xyz[2] = *((float*)pTopData->GetScalarPointer(ijk));
		pPolyPoints->InsertPoint(nIndex, xyz[0], xyz[1], xyz[2]);

		nPtId  = pBottomData->ComputePointId(ijk);
		xyz    = pBottomData->GetPoint(nPtId);
		xyz[2] = *((float*)pBottomData->GetScalarPointer(ijk));
		pPolyPoints->InsertPoint((pTopBounds[3] - pTopBounds[2]) + nIndex + 1, xyz[0], xyz[1], xyz[2]);
	}

	vtkCellArray* pPolys = vtkCellArray::New();

	for(i = (int)pTopBounds[2], nIndex = 0; i < (int)pTopBounds[3]; ++i, ++nIndex)
	{
		vtkIdType quad[4];
		quad[0] = nIndex;
		quad[1] = quad[0] + 1;
		quad[2] = (pTopBounds[3] - pTopBounds[2]) + nIndex + 2;
		quad[3] = quad[2] - 1;

		pPolys->InsertNextCell(4, quad);
	}

	vtkPolyData* pPolyData = vtkPolyData::New();
	pPolyData->SetPoints(pPolyPoints);
	pPolyData->SetPolys(pPolys);

	vtkTextureMapToPlane* pTextureMap = vtkTextureMapToPlane::New();
	pTextureMap->SetInput(pPolyData);
	pTextureMap->AutomaticPlaneGenerationOn();

	vtkTransformTextureCoords* pTextCoord = vtkTransformTextureCoords::New();
	pTextCoord->SetInput(pTextureMap->GetOutput());
	pTextCoord->SetScale(10.0, 10.0, 100.0);

	vtkDataSetMapper* pMapper = vtkDataSetMapper::New();
	pMapper->SetInput(pTextCoord->GetOutput());

	vtkBMPReader* pBMPReader = vtkBMPReader::New();
	pBMPReader->SetFileName(g_pattern[nPattern]);

	vtkTexture* pTexture = vtkTexture::New();
	pTexture->SetInput(pBMPReader->GetOutput());
	pTexture->InterpolateOn();

	vtkActor* pActor = vtkActor::New();
	pActor->GetProperty()->SetColor(g_color[nColor]);
	pActor->GetProperty()->SetPointSize(3.0);
	pActor->SetMapper(pMapper);
	pActor->SetTexture(pTexture);
	pActor->AddPosition(0.1, 0.0, /*-675.0*/0.0);
	pActor->SetScale(1.0, 1.0, 0.25);

	m_pRenderer->AddActor(pActor);

	pPolyPoints->Delete();
	pPolys->Delete();
	pPolyData->Delete();
	pMapper->Delete();

	return pActor;
}

void CRenderDlg::UpdateInlineStrataColumn()
{
	for(size_t i = 0; i < m_ilustrativeActors.size(); ++i)
	{
		m_pRenderer->RemoveActor(m_ilustrativeActors[i].pInlineActor);
		//m_ilustrativeActors[i].pInlineActor->Delete();
	}

	for(size_t j = 1; j < m_horizonList.size(); ++j)
	{
		STRATAINFO& strata = m_ilustrativeActors[j-1];

		strata.pInlineActor = CreateInlineStrataSection(strata.nPattern, strata.nColor, m_horizonList[j-1], m_horizonList[j]);
	}
}

void CRenderDlg::OnLbnChkchangeHorzlist()
{
	int nSize = m_CtrlHorizonList.GetCount();

	for(int i = 0; i < nSize; ++i)
	{
		long         nIdx = (long)m_CtrlHorizonList.GetItemData(i);
		HORIZONINFO& h    = m_horizonList[nIdx];

		h.bVisible = (m_CtrlHorizonList.GetCheck(i) == TRUE);

		if(h.bVisible)
			h.pActor->VisibilityOn();
		else
			h.pActor->VisibilityOff();
	}

	m_pMFCWindow->Invalidate();
}
void CRenderDlg::OnNMReleasedcaptureSliderSliceOpacity(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(m_pInlineActor)
		m_pInlineActor->SetVisibility(m_bShowIl);

	if(m_pXlineActor)
		m_pXlineActor->SetVisibility(m_bShowXl);

	if(m_pTimeActor)
		m_pTimeActor->SetVisibility(m_bShowTs);

	*pResult = 0;
}
