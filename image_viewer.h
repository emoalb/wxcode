#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H
#include <stack>
#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
class ImageViewerFrame : public wxFrame
{
private:
    wxStaticBitmap* imageCtrl;
    std::stack<wxImage> imageStack;
    wxString currentFilePath;
    void ShowAboutDialog(wxCommandEvent& event);
    cv::Mat wxImageToCvMat(const wxImage& image);
    void OnExit(wxCommandEvent& event);
    void OnBlur(wxCommandEvent& event);
    void UndoLastEffect(wxCommandEvent& event);
    void ApplyBlurEffect();
    void ApplyGrayscaleEffect();
     void OnGrayscale(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    public:
    ImageViewerFrame(const wxString& title) ;
};
#endif