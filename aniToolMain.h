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
#include "wx/aui/aui.h"

class ark_leftPanel;

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
protected:
	
private:
		wxImage m_image;
		wxMenuBar* mbar;
		wxStatusBar* statusBar;
		 
		wxSplitterWindow* m_splitter;
		ark_leftPanel *m_left;
		ark_scrolledWindow *m_right;

		wxAuiManager m_mgr;
};

#endif // ANITOOLMAIN_H
