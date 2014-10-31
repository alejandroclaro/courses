// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

// VTK Includes
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkLight.h>

#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>

#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkDataSetMapper.h>
#include <vtkStructuredPoints.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkWarpScalar.h>
#include <vtkMergeFilter.h>

#include <vtkStructuredPointsReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeTextureMapper3D.h>
#include <vtkVolumeTextureMapper2D.h>

#include <vtkCallbackCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <vtkDelaunay3D.h>
#include <vtkDelaunay2D.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkContourFilter.h>

#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkTextureMapToPlane.h>
#include <vtkTransformTextureCoords.h>

#include <vtkVertex.h>
#include <vtkLine.h>
#include <vtkQuad.h>
#include <vtkCellArray.h>

#include <vtkBMPReader.h>

#ifdef _DEBUG
	#pragma comment(lib,"vtkCommon.lib")
	#pragma comment(lib,"vtkDICOMParser.lib")
	#pragma comment(lib,"vtkFiltering.lib")
	#pragma comment(lib,"vtkGenericFiltering.lib")
	#pragma comment(lib,"vtkGraphics.lib")
	#pragma comment(lib,"vtkHybrid.lib")
	#pragma comment(lib,"vtkIO.lib")
	#pragma comment(lib,"vtkImaging.lib")	
	#pragma comment(lib,"vtkNetCDF.lib")
	#pragma comment(lib,"vtkRendering.lib")
	#pragma comment(lib,"vtkVolumeRendering.lib")
	#pragma comment(lib,"vtkWidgets.lib")
	#pragma comment(lib,"vtkexoIIc.lib")
	#pragma comment(lib,"vtkexpat.lib")
	#pragma comment(lib,"vtkfreetype.lib")
	#pragma comment(lib,"vtkftgl.lib")
	#pragma comment(lib,"vtkjpeg.lib")
	#pragma comment(lib,"vtkpng.lib")
	#pragma comment(lib,"vtksys.lib")
	#pragma comment(lib,"vtktiff.lib")
	#pragma comment(lib,"vtkzlib.lib")
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
#else // _RELEASE
	#pragma comment(lib,"vtkCommon.lib")
	#pragma comment(lib,"vtkDICOMParser.lib")
	#pragma comment(lib,"vtkFiltering.lib")
	#pragma comment(lib,"vtkGenericFiltering.lib")
	#pragma comment(lib,"vtkGraphics.lib")
	#pragma comment(lib,"vtkHybrid.lib")
	#pragma comment(lib,"vtkIO.lib")
	#pragma comment(lib,"vtkImaging.lib")	
	#pragma comment(lib,"vtkNetCDF.lib")
	#pragma comment(lib,"vtkRendering.lib")
	#pragma comment(lib,"vtkVolumeRendering.lib")
	#pragma comment(lib,"vtkWidgets.lib")
	#pragma comment(lib,"vtkexoIIc.lib")
	#pragma comment(lib,"vtkexpat.lib")
	#pragma comment(lib,"vtkfreetype.lib")
	#pragma comment(lib,"vtkftgl.lib")
	#pragma comment(lib,"vtkjpeg.lib")
	#pragma comment(lib,"vtkpng.lib")
	#pragma comment(lib,"vtksys.lib")
	#pragma comment(lib,"vtktiff.lib")
	#pragma comment(lib,"vtkzlib.lib")
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
#endif
