#ifndef ARK_SPLITTERWINDOW_H
#define ARK_SPLITTERWINDOW_H

#include "wx/splitter.h"

class ark_splitterWindow : public wxSplitterWindow
{
    public:
        ark_splitterWindow(wxWindow *parent);
        virtual ~ark_splitterWindow();
    protected:
    private:
};

#endif // ARK_SPLITTERWINDOW_H
