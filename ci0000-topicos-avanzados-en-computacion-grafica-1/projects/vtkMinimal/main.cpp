#include "project_config.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h> 
#include <vtkRenderWindowInteractor.h> 
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
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

int main(int argc, char** argv[])
{
	// Read the Data File.
	vtkStructuredPointsReader* pReader = vtkStructuredPointsReader::New();
	pReader->SetFileName("seismic.vtk");
	pReader->Update();

	double* pRange = pReader->GetOutput()->GetScalarRange();
	std::cout << pRange[0] << " " << pRange[1] << "\n";

	// Opacity Function
	vtkPiecewiseFunction* pOpacity = vtkPiecewiseFunction::New();
	pOpacity->AddSegment(-10000.0, 0.0, -3000.0, 0.0);
	pOpacity->AddSegment( -3000.0, 0.0,     0.0, 0.0);
	pOpacity->AddSegment(     0.0, 0.0,  1000.0, 0.0);
	pOpacity->AddSegment(  1000.0, 1.0,  3000.0, 1.0);
	pOpacity->AddSegment(  3000.0, 1.0, 10000.0, 1.0);

	// Transfers Function
	vtkColorTransferFunction* pColor = vtkColorTransferFunction::New();
	pColor->AddRGBPoint(-5000.0 , 1.0 , 0.0 , 0.0);
	pColor->AddRGBPoint(   -1.0 , 1.0 , 0.0 , 0.0);
	pColor->AddRGBPoint(    0.0 , 1.0 , 1.0 , 1.0);
	pColor->AddRGBPoint(    1.0 , 0.0 , 0.0 , 1.0);
	pColor->AddRGBPoint( 5000.0 , 0.0 , 0.0 , 1.0);

	// Volume Property (reflection seismic cube)
	vtkVolumeProperty* pProperty = vtkVolumeProperty::New();
	pProperty->SetAmbient(0.5);
	pProperty->SetColor(pColor);
	pProperty->SetScalarOpacity(pOpacity);
	pProperty->SetInterpolationTypeToLinear();
	pProperty->ShadeOn();

	// Volume Mapper
	vtkVolumeTextureMapper3D* pVolumeMapper = vtkVolumeTextureMapper3D::New();
	pVolumeMapper->SetSampleDistance(0.01);
	pVolumeMapper->SetPreferredMethodToFragmentProgram();

	//vtkFixedPointVolumeRayCastMapper* pVolumeMapper = vtkFixedPointVolumeRayCastMapper::New();
	pVolumeMapper->SetInput((vtkImageData*)pReader->GetOutput());
	//pVolumeMapper->SetVolumeRayCastFunction(vtkVolumeRayCastCompositeFunction::New());
	pVolumeMapper->CroppingOn();
	pVolumeMapper->SetCroppingRegionPlanes(0.0, 15.0, 0.0, 25.0, 10.0, 30.0);

	// Volume Object
	vtkVolume* pVolume = vtkVolume::New();
	pVolume->SetMapper(pVolumeMapper);
	pVolume->SetProperty(pProperty);

	// Outline Filter
	vtkOutlineFilter* pOutline = vtkOutlineFilter::New();
	pOutline->SetInput((vtkDataObject*)pReader->GetOutput());

	vtkPolyDataMapper* pOutlineMapper = vtkPolyDataMapper::New();
	pOutlineMapper->SetInput(pOutline->GetOutput());

	vtkActor* pOutlineActor = vtkActor::New();
	pOutlineActor->SetMapper(pOutlineMapper);
	pOutlineActor->GetProperty()->SetColor(1.0, 1.0, 1.0);

	// Add volume to the renderer
	vtkRenderer *pRenderer = vtkRenderer::New();
	pRenderer->AddVolume(pVolume);
	pRenderer->AddActor(pOutlineActor);
	pRenderer->SetBackground(0.1, 0.2, 0.4);

	pRenderer->GetActiveCamera()->Azimuth(20.0);
	pRenderer->GetActiveCamera()->Dolly(0.1);
	pRenderer->GetActiveCamera()->SetPosition(-100, -100, -100);
	pRenderer->ResetCameraClippingRange();

	vtkLight* pLight1 = vtkLight::New();
	pLight1->SetPosition(-500, -500, -500);
	pLight1->SetFocalPoint(0.0, 0.0, 0.0);
	pLight1->SetColor(1.0, 1.0, 1.0);
	pLight1->SetIntensity(0.5);
	pRenderer->AddLight(pLight1);

	vtkLight* pLight2 = vtkLight::New();
	pLight2->SetPosition(500, 500, 500);
	pLight2->SetFocalPoint(0.0, 0.0, 0.0);
	pLight2->SetColor(1.0, 1.0, 1.0);
	pLight2->SetIntensity(0.5);
	pRenderer->AddLight(pLight2);

	// Create a slice cut.
	vtkPlane* pSlicePlane = vtkPlane::New();
	double*   pDataCenter = pReader->GetOutput()->GetCenter();

	pSlicePlane->SetOrigin(pDataCenter[0], pDataCenter[1], pDataCenter[2]);
	pSlicePlane->SetNormal(-1.0, 0.0, 0.0);

	vtkCutter* pSliceCutter = vtkCutter::New();
	pSliceCutter->SetInputConnection(pReader->GetOutputPort());
	pSliceCutter->SetCutFunction(pSlicePlane);
	pSliceCutter->Update();

	vtkDataSetMapper* pSliceMapper = vtkDataSetMapper::New();
	pSliceMapper->SetInput(pSliceCutter->GetOutput());
	pSliceMapper->SetLookupTable(pColor);
	pSliceMapper->SetScalarRange(-3000, 3000);

	vtkActor* pSliceActor = vtkActor::New();
	pSliceActor->SetMapper(pSliceMapper);

	// Add Slice to the renderer
	pRenderer->AddActor(pSliceActor);

	// Load Horizon
	vtkStructuredPointsReader* pHorizonReader = vtkStructuredPointsReader::New();
	pHorizonReader->SetFileName("h1_1644.hor.vtk");
	pHorizonReader->Update();

	vtkImageDataGeometryFilter* pHorizonGeometry = vtkImageDataGeometryFilter::New();
	pHorizonGeometry->SetInput(pHorizonReader->GetOutput());

	vtkWarpScalar* pHorizonWarp = vtkWarpScalar::New();
	pHorizonWarp->SetInput(pHorizonGeometry->GetOutput());
	pHorizonWarp->SetScaleFactor(0.2);

	vtkMergeFilter* pHorizonMerge = vtkMergeFilter::New();
	pHorizonMerge->SetGeometry(pHorizonWarp->GetOutput());
	pHorizonMerge->SetScalars(pHorizonReader->GetOutput());

	vtkDataSetMapper* pHorizonMapper = vtkDataSetMapper::New();
	pHorizonMapper->SetInput(pHorizonMerge->GetOutput());

	vtkActor* pHorizonActor = vtkActor::New();
	pHorizonActor->SetMapper(pHorizonMapper);

	pRenderer->AddActor(pHorizonActor);

	vtkStructuredPointsReader* pHorizonReader2 = vtkStructuredPointsReader::New();
	pHorizonReader2->SetFileName("h3_1646.hor.vtk");
	pHorizonReader2->Update();

	vtkImageDataGeometryFilter* pHorizonGeometry2 = vtkImageDataGeometryFilter::New();
	pHorizonGeometry2->SetInput(pHorizonReader2->GetOutput());

	vtkWarpScalar* pHorizonWarp2 = vtkWarpScalar::New();
	pHorizonWarp2->SetInput(pHorizonGeometry2->GetOutput());
	pHorizonWarp2->SetScaleFactor(0.2);

	vtkMergeFilter* pHorizonMerge2 = vtkMergeFilter::New();
	pHorizonMerge2->SetGeometry(pHorizonWarp2->GetOutput());
	pHorizonMerge2->SetScalars(pHorizonReader2->GetOutput());

	vtkDataSetMapper* pHorizonMapper2 = vtkDataSetMapper::New();
	pHorizonMapper2->SetInput(pHorizonMerge2->GetOutput());

	vtkActor* pHorizonActor2 = vtkActor::New();
	pHorizonActor2->SetMapper(pHorizonMapper2);

	pRenderer->AddActor(pHorizonActor2);

	// Render window
	vtkRenderWindow *pWindow = vtkRenderWindow::New();
	pWindow->AddRenderer(pRenderer);
	pWindow->SetSize(700, 700);

	// Create an interactor and associate it to the render window
	vtkInteractorStyleTrackballCamera* pTrackball = vtkInteractorStyleTrackballCamera::New();
	vtkRenderWindowInteractor *pInteractor = vtkRenderWindowInteractor::New();
	pInteractor->SetRenderWindow(pWindow);
	pInteractor->SetInteractorStyle(pTrackball);

	// Render
	pInteractor->Initialize();
	pInteractor->Start();

	// Release
	pRenderer->Delete();
	pWindow->Delete();
	pTrackball->Delete();
	pInteractor->Delete();
	pReader->Delete();
	pOpacity->Delete();
	pColor->Delete();
	pProperty->Delete();
	pVolumeMapper->Delete();
	pVolume->Delete();

	return 0;
}
