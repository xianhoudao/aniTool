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

class wxSizeReportCtrl : public wxControl
{
public:

	wxSizeReportCtrl(wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		wxAuiManager* mgr = NULL)
		: wxControl(parent, id, pos, size, wxNO_BORDER)
	{
		m_mgr = mgr;
	}

private:

	void OnPaint(wxPaintEvent& WXUNUSED(evt))
	{
		wxPaintDC dc(this);
		wxSize size = GetClientSize();
		wxString s;
		int h, w, height;

		s.Printf(wxT("Size: %d x %d"), size.x, size.y);

		dc.SetFont(*wxNORMAL_FONT);
		dc.GetTextExtent(s, &w, &height);
		height += 3;
		dc.SetBrush(*wxWHITE_BRUSH);
		dc.SetPen(*wxWHITE_PEN);
		dc.DrawRectangle(0, 0, size.x, size.y);
		dc.SetPen(*wxLIGHT_GREY_PEN);
		dc.DrawLine(0, 0, size.x, size.y);
		dc.DrawLine(0, size.y, size.x, 0);
		dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2));

		if (m_mgr)
		{
			wxAuiPaneInfo pi = m_mgr->GetPane(this);

			s.Printf(wxT("Layer: %d"), pi.dock_layer);
			dc.GetTextExtent(s, &w, &h);
			dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*1));

			s.Printf(wxT("Dock: %d Row: %d"), pi.dock_direction, pi.dock_row);
			dc.GetTextExtent(s, &w, &h);
			dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*2));

			s.Printf(wxT("Position: %d"), pi.dock_pos);
			dc.GetTextExtent(s, &w, &h);
			dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*3));

			s.Printf(wxT("Proportion: %d"), pi.dock_proportion);
			dc.GetTextExtent(s, &w, &h);
			dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*4));
		}
	}

	void OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
	{
		// intentionally empty
	}

	void OnSize(wxSizeEvent& WXUNUSED(evt))
	{
		Refresh();
	}
private:

	wxAuiManager* m_mgr;

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(wxSizeReportCtrl, wxControl)
	EVT_PAINT(wxSizeReportCtrl::OnPaint)
	EVT_SIZE(wxSizeReportCtrl::OnSize)
	EVT_ERASE_BACKGROUND(wxSizeReportCtrl::OnEraseBackground)
END_EVENT_TABLE()

aniToolFrame::aniToolFrame(wxFrame *frame)
    : GUIFrame(frame)
{
	
	m_mgr.SetManagedWindow(this);

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

	//tile
	wxMenu* tileMenu;
	tileMenu = new wxMenu();
	wxMenu*zoom = new wxMenu();
	zoom->Append(idMenuZoomIn,"zoom in");
	zoom->Append(idMenuZoomOut,"zoom out");
	zoom->Append(idMenuZoomBack,"zoom 1:1");
	tileMenu->AppendSubMenu(zoom,wxT("&zoom"));

	bar->Append(tileMenu,wxT("&tile"));

	///help menu
	wxMenu* helpMenu;
	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );
	bar->Append( helpMenu, wxT("&Help") );

	///////////////////////////

	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY ); 
	::wxInitAllImageHandlers();

	
	
	wxAuiToolBar *tbLeft = CreateLeftToolBar();

	m_mgr.AddPane(tbLeft, wxAuiPaneInfo().
		Name(wxT("tbLeft")).Caption(wxT("Left toolbar")).
		ToolbarPane().Left().
		GripperTop());
		
	wxAuiToolBar *tbTop = CreateTopToolBar();
	m_mgr.AddPane(tbTop, wxAuiPaneInfo().
		Name(wxT("tbTop")).Caption(wxT("top toolbar")).
		ToolbarPane().Top());

	wxAuiToolBar *tbRight = CreateRightToolBar();
	m_mgr.AddPane(tbRight, wxAuiPaneInfo().
		Name(wxT("tbRight")).Caption(wxT("top toolbar")).
		ToolbarPane().Right());

	ark_splitterWindow *m_splitter = CreateSplitterWindow();
	m_mgr.AddPane(m_splitter, wxAuiPaneInfo().
		Name(wxT("splitter")).Caption(wxT("m_splitter")).
		CenterPane().
		CloseButton(true).MaximizeButton(true));


	this->SetMenuBar(bar);
	this->SetIcon(wxICON(aaaa)); // To Set App Icon
	m_mgr.Update();
	mbar = bar;
}

aniToolFrame::~aniToolFrame()
{
	m_mgr.UnInit();
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

void aniToolFrame::OnZoomIn( wxCommandEvent& event )
{
	if (this->m_left)
	{
		this->m_left->ZoomIn();
	}
}
void aniToolFrame::OnZoomOut( wxCommandEvent& event )
{
	if (this->m_left)
	{
		this->m_left->ZoomOut();
	}
}
void aniToolFrame::OnZoomBack( wxCommandEvent& event )
{
	if (this->m_left)
	{
		this->m_left->ZoomBack();
	}
}

//////////////////////////////////////////////////////////////////////////
//private

wxAuiToolBar *aniToolFrame::CreateLeftToolBar()
{
	wxAuiToolBar* tb5 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_VERTICAL);
	tb5->SetToolBitmapSize(wxSize(48,48));
	wxImage img;
	img.LoadFile("Kombine_toolbar_045.png");
	tb5->AddTool(idMenuZoomIn, wxT("Test"), wxBitmap(img));
	tb5->AddSeparator();
	img.LoadFile("Kombine_toolbar_044.png");
	tb5->AddTool(idMenuZoomOut, wxT("Test"),  wxBitmap(img));
	//tb5->SetCustomOverflowItems(prepend_items, append_items);
	tb5->Realize();

	return tb5;
}

wxAuiToolBar *aniToolFrame::CreateTopToolBar()
{
	wxAuiToolBar* tb = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	tb->SetToolBitmapSize(wxSize(48,48));
	wxImage img;
	img.LoadFile("Kombine_toolbar_045.png");
	tb->AddTool(idMenuZoomIn, wxT("Test"), wxBitmap(img));
	tb->AddSeparator();
	img.LoadFile("Kombine_toolbar_044.png");
	tb->AddTool(idMenuZoomOut, wxT("Test"),  wxBitmap(img));
	//tb5->SetCustomOverflowItems(prepend_items, append_items);
	tb->Realize();

	return tb;
}
wxAuiToolBar *aniToolFrame::CreateRightToolBar()
{
	wxAuiToolBar* tb = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_VERTICAL);
	tb->SetToolBitmapSize(wxSize(48,48));
	wxImage img;
	img.LoadFile("Kombine_toolbar_045.png");
	tb->AddTool(idMenuZoomIn, wxT("Test"), wxBitmap(img));
	tb->AddSeparator();
	img.LoadFile("Kombine_toolbar_044.png");
	tb->AddTool(idMenuZoomOut, wxT("Test"),  wxBitmap(img));
	//tb5->SetCustomOverflowItems(prepend_items, append_items);
	tb->Realize();

	return tb;
}
wxSizeReportCtrl* aniToolFrame::CreateSizeReportCtrl(int width, int height)
{
	wxSizeReportCtrl* ctrl = new wxSizeReportCtrl(this, wxID_ANY,
		wxDefaultPosition,
		wxSize(width, height), &m_mgr);
	return ctrl;
}

ark_splitterWindow *aniToolFrame::CreateSplitterWindow()
{
	ark_splitterWindow *splitter = new ark_splitterWindow(this);
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
	m_left->SetFrameOwner(this);

	return splitter;
}