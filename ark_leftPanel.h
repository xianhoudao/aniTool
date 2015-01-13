#pragma once

#include "wx/scrolwin.h"
#include "wx/image.h"

class ark_leftPanel : public wxScrolledWindow
{
public:
	ark_leftPanel(wxWindow *parent);
	virtual ~ark_leftPanel();
public:
	void LoadPic(wxString path);
	void SetFrameOwner(wxFrame *owner);
public:
	virtual void OnDraw(wxDC& dc);
	virtual void OnMouseMove( wxMouseEvent &event );
private:
	wxImage m_image;
	wxFrame *m_frame_owner;
	DECLARE_EVENT_TABLE()
};