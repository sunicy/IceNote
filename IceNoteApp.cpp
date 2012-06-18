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
#include <wx/richtext/richtextbuffer.h>
#include <wx/richtext/richtextxml.h>

IMPLEMENT_APP(IceNoteApp);

bool IceNoteApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);
    if ( wxsOK )
    {
    	IceNoteFrame* Frame = new IceNoteFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)

    return wxsOK;

}
