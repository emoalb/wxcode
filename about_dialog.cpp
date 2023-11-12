#include "about_dialog.h"
#include <iostream>

AboutDialog::AboutDialog(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxSize(400, 400))
{

    rotation=1.0f;
    transX = 0.0f;
    transY = 0.2f;
    transZ = -5.0f;

    sizer = new wxBoxSizer(wxHORIZONTAL);
    glCanvas = new wxGLCanvas(this, wxID_ANY, NULL, wxDefaultPosition, wxSize(300, 300));
    sizer->Add(glCanvas, 1, wxEXPAND | wxALL);
    SetSizer(sizer);
    glContext = new wxGLContext(glCanvas);

   
   
    // Bind events
    Bind(wxEVT_CLOSE_WINDOW, &AboutDialog::OnClose, this);
   
    glCanvas->Bind(wxEVT_PAINT,&AboutDialog::OnOpenGLPaint, this);
    glCanvas->Bind(wxEVT_LEFT_DOWN,&AboutDialog::OnLeftMousePress,this);
    glCanvas->Bind(wxEVT_RIGHT_DOWN,&AboutDialog::OnRightMousePress,this);
    glCanvas->Bind(wxEVT_RIGHT_DOWN,&AboutDialog::OnRightMousePress,this);
    glCanvas->Bind(wxEVT_CHAR,&AboutDialog::OnKeyPress,this);
}
void AboutDialog::OnKeyPress(wxKeyEvent& event){
            switch ( event.GetKeyCode() )
        {
            case WXK_LEFT:
            transX+=0.2f;
            break;
            case WXK_RIGHT:
            transX-=0.2f;
             break;
            case WXK_UP:
            transY+=0.2f;                      
            break;
             case WXK_DOWN:
            transY-=0.2f;                      
            break;
             case WXK_PAGEUP:
            transZ-=0.2f;                      
            break;
             case WXK_PAGEDOWN:
            transZ+=0.2f;                      
            break;
        }
           Refresh();

}
void AboutDialog::OnClose(wxCloseEvent& event) // Correct the event type
{
    std::cout<<"Cleaning"<<std::endl;
  //    event.Skip(true);
      CleanupOpenGL();
      EndModal(0);
}
void AboutDialog::CleanupOpenGL()
{
    if (glContext) {
        glCanvas->SetCurrent(*glContext); // Set the context before cleanup
        // Release any OpenGL resources (e.g., textures, shaders, etc.)
    }
    // Release the OpenGL context
    if (glContext) {
        delete glContext;
        glContext = nullptr;
    }
}
void AboutDialog::OnNativePaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    // Native painting code here
}
void AboutDialog::prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
	
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_ALWAYS); // The Type Of Depth Testing To Do
     glEnable(GL_DITHER);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
    glEnable(GL_COLOR_MATERIAL);
	
    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
    gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
}
int AboutDialog::getWidth()
{
    return GetSize().x;
}
 
int AboutDialog::getHeight()
{
    return GetSize().y;
}
    void AboutDialog::OnLeftMousePress(wxMouseEvent& event) {
       
        event.Skip();
 
       rotation +=5.0f;
        Refresh();
    }
        void AboutDialog::OnRightMousePress(wxMouseEvent& event) {
       
        event.Skip();
 
       rotation -=5.0f;
        Refresh();
    }

void AboutDialog::OnOpenGLPaint(wxPaintEvent& event)
{

    glCanvas->SetCurrent(*glContext);
    prepare3DViewport(0,0,getWidth(), getHeight());
	glClearColor( 0.1f,0.5f,0.0f,0.4f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(0,0,1,1);
    glTranslatef(transX,transY,transZ);  
    glRotatef(rotation, 1.0, 1.0, 1.0);
    glColor4f(1, 0, 0, 1);
    for (int i = 0; i < 6; i++) {   
        glColor3fv(cubeColors[i]);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {        
        glVertex3fv(cubeVertices[i][j]);
     
    }
    glEnd();
    }  
   glFlush();


     glCanvas->SwapBuffers();
}



