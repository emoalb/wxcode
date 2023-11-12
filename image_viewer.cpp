#include <stack>
#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "about_dialog.h"
class ImageViewerFrame : public wxFrame
{


private:
    wxStaticBitmap* imageCtrl;
    std::stack<wxImage> imageStack;
   wxString currentFilePath;

    void ShowAboutDialog(wxCommandEvent& event)
{
    AboutDialog* aboutDialog= new AboutDialog (this, wxID_ANY, wxT("About Image Viewer"));
    aboutDialog->CenterOnParent();
    aboutDialog->ShowModal();
  delete aboutDialog;

}
    void OnOpen(wxCommandEvent& event)
    {
        wxString filepath = wxFileSelector(wxT("Choose an image to open"), wxEmptyString, wxEmptyString, wxEmptyString, wxT("Image files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg"));

        if (!filepath.empty())
        {
            cv::Mat image = cv::imread(std::string(filepath.mb_str()));
            if (!image.empty())
            {
               
                wxBitmap bitmap = wxBitmap( wxImage(image.cols, image.rows, image.data, true));
                imageCtrl->SetBitmap(bitmap);
                wxImage img =   imageCtrl->GetBitmap().ConvertToImage();
                imageStack.push(img);
            }
        }
    }
 void OnSave(wxCommandEvent& event)
{
    if (!imageCtrl->GetBitmap().IsOk())
        return;

    wxFileDialog saveDialog(this, "Save Image", "", "", "BMP files (*.bmp)|*.bmp|JPEG files (*.jpg)|*.jpg|PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString filePath = saveDialog.GetPath();
    wxString fileType = saveDialog.GetWildcard();
    
    wxImage image = imageCtrl->GetBitmap().ConvertToImage();
    if (fileType.Contains("BMP"))
    {
         filePath.append(".bmp");
        image.SaveFile(filePath, wxBITMAP_TYPE_BMP);
    }
    else if (fileType.Contains("JPEG"))
    {
         filePath.append(".jpeg");
        image.SaveFile(filePath, wxBITMAP_TYPE_JPEG);
    }
    else if (fileType.Contains("PNG"))
    {
         filePath.append(".png");
        image.SaveFile(filePath, wxBITMAP_TYPE_PNG);
    }
}
    void OnExit(wxCommandEvent& event)
    {
        Close();
    }

	static const int ID_EFFECT_GRAYSCALE = 101;
    static const int ID_EFFECT_BLUR = 102;
    static const int ID_EFFECT_UNDO = 100;
    static const int ID_ABOUT = 103;
    // Menu event handlers
    void OnGrayscale(wxCommandEvent& event)
    {
        ApplyGrayscaleEffect();
    }

    void OnBlur(wxCommandEvent& event)
    {
        ApplyBlurEffect();
    }
    void UndoLastEffect(wxCommandEvent& event)
    {
    if (imageStack.size() >1) {
        imageStack.pop(); // Remove the current image
        wxImage lastImage = imageStack.top(); // Get the previous image
        wxBitmap bitmap = wxBitmap(lastImage);
        imageCtrl->SetBitmap(bitmap);
    }
    }

    // Image effect functions
    void ApplyGrayscaleEffect()
    {
        if (!imageCtrl->GetBitmap().IsOk())
        return;

           wxImage image = imageCtrl->GetBitmap().ConvertToImage();
             int width = image.GetWidth();
             int height = image.GetHeight();
             imageStack.push(image);
             wxImage grayscaleImage(width, height);

            for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
            wxColour color = image.GetRed(x, y);
            unsigned char grayValue = (color.Red() + color.Green() + color.Blue()) / 3;
            grayscaleImage.SetRGB(x, y, grayValue, grayValue, grayValue);
         }
    }

    wxBitmap bitmap = wxBitmap(grayscaleImage);
    imageCtrl->SetBitmap(bitmap);
          

