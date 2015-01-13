#include "ark_splitterWindow.h"

ark_splitterWindow::ark_splitterWindow(wxWindow *parent)
                : wxSplitterWindow(parent, wxID_ANY,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSP_3D | wxSP_LIVE_UPDATE |
                                   wxCLIP_CHILDREN /* | wxSP_NO_XP_THEME */ )
{
    //ctor
}

ark_splitterWindow::~ark_splitterWindow()
{
    //dtor
}
