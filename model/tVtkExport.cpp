#include "tVtkExport.h"

#include <vtkXMLMultiBlockDataWriter.h>

tVtkExport::tVtkExport(QString fileName, tModel *m) :
    fName(fileName)
{

    data = vtkSmartPointer<vtkMultiBlockDataSet>::New();

    //Create Writer
    //writer = vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
    //writer->SetFileName(fileName.toLocal8Bit().data());
    //test((",,,"+fileName).split(','), 1);
    exportElement(m);
}



tVtkExport::~tVtkExport()
{
    // Finally write it
    //writer->Write();

    vtkSmartPointer<vtkXMLMultiBlockDataWriter> writer = vtkSmartPointer<vtkXMLMultiBlockDataWriter>::New();
    QString ext = writer->GetDefaultFileExtension();
    writer->SetFileName((fName + "." + ext).toLocal8Bit().data() );
    #if VTK_MAJOR_VERSION <= 5
        writer->SetInput(data);
    #else
        writer->SetInputData(data);
    #endif
    writer->Write();
}

void tVtkExport::exportElement(tElement *el)
{
    tSurface* s = dynamic_cast<tSurface*>(el);
    tGroup* g = dynamic_cast<tGroup*>(el);
    if (s) {
        exportSurface(s);
    } else if (g){
        exportGroup(g);
    }
}

void tVtkExport::exportGroup(tGroup *g)
{
    for (int i=0; i<g->nElements(); i++){
        tElement* el = g->element(i);
        exportElement(el);
    }
}

void tVtkExport::exportSurface(tSurface *s)
{
    int nu,nv;
    nu = s->uDiv()*s->uRes();
    nv = s->vDiv()*s->vRes();

    vtkSmartPointer<vtkStructuredGrid> structuredGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();


    // Specify the dimensions of the grid
    structuredGrid->SetDimensions(nu+1,nv+1,1);
    structuredGrid->SetPoints(points);

    for (int v=0; v<=nv; v++){
        for (int u=0; u<=nu; u++){
            tVector x = s->vectorAt(float(u)/float(nu), float(v)/float(nv));
            points->InsertNextPoint(x.x, x.y, x.z);
        }
    }

    int newBlockId = data->GetNumberOfBlocks();
    data->SetBlock(newBlockId,structuredGrid);
//#if VTK_MAJOR_VERSION <= 5
//    writer->SetInput(structuredGrid);
//#else
//    writer->SetInputData(structuredGrid);
//#endif


}


#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkCleanPolyData.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

bool tVtkExport::test(QStringList argv, int argc)
{
    vtkSmartPointer<vtkPolyData> input1 = vtkSmartPointer<vtkPolyData>::New();
      vtkSmartPointer<vtkPolyData> input2 = vtkSmartPointer<vtkPolyData>::New();

      if(argc == 1) //command line arguments not specified
        {
        vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
        sphereSource->SetCenter(5,0,0);
        sphereSource->Update();

        input1->ShallowCopy(sphereSource->GetOutput());

        vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
        coneSource->Update();

        input2->ShallowCopy(coneSource->GetOutput());
        }
      else
      {
        if(argc != 3) {
          std::cout << "argc = " << argc << std::endl;
          std::cout << "Required arguments: File1 File2" << std::endl;
          return EXIT_FAILURE;
        }

        std::string inputFilename1 = argv[1].toStdString();
        std::string inputFilename2 = argv[2].toStdString();
        vtkSmartPointer<vtkXMLPolyDataReader> reader1 = vtkSmartPointer<vtkXMLPolyDataReader>::New();
        reader1->SetFileName(inputFilename1.c_str());
        reader1->Update();
        input1->ShallowCopy(reader1->GetOutput());

        vtkSmartPointer<vtkXMLPolyDataReader> reader2 = vtkSmartPointer<vtkXMLPolyDataReader>::New();
        reader2->SetFileName(inputFilename2.c_str());
        reader2->Update();
        input2->ShallowCopy(reader2->GetOutput());
      }

      //Append the two meshes
      vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    #if VTK_MAJOR_VERSION <= 5
      appendFilter->AddInputConnection(input1->GetProducerPort());
      appendFilter->AddInputConnection(input2->GetProducerPort());
    #else
      appendFilter->AddInputData(input1);
      appendFilter->AddInputData(input2);
    #endif
      appendFilter->Update();

      // Remove any duplicate points.
      vtkSmartPointer<vtkCleanPolyData> cleanFilter = vtkSmartPointer<vtkCleanPolyData>::New();
      cleanFilter->SetInputConnection(appendFilter->GetOutputPort());
      cleanFilter->Update();

      //Create a mapper and actor
      vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      cleanFilter->GetOutputPort();
      mapper->SetInputConnection(cleanFilter->GetOutputPort());

      vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
      actor->SetMapper(mapper);

      //Create a renderer, render window, and interactor
      vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
      vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
      renderWindow->AddRenderer(renderer);
      vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
      renderWindowInteractor->SetRenderWindow(renderWindow);

      //Add the actors to the scene
      renderer->AddActor(actor);
      renderer->SetBackground(.3, .2, .1); // Background color dark red

      //Render and interact
      renderWindow->Render();
      renderWindowInteractor->Start();

      return EXIT_SUCCESS;
}