    // Keep only the last 4 states in the stack
    while (imageStack.size() > 20)
    {
        imageStack.pop();
    }
    }

    void ApplyBlurEffect()
    {
        if (!imageCtrl->GetBitmap().IsOk())
            return;

        wxImage image = imageCtrl->GetBitmap().ConvertToImage();
        imageStack.push(image);
        cv::Mat cvImage = wxImageToCvMat(image);
        cv::GaussianBlur(cvImage, cvImage, cv::Size(5, 5), 0);

        wxBitmap bitmap = wxBitmap(wxImage(cvImage.cols, cvImage.rows, cvImage.data, true));
        imageCtrl->SetBitmap(bitmap);  

    // Keep only the last 4 states in the stack
    while (imageStack.size() > 20)
    {
        imageStack.pop();
    }
    }

    cv::Mat wxImageToCvMat(const wxImage& image)
    {
        wxImage::RGBValue* data =(wxImage::RGBValue*) image.GetData();
        return cv::Mat(image.GetHeight(), image.GetWidth(), CV_8UC3, data);
    }

    public:
    ImageViewerFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
    {
        wxMenu* fileMenu = new wxMenu;
        fileMenu->Append(wxID_OPEN, wxT("Open"));
        fileMenu->Append(wxID_SAVE, wxT("Save"));
        fileMenu->Append(wxID_EXIT, wxT("Exit"));
        wxMenuBar* menuBar = new wxMenuBar;
        menuBar->Append(fileMenu, wxT("File"));
		  wxMenu* effectsMenu = new wxMenu;
        effectsMenu->Append(ID_EFFECT_GRAYSCALE, wxT("Grayscale"));
        effectsMenu->Append(ID_EFFECT_BLUR, wxT("Blur"));
        effectsMenu->Append(ID_EFFECT_UNDO, wxT("Undo"));
        wxMenu* helpMenu = new wxMenu;       
        menuBar->Append(effectsMenu, wxT("Effects"));
         helpMenu->Append(ID_ABOUT, wxT("About"));
        menuBar->Append(helpMenu, wxT("Help"));
        SetMenuBar(menuBar);
       
       

        wxPanel* panel = new wxPanel(this);
        imageCtrl = new wxStaticBitmap(panel, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0);

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(imageCtrl, 1, wxEXPAND);
        panel->SetSizerAndFit(sizer);
        Bind(wxEVT_MENU, &ImageViewerFrame::OnSave, this, wxID_SAVE);
        Bind(wxEVT_MENU, &ImageViewerFrame::OnOpen, this, wxID_OPEN);
        Bind(wxEVT_MENU, &ImageViewerFrame::OnExit, this, wxID_EXIT);
        Bind(wxEVT_MENU, &ImageViewerFrame::OnGrayscale, this, ID_EFFECT_GRAYSCALE);
        Bind(wxEVT_MENU, &ImageViewerFrame::OnBlur, this, ID_EFFECT_BLUR);
        Bind(wxEVT_MENU, &ImageViewerFrame::UndoLastEffect, this, ID_EFFECT_UNDO);
        Bind(wxEVT_MENU, &ImageViewerFrame::ShowAboutDialog, this, ID_ABOUT);
    }
};
//cv::Mat wxImageToCvMat(const wxImage& image)
//{
 //   const unsigned char* data = image.GetData();
 //   int width = image.GetWidth();
  //  int height = image.GetHeight();
  //  cv::Mat cvImage(height, width, CV_8UC3);

 //   for (int y = 0; y < height; y++) {
//       for (int x = 0; x < width; x++) {
 //           int index = (y * width + x) * 3; // RGB values
 //           cvImage.at<cv::Vec3b>(y, x) = cv::Vec3b(data[index + 2], data[index + 1], data[index]);
 //       }
  //  }
//
 //   return cvImage;
//}

class ImageViewerApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        ImageViewerFrame* frame = new ImageViewerFrame(wxT("Image Viewer"));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(ImageViewerApp);

//sudo apt-get install libwxgtk3.0-dev libopencv-dev
//g++ -o image_viewer `wx-config --cppflags` `wx-config --libs` `pkg-config --cflags --libs opencv` image_viewer.cpp
//g++ -o image_viewer `wx-config --cppflags` `wx-config --libs` `pkg-config --cflags --libs opencv` image_viewer.cpp