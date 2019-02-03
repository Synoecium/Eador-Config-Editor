/***************************************************************
 * Name:      EadorConfigEditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Synoecium ()
 * Created:   2016-03-17
 * Copyright: Synoecium ()
 * License:
 **************************************************************/

#include "EadorConfigEditorApp.h"

//(*AppHeaders
#include "EadorConfigEditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EadorConfigEditorApp);

bool EadorConfigEditorApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	EadorConfigEditorFrame* Frame = new EadorConfigEditorFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
