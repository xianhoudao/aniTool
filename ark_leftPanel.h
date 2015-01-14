#pragma once

#include "wx/scrolwin.h"
#include "wx/image.h"
#include "wx/overlay.h"

class wxPoint;
class wxOverlay;

class ark_leftPanel : public wxScrolledWindow
{
public:
	ark_leftPanel(wxWindow *parent);
	virtual ~ark_leftPanel();
public:
	void LoadPic(wxString path);
	void SetFrameOwner(wxFrame *owner);
	void ZoomIn();
	void ZoomOut();
	void ZoomBack();
private:
	void _updateVirtualSize();
public:
	virtual void OnDraw(wxDC& dc);
	virtual void OnMouseMove( wxMouseEvent &event );
	virtual void OnMouseDown( wxMouseEvent &event );
	virtual void OnMouseUp( wxMouseEvent &event );
private:
	float m_scale;
	wxImage m_image;
	wxFrame *m_frame_owner;
	wxPoint m_img_pos;
	bool m_show_img_rect;
	wxPoint m_anchorpoint;
	wxPoint m_currentpoint;
	bool m_rubberBand;
	wxOverlay    m_overlay;

	DECLARE_EVENT_TABLE()
};