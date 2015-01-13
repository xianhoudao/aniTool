/***************************************************************
 * Name:      aniToolApp.h
 * Purpose:   Defines Application Class
 * Author:    chq ()
 * Created:   2014-12-27
 * Copyright: chq ()
 * License:
 **************************************************************/

#ifndef ANITOOLAPP_H
#define ANITOOLAPP_H

#include <wx/app.h>

class ark_scrolledWindow;

class aniToolApp : public wxApp
{
    public:
        virtual bool OnInit();
public:
private:
};

extern aniToolApp& wxGetApp();

#endif // ANITOOLAPP_H
