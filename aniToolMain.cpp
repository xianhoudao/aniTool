/***************************************************************
 * Name:      aniToolMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    chq ()
 * Created:   2014-12-27
 * Copyright: chq ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "aniToolMain.h"
#include "include/ark_scrolledWindow.h"
#include "include/ark_splitterWindow.h"
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


aniToolFrame::aniToolFrame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
    m_splitter = new ark_splitterWindow(this);

    // If you use non-zero gravity you must initialize the splitter with its
    // correct initial size, otherwise it will change the sash position by a
    // huge amount when it's resized from its initial default size to its real
    // size when the frame lays it out. This wouldn't be necessary if default
    // zero gravity were used (although it would do no harm neither).
    m_splitter->SetSize(GetClientSize());
    m_splitter->SetSashGravity(1.0);

    m_left = new ark_scrolledWindow(m_splitter);
    m_left->SetBackgroundColour(*wxCYAN);
    m_right = new ark_scrolledWindow(m_splitter);

    m_splitter->SplitVertically(m_left, m_right, 0);

}

aniToolFrame::~aniToolFrame()
{
}

void aniToolFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void aniToolFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void aniToolFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void aniToolFrame::OnSetImage(wxCommandEvent& event)
{

}
