/***************************************************************
 * Name:      aniToolApp.cpp
 * Purpose:   Code for Application Class
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

#include "aniToolApp.h"
#include "aniToolMain.h"


IMPLEMENT_APP(aniToolApp);

bool aniToolApp::OnInit()
{
	if ( !wxApp::OnInit() )
		return false;

	aniToolFrame *frame = new aniToolFrame(NULL);
	frame->Show(true);

   // wxGetApp();
    return true;
}
