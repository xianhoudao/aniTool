#include "include/ark_scrolledWindow.h"

ark_scrolledWindow::ark_scrolledWindow(wxWindow *parent)
:wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                  wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    //ctor
}

ark_scrolledWindow::~ark_scrolledWindow()
{
    //dtor
}
