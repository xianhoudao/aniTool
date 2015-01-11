/***************************************************************
 * Name:      aniToolMain.h
 * Purpose:   Defines Application Frame
 * Author:    chq ()
 * Created:   2014-12-27
 * Copyright: chq ()
 * License:
 **************************************************************/

#ifndef ANITOOLMAIN_H
#define ANITOOLMAIN_H



#include "aniToolApp.h"


#include "GUIFrame.h"
#include "wx/splitter.h"

class aniToolFrame: public GUIFrame
{
    public:
        aniToolFrame(wxFrame *frame);
        ~aniToolFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnSetImage(wxCommandEvent& event);
    private:
        wxSplitterWindow* m_splitter;
        wxWindow *m_left, *m_right;
};

#endif // ANITOOLMAIN_H
