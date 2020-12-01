#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageDifference.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>

int main(int, char *[])
{
    for (int i = 1; i < 19; ++i){
        std::string path = "/Users/aramirez/Documents/SciViz/Proyecto/COL Forest Change/b_" + std::to_string(2000 + i) + ".1080.png";
        // Read the image
        vtkSmartPointer<vtkPNGReader> source1 = vtkSmartPointer<vtkPNGReader>::New();
        source1->SetFileName(path.c_str());
        source1->Update();

        std::string path2 = "/Users/aramirez/Documents/SciViz/Proyecto/COL Forest Change/b_" + std::to_string(2000 + i + 1) + ".1080.png";
        // Read the image
        vtkSmartPointer<vtkPNGReader> source2 = vtkSmartPointer<vtkPNGReader>::New();
        source2->SetFileName(path2.c_str());
        source2->Update();


        vtkSmartPointer<vtkImageData> image1 = source1->GetOutput();
        vtkSmartPointer<vtkImageData> image2 = source2->GetOutput();
        int* dims = image1->GetDimensions();
        for (int z=0; z<dims[2]; z++)
        {
            for (int y=0; y<dims[1]; y++)
            {
                for (int x=0; x<dims[0]; x++)
                {
                    // zero is the component, add another loop if you have more
                    // than one component
                    double v = image1->GetScalarComponentAsDouble(x,y,z,0);
                    double v2 = image2->GetScalarComponentAsDouble(x,y,z,0);
                    image1->SetScalarComponentFromDouble(x, y, z, 0, v - v2);
                }
            }
        }


        std::string fileName = "diff_" + std::to_string(2000 + i + 1) + "-" + std::to_string(2000 + i) + ".1080.png";
        vtkSmartPointer<vtkPNGWriter> jWriter = vtkSmartPointer<vtkPNGWriter>::New();
        jWriter->SetFileName(("/Users/aramirez/Documents/SciViz/Proyecto/COL Forest Change/" + fileName).c_str());
        jWriter->SetInputData(image1);
        jWriter->Write();

        cout << "Image " + i << std::endl;
    }

    

 
  return EXIT_SUCCESS;
}
