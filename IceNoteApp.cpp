/***************************************************************
 * Name:      IceNoteApp.cpp
 * Purpose:   Code for Application Class
 * Author:    T25 ()
 * Created:   2012-06-14
 * Copyright: T25 ()
 * License:
 **************************************************************/

#include "IceNoteApp.h"

//(*AppHeaders
#include "IceNoteMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(IceNoteApp);

bool IceNoteApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	IceNoteFrame* Frame = new IceNoteFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
