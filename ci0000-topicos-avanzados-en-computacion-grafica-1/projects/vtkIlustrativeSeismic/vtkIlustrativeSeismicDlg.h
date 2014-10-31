// vtkIlustrativeSeismicDlg.h : header file
//

#pragma once

// INCLUDES *******************************************************************

#include "vtkMFCWindow.h"
#include <vector>
#include "afxwin.h"
#include "afxcmn.h"

// STRUCTURE DECLARATION ******************************************************

struct HORIZONINFO
{
	bool bPicked;
	bool bVisible;
	
	vtkStructuredPointsReader* pReader;
	vtkDataSetMapper*          pMapper;
	vtkActor*                  pActor;
	vtkColorTransferFunction*  pDepthPalette;
};

struct STRATAINFO
{
	int       nPattern;
	int       nColor;
	vtkActor* pInlineActor;
	vtkActor* pXlineActor;
};

// CLASS DECLARATION **********************************************************

//
// Render dialog
//
class CRenderDlg : public CDialog
{
	public:

		enum { IDD = IDD_VTKILUSTRATIVESEISMIC_DIALOG };

	protected:
	
		HICON m_hIcon;

		vtkMFCWindow*              m_pMFCWindow;
		vtkRenderer*               m_pRenderer;
		vtkStructuredPointsReader* m_pReader;
		vtkVolume*                 m_pVolume;
		vtkVolumeTextureMapper3D*  m_pVolumeMapper;
		vtkActor*                  m_pInlineActor;
		std::vector<STRATAINFO>    m_ilustrativeActors;
		vtkActor*                  m_pXlineActor;
		vtkActor*                  m_pTimeActor;
		std::vector<HORIZONINFO>   m_horizonList;

		vtkColorTransferFunction*  m_pSeismicPalette;

		CSliderCtrl   m_CtrlIlSlider;
		CSliderCtrl   m_CtrlXlSlider;
		CSliderCtrl   m_CtrlTsSlider;
		CSliderCtrl   m_CtrlILOpacitySlider;
		CSliderCtrl   m_CtrlXLOpacitySlider;
		CSliderCtrl   m_CtrlTSOpacitySlider;
		CSliderCtrl   m_CtrlMinXSlider;
		CSliderCtrl   m_CtrlMaxXSlider;
		CSliderCtrl   m_CtrlMinYSlider;
		CSliderCtrl   m_CtrlMaxYSlider;
		CSliderCtrl   m_CtrlMinZSlider;
		CSliderCtrl   m_CtrlMaxZSlider;
		CCheckListBox m_CtrlHorizonList;

		BOOL        m_bShowIl;
		BOOL        m_bShowXl;
		BOOL        m_bShowTs;
		BOOL        m_bShowVolume;

		int         m_nIlSlice;
		int         m_nXlSlice;
		int         m_nTsSlice;
		int         m_pVolumeCrop[6];

	public:

		CRenderDlg(CWnd* pParent = NULL); // standard constructor
		~CRenderDlg();

	protected:

		virtual BOOL OnInitDialog();
		virtual void DoDataExchange(CDataExchange* pDX);

		void ExecutePipeline();
		void UpdateInlineSlice();
		void UpdateXlineSlice();
		void UpdateTimeSlice();
		void UpdateLights();

		void ClearHorizons();

		void      UpdateXlineStrataColumn();
		vtkActor* CreateXlineStrataSection(int nPattern, int nColor, const HORIZONINFO& top, const HORIZONINFO& bottom);

		void      UpdateInlineStrataColumn();
		vtkActor* CreateInlineStrataSection(int nPattern, int nColor, const HORIZONINFO& top, const HORIZONINFO& bottom);

	DECLARE_MESSAGE_MAP()

		afx_msg void    OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void    OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
		afx_msg void    OnBnClickedLoaddata();
		afx_msg void    OnBnClickedLoadhorizon();
		afx_msg void    OnBnClickedCheck();
		afx_msg void    OnNMReleasedcaptureVolCrop(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void    OnNMReleasedcaptureInline(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void    OnNMReleasedcaptureXline(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void    OnNMReleasedcaptureTimeSlice(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void    OnLbnSelchangeHorzlist();
		afx_msg void    OnLbnChkchangeHorzlist();
		afx_msg void    OnNMReleasedcaptureSliderSliceOpacity(NMHDR *pNMHDR, LRESULT *pResult);
};
