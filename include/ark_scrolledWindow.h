#ifndef ARK_SCROLLEDWINDOW_H
#define ARK_SCROLLEDWINDOW_H

#include "wx/scrolwin.h"

class ark_scrolledWindow : public wxScrolledWindow
{
    public:
        ark_scrolledWindow(wxWindow *parent);
        virtual ~ark_scrolledWindow();
    protected:
    private:
};

#endif // ARK_SCROLLEDWINDOW_H
