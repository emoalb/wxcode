#include "about_dialog.h"
#include <iostream>

AboutDialog::AboutDialog(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxDialog(parent, id, title, wxDefaultPosition, wxSize(400, 400))
{
    sizer = new wxBoxSizer(wxHORIZONTAL);
    glCanvas = new wxGLCanvas(this, wxID_ANY, NULL, wxDefaultPosition, wxSize(300, 300));
    sizer->Add(glCanvas, 1, wxEXPAND | wxALL);
    SetSizer(sizer);
    glContext = new wxGLContext(glCanvas);

    // Bind events
    Bind(wxEVT_CLOSE_WINDOW, &AboutDialog::OnClose, this);
    glCanvas->Bind(wxEVT_PAINT, &AboutDialog::OnOpenGLPaint, this);
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
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
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
void AboutDialog::OnOpenGLPaint(wxPaintEvent& event)
{
   
 
    static GLfloat rotation = 0.0f;
    glRotatef(rotation, 0.0f, 30.0f, 0.0f); // Rotate the scene to control view orientation
    glCanvas->SetCurrent(*glContext);
    prepare3DViewport(0,0,getWidth(), getHeight());
    glLoadIdentity();
	glClearColor( 0.1f,0.5f,0.0f,0.4f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(0,0,1,1);
    glTranslatef(0,0.2,-5);
   // glRotatef(50.0f, 0.0f, 1.0f, 1.0f);
    
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

  rotation += 1.0f;
     glCanvas->SwapBuffers();
}



