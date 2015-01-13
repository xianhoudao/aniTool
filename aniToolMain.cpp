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
#include "ark_scrolledWindow.h"
#include "ark_splitterWindow.h"
#include "ark_leftPanel.h"

#include "wx/docview.h"
#include "wx/config.h"

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
	
	wxMenuBar *bar = new wxMenuBar( 0 );
	wxMenu* fileMenu;
	///file menu
	fileMenu = new wxMenu();

	wxMenuItem* menuFileNew = new wxMenuItem(fileMenu, idMenuNew,wxString(wxT("&New")) + wxT('\t') + wxT("Alt+N"),wxT("New file"),wxITEM_NORMAL);
	fileMenu->Append(menuFileNew);

	wxMenuItem* menuFileOpen = new wxMenuItem(fileMenu, idMenuOpen,wxString(wxT("&Open..")) + wxT('\t') + wxT("Alt+O"),wxT("open file"),wxITEM_NORMAL);
	fileMenu->Append(menuFileOpen);

	wxMenuItem* menuFileSave= new wxMenuItem(fileMenu, idMenuSave,wxString(wxT("&Save")) + wxT('\t') + wxT("Alt+S"),wxT("save file"),wxITEM_NORMAL);
	fileMenu->Append(menuFileSave);

	wxMenuItem* menuFileSaveAs = new wxMenuItem(fileMenu, idMenuSaveAs,wxString(wxT("&Save As...")),wxT("save file"),wxITEM_NORMAL);
	fileMenu->Append(menuFileSaveAs);

	fileMenu->AppendSeparator();

	wxMenuItem* menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );

	bar->Append( fileMenu, wxT("&File") );

	//Project
	wxMenu* ProjectMenu;
	ProjectMenu = new wxMenu();

	wxMenuItem* menuSetImage = new wxMenuItem( ProjectMenu, idMenuSetImage, wxString( wxT("&Set Image") ) , wxT("Set Image"), wxITEM_NORMAL );
	ProjectMenu->Append(menuSetImage);
	bar->Append( ProjectMenu, wxT("&Project") );

	///help menu
	wxMenu* helpMenu;
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	bar->Append( helpMenu, wxT("&Help") );

	///////////////////////////

	/*statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );*/
    
	::wxInitAllImageHandlers();

	/*
	wxDocManager *docManager = new wxDocManager;
	new wxDocTemplate(docManager, "Image", "*.png;*.jpg", "", "png;jpg",
		"Image Doc", "Image View",
		CLASSINFO(ark_ImageDocument), CLASSINFO(ark_ImageView));

	wxFrame *frame = new wxDocMDIParentFrame(docManager, NULL, wxID_ANY,
 	 			GetAppDisplayName(),
 	 			wxDefaultPosition,
 	 			wxSize(500, 400),
				wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE);
				
	// A nice touch: a history of files visited. Use this menu.
	docManager->FileHistoryUseMenu(ProjectMenu);
#if wxUSE_CONFIG
	docManager->FileHistoryLoad(*wxConfig::Get());
#endif // wxUSE_CONFIG
	*/
	
	ark_splitterWindow *splitter = new ark_splitterWindow(this);

	// If you use non-zero gravity you must initialize the splitter with its
	// correct initial size, otherwise it will change the sash position by a
	// huge amount when it's resized from its initial default size to its real
	// size when the frame lays it out. This wouldn't be necessary if default
	// zero gravity were used (although it would do no harm neither).
	splitter->SetSize(this->GetClientSize());
	splitter->SetSashGravity(1.0);
	splitter->SetMinimumPaneSize(100);

	m_left = new ark_leftPanel(splitter);
	wxColour color;
	color.Set(16,161,244);
	m_left->SetBackgroundColour(color);
	m_right = new ark_scrolledWindow(splitter);
	m_right->SetBackgroundColour(*wxCYAN);
	splitter->SplitVertically(m_left, m_right, 0);

	this->SetMenuBar(bar);
	this->SetIcon(wxICON(aaaa)); // To Set App Icon

// 	wxAuiToolBar* tb5 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
// 		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_VERTICAL);
// 	tb5->SetToolBitmapSize(wxSize(48,48));
// 	tb5->AddTool(idToolBar1+1, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
// 	tb5->AddSeparator();
// 	tb5->AddTool(idToolBar1+2, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
// 	tb5->AddTool(idToolBar1+3, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
// 	tb5->AddTool(idToolBar1+4, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
// 	tb5->AddTool(idToolBar1+5, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
// 	//tb5->SetCustomOverflowItems(prepend_items, append_items);
// 	tb5->Realize();

	mbar = bar;
	m_splitter = splitter;
// 	m_mgr.AddPane(tb5, wxAuiPaneInfo().
// 		Name(wxT("tool")).Caption(wxT("Pane Caption")).
// 		Left().Position(1));
// 	m_mgr.AddPane(m_splitter,wxAuiPaneInfo().
// 		Name(wxT("tool1")).Caption(wxT("Pane Caption")).
// 		Left().Position(2));
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
	wxFileDialog dialog(this, wxT("Please choose an pic"),
		wxEmptyString, wxEmptyString, wxT("*.png;*.jpg;*.bmp"), wxFD_OPEN);
	if (dialog.ShowModal() == wxID_OK)
	{
		m_left->LoadPic(dialog.GetPath());
	}
}
