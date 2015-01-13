#include "ark_leftPanel.h"
#include "GUIFrame.h"
#include "wx/docmdi.h"
#include "wx/artprov.h"
#include "wx/aui/aui.h"

BEGIN_EVENT_TABLE(ark_leftPanel, wxScrolledWindow)
//	EVT_PAINT  (ark_leftPanel::OnPaint)
	EVT_MOTION (ark_leftPanel::OnMouseMove)
// 	EVT_LEFT_DOWN (ark_leftPanel::OnMouseDown)
// 	EVT_LEFT_UP (ark_leftPanel::OnMouseUp)
END_EVENT_TABLE()

ark_leftPanel::ark_leftPanel(wxWindow *parent)
	:wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
	wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
	,m_frame_owner(NULL)
{
	 	wxAuiToolBar* tb5 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
	 		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_VERTICAL);
	 	tb5->SetToolBitmapSize(wxSize(48,48));
	 	tb5->AddTool(idToolBar1+1, wxT("Test"), wxArtProvider::GetBitmap(wxART_ERROR));
	 	tb5->AddSeparator();
	 	tb5->AddTool(idToolBar1+2, wxT("Test"), wxArtProvider::GetBitmap(wxART_QUESTION));
	 	tb5->AddTool(idToolBar1+3, wxT("Test"), wxArtProvider::GetBitmap(wxART_INFORMATION));
	 	tb5->AddTool(idToolBar1+4, wxT("Test"), wxArtProvider::GetBitmap(wxART_WARNING));
	 	tb5->AddTool(idToolBar1+5, wxT("Test"), wxArtProvider::GetBitmap(wxART_MISSING_IMAGE));
	 	//tb5->SetCustomOverflowItems(prepend_items, append_items);
	 	tb5->Realize();

		SetScrollRate( 10, 10 );
}
ark_leftPanel::~ark_leftPanel()
{

}

void ark_leftPanel::OnDraw(wxDC& dc)
{
	if (this->m_image.IsOk())
	{
		(&dc)->DrawBitmap(wxBitmap(m_image), 50, 50, true /* use mask */);
	}
}

void ark_leftPanel::OnMouseMove( wxMouseEvent &event )
{
// 	wxClientDC dc(this);
// 	PrepareDC(dc);
// 	m_owner->PrepareDC(dc);

	wxPoint pos = event.GetPosition();
// 	long x = dc.DeviceToLogicalX( pos.x );
// 	long y = dc.DeviceToLogicalY( pos.y );
// 	wxString str;
// 	str.Printf( wxT("Current mouse position: %d,%d"), (int)x, (int)y );
// 	m_owner->SetStatusText( str );
}

void ark_leftPanel::LoadPic(wxString path)
{
	this->m_image.LoadFile(path);
	if (this->m_image.IsOk())
	{
		this->SetVirtualSize(this->m_image.GetWidth(),this->m_image.GetHeight());
	}
	Refresh();
}

void ark_leftPanel::SetFrameOwner(wxFrame *owner)
{

}