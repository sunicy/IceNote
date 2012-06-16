/***************************************************************
 * Name:      IceNoteMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    T25 ()
 * Created:   2012-06-14
 * Copyright: T25 ()
 * License:
 **************************************************************/

#include "IceNoteMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(IceNoteFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)



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

//(*IdInit(IceNoteFrame)
const long IceNoteFrame::ID_TREECTRL = wxNewId();
const long IceNoteFrame::ID_RICHTEXTCTRL = wxNewId();
const long IceNoteFrame::ID_SPLITTERWINDOW = wxNewId();
const long IceNoteFrame::idMenuCreateNote = wxNewId();
const long IceNoteFrame::idMenuCreateNotebook = wxNewId();
const long IceNoteFrame::idMenuExport = wxNewId();
const long IceNoteFrame::idMenuImport = wxNewId();
const long IceNoteFrame::idMenuQuit = wxNewId();
const long IceNoteFrame::idMenuUndo = wxNewId();
const long IceNoteFrame::idMenuRedo = wxNewId();
const long IceNoteFrame::idMenuCut = wxNewId();
const long IceNoteFrame::idMenuCopy = wxNewId();
const long IceNoteFrame::idMenuPaste = wxNewId();
const long IceNoteFrame::idMenuSelectAll = wxNewId();
const long IceNoteFrame::idMenuWordCount = wxNewId();
const long IceNoteFrame::idMenuAddPicture = wxNewId();
const long IceNoteFrame::idMenuImportText = wxNewId();
const long IceNoteFrame::idMenuStyle = wxNewId();
const long IceNoteFrame::idMenuAlignLeft = wxNewId();
const long IceNoteFrame::idMenuAlignCenter = wxNewId();
const long IceNoteFrame::idMenuAlignRight = wxNewId();
const long IceNoteFrame::idMenuIncIndent = wxNewId();
const long IceNoteFrame::idMenuDecIndent = wxNewId();
const long IceNoteFrame::ID_MENUITEM1 = wxNewId();
const long IceNoteFrame::idMenuAbout = wxNewId();
const long IceNoteFrame::ID_STATUSBAR1 = wxNewId();
const long IceNoteFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(IceNoteFrame,wxFrame)
    //(*EventTable(IceNoteFrame)
    //*)
END_EVENT_TABLE()

