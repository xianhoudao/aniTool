#include "ark_scrolledWindow.h"
#include "wx/docview.h"
#include "wx/image.h"
ark_scrolledWindow::ark_scrolledWindow(wxWindow *parent)
:wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                  wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    //ctor
	SetScrollRate( 10, 10 );
}

ark_scrolledWindow::~ark_scrolledWindow()
{
    //dtor
}


