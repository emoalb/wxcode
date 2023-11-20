#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H
#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <wx/glcanvas.h>

class AboutDialog : public wxDialog
{
public:
    AboutDialog(wxWindow* parent, wxWindowID id, const wxString& title);

private:
wxTimer *m_timer;
 GLfloat rotation,transX,transY,transZ;
   const GLfloat light0_pos[4]   = { -50.0f, 50.0f, 0.0f, 0.0f};
   const GLfloat light0_color[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
    void OnClose(wxCloseEvent& event); 
    void OnOpenGLPaint(wxPaintEvent& event);
    void OnLeftMousePress(wxMouseEvent& event);
    void OnRightMousePress(wxMouseEvent& event);
    void OnKeyPress(wxKeyEvent& event);
    void OnNativePaint(wxPaintEvent& event);
    int getHeight();
    void OnTimer(wxTimerEvent& timer);
    int getWidth();
    void prepare3DViewport
    (int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
    static const int ID_TIMER = 500;
    void CleanupOpenGL();
    wxGLCanvas* glCanvas;
    wxBoxSizer* sizer;
    wxGLContext* glContext;
};

#endif