IceNoteFrame::IceNoteFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(IceNoteFrame)
    wxMenu* Menu1;
    wxMenuItem* mnQuit;
    wxMenu* Menu2;
    wxMenuItem* mnAbout;
    wxMenuBar* menuBar;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(935,460));
    listEditSplitter = new wxSplitterWindow(this, ID_SPLITTERWINDOW, wxPoint(200,224), wxDefaultSize, wxSP_3D|wxFULL_REPAINT_ON_RESIZE, _T("ID_SPLITTERWINDOW"));
    listEditSplitter->SetMinimumPaneSize(150);
    //listEditSplitter->SetSashGravity(0.5);
    noteTree = new wxTreeCtrl(listEditSplitter, ID_TREECTRL, wxPoint(87,231), wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL"));
    mainText = new wxRichTextCtrl(listEditSplitter, ID_RICHTEXTCTRL, wxEmptyString, wxPoint(830,175), wxDefaultSize, wxRE_MULTILINE, wxDefaultValidator, _T("ID_RICHTEXTCTRL"));
    	wxRichTextAttr rchtxtAttr_1;
    listEditSplitter->SplitVertically(noteTree, mainText, 100);
    //listEditSplitter->SetSashPosition(200);
    menuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    mnCreateNote = new wxMenuItem(Menu1, idMenuCreateNote, _("Create a note"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mnCreateNote);
    mnCreateNotebook = new wxMenuItem(Menu1, idMenuCreateNotebook, _("Create a notebook"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mnCreateNotebook);
    Menu1->AppendSeparator();
    mnExport = new wxMenuItem(Menu1, idMenuExport, _("Export..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mnExport);
    mnImport = new wxMenuItem(Menu1, idMenuImport, _("Import..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mnImport);
    mnQuit = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(mnQuit);
    menuBar->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    mnUndo = new wxMenuItem(Menu3, idMenuUndo, _("Undo\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnUndo);
    mnRedo = new wxMenuItem(Menu3, idMenuRedo, _("Redo\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnRedo);
    Menu3->AppendSeparator();
    mnCut = new wxMenuItem(Menu3, idMenuCut, _("Cut\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnCut);
    mnCopy = new wxMenuItem(Menu3, idMenuCopy, _("Copy\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnCopy);
    mnPaste = new wxMenuItem(Menu3, idMenuPaste, _("Paste\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnPaste);
    mnSelectAll = new wxMenuItem(Menu3, idMenuSelectAll, _("Select &All\tCtrl+A"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnSelectAll);
    Menu3->AppendSeparator();
    mnWordCount = new wxMenuItem(Menu3, idMenuWordCount, _("Word Count..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnWordCount);
    Menu3->AppendSeparator();
    mnAddPicture = new wxMenuItem(Menu3, idMenuAddPicture, _("Add a picture..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnAddPicture);
    mnImportText = new wxMenuItem(Menu3, idMenuImportText, _("Import text..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnImportText);
    menuBar->Append(Menu3, _("&Edit"));
    Menu4 = new wxMenu();
    mnStyle = new wxMenuItem(Menu4, idMenuStyle, _("&Style..."), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(mnStyle);
    MenuItem17 = new wxMenu();
    mnParaLeft = new wxMenuItem(MenuItem17, idMenuAlignLeft, _("Left"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(mnParaLeft);
    mnParaCenter = new wxMenuItem(MenuItem17, idMenuAlignCenter, _("Center"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(mnParaCenter);
    mnParaRight = new wxMenuItem(MenuItem17, idMenuAlignRight, _("Right"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(mnParaRight);
    MenuItem17->AppendSeparator();
    mnParaIncIndent = new wxMenuItem(MenuItem17, idMenuIncIndent, _("Increse Indent"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(mnParaIncIndent);
    mnParaDecIndent = new wxMenuItem(MenuItem17, idMenuDecIndent, _("Decrease Indent"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(mnParaDecIndent);
    Menu4->Append(ID_MENUITEM1, _("&Paragraph"), MenuItem17, wxEmptyString);
    menuBar->Append(Menu4, _("&Format"));
    Menu2 = new wxMenu();
    mnAbout = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(mnAbout);
    menuBar->Append(Menu2, _("Help"));
    SetMenuBar(menuBar);
    statusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    statusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    statusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(statusBar);

    Connect(idMenuCreateNote,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IceNoteFrame::OnMenuItem3Selected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IceNoteFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IceNoteFrame::OnAbout);
    //*)
}

IceNoteFrame::~IceNoteFrame()
{
    //(*Destroy(IceNoteFrame)
    //*)
}

void IceNoteFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void IceNoteFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void IceNoteFrame::OnClose(wxCloseEvent& event)
{

}

void IceNoteFrame::OnRichTextCtrlPaint(wxPaintEvent& event)
{
}

// Forward command events to the current rich text control, if any
bool IceNoteFrame::ProcessEvent(wxEvent& event)
{
    if (event.IsCommandEvent() && !event.IsKindOf(CLASSINFO(wxChildFocusEvent)))
    {
        // Problem: we can get infinite recursion because the events
        // climb back up to this frame, and repeat.
        // Assume that command events don't cause another command event
        // to be called, so we can rely on inCommand not being overwritten

        static int s_eventType = 0;
        static wxWindowID s_id = 0;

        if (s_id != event.GetId() && s_eventType != event.GetEventType())
        {
            s_eventType = event.GetEventType();
            s_id = event.GetId();

            wxWindow* focusWin = wxFindFocusDescendant(this);
            if (focusWin && focusWin->GetEventHandler()->ProcessEvent(event))
            {
                //s_command = NULL;
                s_eventType = 0;
                s_id = 0;
                return true;
            }

            s_eventType = 0;
            s_id = 0;
        }
        else
        {
            return false;
        }
    }

    return wxFrame::ProcessEvent(event);
}

void IceNoteFrame::OnMenuItem3Selected(wxCommandEvent& event)
{
}
