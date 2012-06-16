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
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* menuBar;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(935,460));
    menuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuCreateNote, _("Create a note"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, idMenuCreateNotebook, _("Create a notebook"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    Menu1->AppendSeparator();
    MenuItem5 = new wxMenuItem(Menu1, idMenuExport, _("Export..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu1, idMenuImport, _("Import..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    menuBar->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem7 = new wxMenuItem(Menu3, idMenuUndo, _("Undo\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu3, idMenuRedo, _("Redo\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    Menu3->AppendSeparator();
    MenuItem9 = new wxMenuItem(Menu3, idMenuCut, _("Cut\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu3, idMenuCopy, _("Copy\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem10);
    MenuItem11 = new wxMenuItem(Menu3, idMenuPaste, _("Paste\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(Menu3, idMenuSelectAll, _("Select &All\tCtrl+A"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem12);
    Menu3->AppendSeparator();
    MenuItem13 = new wxMenuItem(Menu3, idMenuWordCount, _("Word Count..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem13);
    Menu3->AppendSeparator();
    MenuItem14 = new wxMenuItem(Menu3, idMenuAddPicture, _("Add a picture..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(Menu3, idMenuImportText, _("Import text..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem15);
    menuBar->Append(Menu3, _("&Edit"));
    Menu4 = new wxMenu();
    MenuItem16 = new wxMenuItem(Menu4, idMenuStyle, _("&Style..."), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem16);
    MenuItem17 = new wxMenu();
    MenuItem18 = new wxMenuItem(MenuItem17, idMenuAlignLeft, _("Left"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(MenuItem18);
    MenuItem19 = new wxMenuItem(MenuItem17, idMenuAlignCenter, _("Center"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(MenuItem19);
    MenuItem20 = new wxMenuItem(MenuItem17, idMenuAlignRight, _("Right"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(MenuItem20);
    MenuItem17->AppendSeparator();
    MenuItem21 = new wxMenuItem(MenuItem17, idMenuIncIndent, _("Increse Indent"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(MenuItem21);
    MenuItem22 = new wxMenuItem(MenuItem17, idMenuDecIndent, _("Decrease Indent"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(MenuItem22);
    Menu4->Append(ID_MENUITEM1, _("&Paragraph"), MenuItem17, wxEmptyString);
    menuBar->Append(Menu4, _("&Format"));
    Menu2 = new wxMenu();

    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    menuBar->Append(Menu2, _("Help"));
    SetMenuBar(menuBar);
    statusBar = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    statusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    statusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(statusBar);

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
