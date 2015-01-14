#include "ark_leftPanel.h"
#include "GUIFrame.h"
#include "wx/docmdi.h"
#include "wx/artprov.h"
#include "wx/aui/aui.h"

BEGIN_EVENT_TABLE(ark_leftPanel, wxScrolledWindow)
//	EVT_PAINT  (ark_leftPanel::OnPaint)
	EVT_MOTION (ark_leftPanel::OnMouseMove)
 	EVT_LEFT_DOWN (ark_leftPanel::OnMouseDown)
 	EVT_LEFT_UP (ark_leftPanel::OnMouseUp)
END_EVENT_TABLE()

ark_leftPanel::ark_leftPanel(wxWindow *parent)
	:wxScrolledWindow(parent, wxID_ANY, wxPoint(0,0), wxSize(200,200),
	wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
	,m_frame_owner(NULL)
{
		SetScrollRate( 10, 10 );
		m_scale = 1.0f;
		m_img_pos = wxPoint(50,50);
		m_show_img_rect = false;
		m_rubberBand = false;
}
ark_leftPanel::~ark_leftPanel()
{

}

void ark_leftPanel::OnDraw(wxDC& dc)
{
	dc.SetUserScale(m_scale,m_scale);
	if (this->m_image.IsOk())
	{
		(&dc)->DrawBitmap(wxBitmap(m_image), m_img_pos.x, m_img_pos.y, true /* use mask */);

		if (m_show_img_rect == true)
		{
			dc.SetPen( wxPen( *wxRED, 2 ) );
			dc.SetBrush( *wxTRANSPARENT_BRUSH );
			dc.DrawRectangle(m_img_pos.x, m_img_pos.y, m_image.GetWidth(), m_image.GetHeight());
		}
	}
}

void ark_leftPanel::OnMouseMove( wxMouseEvent &event )
{
 	wxClientDC dc(this);
 	PrepareDC(dc);
 	if(m_frame_owner)m_frame_owner->PrepareDC(dc);

	wxPoint pos = event.GetPosition();
 	long x = dc.DeviceToLogicalX( pos.x );
 	long y = dc.DeviceToLogicalY( pos.y );
 	wxString str;
 	str.Printf( wxT("Current mouse position: %d,%d"), (int)x, (int)y );
 	if(m_frame_owner)m_frame_owner->SetStatusText( str );

	if (m_image.IsOk())
	{
		wxRect rect(m_img_pos.x*m_scale,m_img_pos.y*m_scale,m_image.GetWidth()*m_scale,m_image.GetHeight()*m_scale);
		if (rect.Contains(wxPoint(x,y)) && m_show_img_rect == false)
		{
			m_show_img_rect = true;
			Refresh();
		}else if(!rect.Contains(wxPoint(x,y)) && m_show_img_rect == true)
		{
			m_show_img_rect = false;
			Refresh();
		}
	}

	if ( m_rubberBand )
	{
		int x,y, xx, yy ;
		event.GetPosition(&x,&y);
		CalcUnscrolledPosition( x, y, &xx, &yy );
		m_currentpoint = wxPoint( xx , yy ) ;
		wxRect newrect ( m_anchorpoint , m_currentpoint ) ;

		wxClientDC dc( this ) ;
		PrepareDC( dc ) ;

		wxDCOverlay overlaydc( m_overlay, &dc );
		overlaydc.Clear();
#ifdef __WXMAC__
		dc.SetPen( *wxGREY_PEN );
		dc.SetBrush( wxColour( 192,192,192,64 ) );
#else
		dc.SetPen( wxPen( *wxRED, 2 ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );
#endif
		dc.DrawRectangle( newrect );

		
	}
}

void ark_leftPanel::OnMouseDown( wxMouseEvent &event )
{
	int x,y,xx,yy ;
	event.GetPosition(&x,&y);
	CalcUnscrolledPosition( x, y, &xx, &yy );
	m_anchorpoint = wxPoint( xx , yy ) ;
	m_currentpoint = m_anchorpoint ;
	m_rubberBand = true ;
	CaptureMouse() ;
}
void ark_leftPanel::OnMouseUp( wxMouseEvent &event )
{
	if ( m_rubberBand )
	{
		ReleaseMouse();
		{
			wxClientDC dc( this );
			PrepareDC( dc );
			wxDCOverlay overlaydc( m_overlay, &dc );
			overlaydc.Clear();
		}
		m_overlay.Reset();
		m_rubberBand = false;

		wxPoint endpoint = CalcUnscrolledPosition(event.GetPosition());

		// Don't pop up the message box if nothing was actually selected.
		if ( endpoint != m_anchorpoint )
		{
			wxLogMessage("Selected rectangle from (%d, %d) to (%d, %d)",
				m_anchorpoint.x, m_anchorpoint.y,
				endpoint.x, endpoint.y);
		}
	}
}
void ark_leftPanel::LoadPic(wxString path)
{
	this->m_image.LoadFile(path);
	m_scale = 1.0f;
	_updateVirtualSize();
	Refresh();
}

void ark_leftPanel::SetFrameOwner(wxFrame *owner)
{
	m_frame_owner = owner;
}

void ark_leftPanel::ZoomIn()
{
	m_scale -= 0.1f;
	m_scale = m_scale < 1?1:m_scale;
	_updateVirtualSize();
	Refresh();
}
void ark_leftPanel::ZoomOut()
{
	m_scale += 0.1f;
	m_scale = m_scale > 3?3:m_scale;
	_updateVirtualSize();
	Refresh();
}
void ark_leftPanel::ZoomBack()
{
	m_scale = 1.0f;
	_updateVirtualSize();
	Refresh();
}

void ark_leftPanel::_updateVirtualSize()
{
	if (this->m_image.IsOk())
	{
		this->SetVirtualSize(this->m_image.GetWidth()* m_scale,this->m_image.GetHeight()*m_scale);
	}
}