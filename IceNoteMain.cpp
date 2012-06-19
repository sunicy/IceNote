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
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>

//*)

#include "NoteTreeItemData.h"
#include <map>
#include <wx/textdlg.h>
#include <wx/richtext/richtextformatdlg.h>

using namespace std;

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
const long IceNoteFrame::ID_STATICTEXT1 = wxNewId();
const long IceNoteFrame::ID_TEXTCTRL1 = wxNewId();
const long IceNoteFrame::ID_STATICTEXT2 = wxNewId();
const long IceNoteFrame::ID_TEXTCTRL2 = wxNewId();
const long IceNoteFrame::ID_STATICTEXT3 = wxNewId();
const long IceNoteFrame::ID_TEXTCTRL3 = wxNewId();
const long IceNoteFrame::ID_STATICTEXT4 = wxNewId();
const long IceNoteFrame::ID_TEXTCTRL4 = wxNewId();
const long IceNoteFrame::ID_PANEL3 = wxNewId();
const long IceNoteFrame::ID_RICHTEXTCTRL1 = wxNewId();
const long IceNoteFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long IceNoteFrame::ID_SPLITTERWINDOW = wxNewId();
const long IceNoteFrame::ID_NEW_NOTEBOOK = wxNewId();
const long IceNoteFrame::ID_NEW_NOTE = wxNewId();
const long IceNoteFrame::ID_DEL_NOTE = wxNewId();
const long IceNoteFrame::ID_EXPORT = wxNewId();
const long IceNoteFrame::ID_IMPORT = wxNewId();
const long IceNoteFrame::ID_QUIT = wxNewId();
const long IceNoteFrame::ID_CUT = wxNewId();
const long IceNoteFrame::ID_COPY = wxNewId();
const long IceNoteFrame::ID_PASTE = wxNewId();
const long IceNoteFrame::ID_SELALL = wxNewId();
const long IceNoteFrame::ID_WORD_COUNT = wxNewId();
const long IceNoteFrame::ID_ADD_PIC = wxNewId();
const long IceNoteFrame::ID_IMPORT_TEXT = wxNewId();
const long IceNoteFrame::ID_STYLESHEET = wxNewId();
const long IceNoteFrame::ID_TEXT_ALIGNMENT_LEFT = wxNewId();
const long IceNoteFrame::ID_TEXT_ALIGNMENT_CENTER = wxNewId();
const long IceNoteFrame::ID_TEXT_ALIGNMENT_RIGHT = wxNewId();
const long IceNoteFrame::ID_INC_INDENT = wxNewId();
const long IceNoteFrame::ID_DEC_INDENT = wxNewId();
const long IceNoteFrame::ID_MENUITEM1 = wxNewId();
const long IceNoteFrame::idMenuAbout = wxNewId();
const long IceNoteFrame::ID_STATUSBAR1 = wxNewId();
const long IceNoteFrame::ID_BOLD = wxNewId();
const long IceNoteFrame::ID_ITALIC = wxNewId();
const long IceNoteFrame::ID_UNDERLINE = wxNewId();
const long IceNoteFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(IceNoteFrame,wxFrame)
    EVT_MENU(ID_NEW_NOTEBOOK,  IceNoteFrame::OnCreateNotebook)
    EVT_MENU(ID_NEW_NOTE,  IceNoteFrame::OnCreateNote)

    EVT_UPDATE_UI(ID_BOLD,  IceNoteFrame::OnUpdateBold)
    EVT_UPDATE_UI(ID_ITALIC,  IceNoteFrame::OnUpdateItalic)
    EVT_UPDATE_UI(ID_UNDERLINE,  IceNoteFrame::OnUpdateUnderline)
    EVT_MENU(ID_BOLD,  IceNoteFrame::OnBold)
    EVT_MENU(ID_ITALIC,  IceNoteFrame::OnItalic)
    EVT_MENU(ID_UNDERLINE,  IceNoteFrame::OnUnderline)

    EVT_MENU(ID_TEXT_ALIGNMENT_LEFT,  IceNoteFrame::OnAlignLeft)
    EVT_MENU(ID_TEXT_ALIGNMENT_CENTER,  IceNoteFrame::OnAlignCentre)
    EVT_MENU(ID_TEXT_ALIGNMENT_RIGHT,  IceNoteFrame::OnAlignRight)

    EVT_UPDATE_UI(ID_TEXT_ALIGNMENT_LEFT,  IceNoteFrame::OnUpdateAlignLeft)
    EVT_UPDATE_UI(ID_TEXT_ALIGNMENT_CENTER,  IceNoteFrame::OnUpdateAlignCentre)
    EVT_UPDATE_UI(ID_TEXT_ALIGNMENT_RIGHT,  IceNoteFrame::OnUpdateAlignRight)

    EVT_MENU(ID_DEL_NOTE,  IceNoteFrame::OnDelNote)
    EVT_MENU(ID_STYLESHEET,  IceNoteFrame::OnStyleSheet)

    EVT_TREE_SEL_CHANGED(ID_TREECTRL, IceNoteFrame::OnSelChanged)
    //(*EventTable(IceNoteFrame)
    //*)
END_EVENT_TABLE()

#define PROG_TITLE _T("IceNote")
#define RES_DIR "res/"
#define NB_DIR  _T("/notes")

IceNoteFrame::IceNoteFrame(wxWindow* parent,wxWindowID id)
{

    #ifndef _CUR_
        wxFileName::SetCwd("../../");
    #endif
    /* Let's have the FILE_HANDLER! */
    wxString noteDir = wxGetCwd() << NB_DIR;
    m_fileHandler = new NoteFileHandler(noteDir);

    //(*Init[STOP]ialize(IceNoteFrame)
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxMenuItem* mnQuit;
    wxMenu* Menu2;
    wxMenuItem* mnAbout;
    wxMenuBar* menuBar;

    wxImageList* noteImageList = new wxImageList(16, 16, 3);
    noteImageList->Add(wxBitmap(Notebook_XPM));
    noteImageList->Add(wxBitmap(Note_XPM));

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(946,478));
    listEditSplitter = new wxSplitterWindow(this, ID_SPLITTERWINDOW, wxPoint(200,224), wxDefaultSize, wxSP_LIVE_UPDATE|wxFULL_REPAINT_ON_RESIZE, _T("ID_SPLITTERWINDOW"));
    listEditSplitter->SetMinSize(wxSize(100,100));
    listEditSplitter->SetMinimumPaneSize(100);
    listEditSplitter->SetSashGravity(0);
    noteTree = new wxTreeCtrl(listEditSplitter, ID_TREECTRL, wxPoint(87,231), wxDefaultSize, wxTR_TWIST_BUTTONS|wxTR_NO_LINES|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL"));
    noteTree->SetImageList(noteImageList);
    wxTreeItemId noteTree_Item1 = noteTree->AddRoot(_T("Notebooks"), -1, -1, new NoteTreeItemData());
    noteTree->AppendItem(noteTree_Item1, _T("Hello!"), -1, -1, new NoteTreeItemData(10, NIT_DIR));

    SplitterWindow1 = new wxSplitterWindow(listEditSplitter, ID_SPLITTERWINDOW1, wxPoint(890,151), wxDefaultSize, wxNO_BORDER, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(100,100));
    SplitterWindow1->SetMinimumPaneSize(100);
    SplitterWindow1->SetSashGravity(0);
    Panel3 = new wxPanel(SplitterWindow1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->SetMinSize(wxSize(-1,150));
    FlexGridSizer2 = new wxFlexGridSizer(4, 2, 0, 0);
    FlexGridSizer2->AddGrowableCol(1);
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("Title"), wxDefaultPosition, wxSize(64,18), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_edtTitle = new wxTextCtrl(Panel3, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(560,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    m_edtTitle->SetMinSize(wxSize(-1,22));
    m_edtTitle->SetMaxSize(wxSize(-1,22));
    FlexGridSizer2->Add(m_edtTitle, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel3, ID_STATICTEXT2, _("Tags"), wxDefaultPosition, wxSize(64,18), wxALIGN_RIGHT, _T("ID_STATICTEXT2"));
    FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_edtTags = new wxTextCtrl(Panel3, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(560,22), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    m_edtTags->SetMinSize(wxSize(-1,22));
    m_edtTags->SetMaxSize(wxSize(-1,22));
    FlexGridSizer2->Add(m_edtTags, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Created Time"), wxDefaultPosition, wxSize(80,18), wxALIGN_RIGHT, _T("ID_STATICTEXT3"));
    FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_edtCreatedTime = new wxTextCtrl(Panel3, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(560,22), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    FlexGridSizer2->Add(m_edtCreatedTime, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel3, ID_STATICTEXT4, _("Last Modified"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_edtLastModified = new wxTextCtrl(Panel3, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(560,22), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    FlexGridSizer2->Add(m_edtLastModified, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel3);
    FlexGridSizer2->SetSizeHints(Panel3);
    m_richTextCtrl = new wxRichTextCtrl(SplitterWindow1, ID_RICHTEXTCTRL1, wxEmptyString, wxPoint(252,315), wxDefaultSize, wxWANTS_CHARS|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_RICHTEXTCTRL1"));
    	wxRichTextAttr rchtxtAttr_1;
    SplitterWindow1->SplitHorizontally(Panel3, m_richTextCtrl);
    SplitterWindow1->SetSashPosition(100);
    listEditSplitter->SplitVertically(noteTree, SplitterWindow1);
    listEditSplitter->SetSashPosition(200);
    menuBar = new wxMenuBar();
    Menu1 = new wxMenu();
    mnCreateNotebook = new wxMenuItem(Menu1, ID_NEW_NOTEBOOK, _("Create a notebook"), wxEmptyString, wxITEM_NORMAL);
    mnCreateNotebook->SetBitmap(wxBitmap(wxImage(_T(RES_DIR"new-notebook.png"))));
    Menu1->Append(mnCreateNotebook);
    mnCreateNote = new wxMenuItem(Menu1, ID_NEW_NOTE, _("Create a note\tCtrl+N"), wxEmptyString, wxITEM_NORMAL);
    mnCreateNote->SetBitmap(wxBitmap(wxImage(_T(RES_DIR"new-note.png"))));
    Menu1->Append(mnCreateNote);
    MenuItem1 = new wxMenuItem(Menu1, ID_DEL_NOTE, _("Remove Note/Notebook"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    Menu1->AppendSeparator();
    mnExport = new wxMenuItem(Menu1, ID_EXPORT, _("Export..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mnExport);
    mnImport = new wxMenuItem(Menu1, ID_IMPORT, _("Import..."), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(mnImport);
    mnQuit = new wxMenuItem(Menu1, ID_QUIT, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(mnQuit);
    menuBar->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    mnUndo = new wxMenuItem(Menu3, wxID_UNDO, _("Undo\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnUndo);
    mnRedo = new wxMenuItem(Menu3, wxID_REDO, _("Redo\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnRedo);
    Menu3->AppendSeparator();
    mnCut = new wxMenuItem(Menu3, ID_CUT, _("Cut\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnCut);
    mnCopy = new wxMenuItem(Menu3, ID_COPY, _("Copy\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnCopy);
    mnPaste = new wxMenuItem(Menu3, ID_PASTE, _("Paste\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnPaste);
    mnSelectAll = new wxMenuItem(Menu3, ID_SELALL, _("Select &All\tCtrl+A"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnSelectAll);
    Menu3->AppendSeparator();
    mnWordCount = new wxMenuItem(Menu3, ID_WORD_COUNT, _("Word Count..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnWordCount);
    Menu3->AppendSeparator();
    mnAddPicture = new wxMenuItem(Menu3, ID_ADD_PIC, _("Add a picture..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnAddPicture);
    mnImportText = new wxMenuItem(Menu3, ID_IMPORT_TEXT, _("Import text..."), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnImportText);
    menuBar->Append(Menu3, _("&Edit"));
    Menu4 = new wxMenu();
    mnStyle = new wxMenuItem(Menu4, ID_STYLESHEET, _("&Style sheet..."), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(mnStyle);
    MenuItem17 = new wxMenu();
    mnParaLeft = new wxMenuItem(MenuItem17, ID_TEXT_ALIGNMENT_LEFT, _("Left"), wxEmptyString, wxITEM_CHECK);
    MenuItem17->Append(mnParaLeft);
    mnParaCenter = new wxMenuItem(MenuItem17, ID_TEXT_ALIGNMENT_CENTER, _("Center"), wxEmptyString, wxITEM_CHECK);
    MenuItem17->Append(mnParaCenter);
    mnParaRight = new wxMenuItem(MenuItem17, ID_TEXT_ALIGNMENT_RIGHT, _("Right"), wxEmptyString, wxITEM_CHECK);
    MenuItem17->Append(mnParaRight);
    MenuItem17->AppendSeparator();
    mnParaIncIndent = new wxMenuItem(MenuItem17, ID_INC_INDENT, _("Increse Indent"), wxEmptyString, wxITEM_NORMAL);
    MenuItem17->Append(mnParaIncIndent);
    mnParaDecIndent = new wxMenuItem(MenuItem17, ID_DEC_INDENT, _("Decrease Indent"), wxEmptyString, wxITEM_NORMAL);
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
    toolBar = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
    ToolBarItem1 = toolBar->AddTool(ID_NEW_NOTEBOOK, _("Create a notebook"), wxBitmap(wxImage(_T(RES_DIR"new-notebook.png"))), wxNullBitmap, wxITEM_NORMAL, _("Create a notebook"), wxEmptyString);
    ToolBarItem2 = toolBar->AddTool(ID_NEW_NOTE, _("Create a Note"), wxBitmap(wxImage(_T(RES_DIR"new-note.png"))), wxNullBitmap, wxITEM_NORMAL, _("Create a Note"), wxEmptyString);
    ToolBarItem3 = toolBar->AddTool(ID_DEL_NOTE, _("Delete a note"), wxBitmap(wxImage(_T(RES_DIR"delete.png"))), wxNullBitmap, wxITEM_NORMAL, _("Delete a note"), wxEmptyString);
    toolBar->AddSeparator();
    ToolBarItem4 = toolBar->AddTool(wxID_UNDO, _("Undo"), wxBitmap(wxImage(_T(RES_DIR"undo.png"))), wxNullBitmap, wxITEM_NORMAL, _("Undo the last action"), wxEmptyString);
    ToolBarItem5 = toolBar->AddTool(wxID_REDO, _("Redo"), wxBitmap(wxImage(_T(RES_DIR"redo.png"))), wxNullBitmap, wxITEM_NORMAL, _("Redo the last action"), wxEmptyString);
    toolBar->AddSeparator();
    ToolBarItem6 = toolBar->AddTool(ID_BOLD, _("Bold"), wxBitmap(wxImage(_T(RES_DIR"bold.png"))), wxNullBitmap, wxITEM_CHECK, _("Bold"), wxEmptyString);
    ToolBarItem7 = toolBar->AddTool(ID_ITALIC, _("Italic"), wxBitmap(wxImage(_T(RES_DIR"italic.png"))), wxNullBitmap, wxITEM_CHECK, _("Italic"), wxEmptyString);
    ToolBarItem8 = toolBar->AddTool(ID_UNDERLINE, _("Underline"), wxBitmap(wxImage(_T(RES_DIR"underline.png"))), wxNullBitmap, wxITEM_CHECK, _("Underline"), wxEmptyString);
    toolBar->AddSeparator();
    ToolBarItem9 = toolBar->AddTool(ID_TEXT_ALIGNMENT_LEFT, _("Left align"), wxBitmap(wxImage(_T(RES_DIR"Align Left.png"))), wxNullBitmap, wxITEM_CHECK, _("Left alignment"), wxEmptyString);
    ToolBarItem10 = toolBar->AddTool(ID_TEXT_ALIGNMENT_CENTER, _("Center align"), wxBitmap(wxImage(_T(RES_DIR"Align Center.png"))), wxNullBitmap, wxITEM_CHECK, _("Center alignment"), wxEmptyString);
    ToolBarItem11 = toolBar->AddTool(ID_TEXT_ALIGNMENT_RIGHT, _("Right align"), wxBitmap(wxImage(_T(RES_DIR"Align Right.png"))), wxNullBitmap, wxITEM_CHECK, _("Right alignment"), wxEmptyString);
    ToolBarItem12 = toolBar->AddTool(ID_STYLESHEET, _("Style sheet"), wxBitmap(wxImage(_T(RES_DIR"style.png"))), wxNullBitmap, wxITEM_NORMAL, _("Style sheet"), wxEmptyString);
    toolBar->Realize();
    SetToolBar(toolBar);

    Connect(ID_QUIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IceNoteFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&IceNoteFrame::OnAbout);
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&IceNoteFrame::OnClose);
    //[STOP]*)
    m_richTextCtrl->SetFocus();
    //SplitterWindow1->Enable(false);

    /* Bind the OnSelChanged */
    Connect(ID_TREECTRL,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&IceNoteFrame::OnSelChanged);

    buildNoteTreeFromFileHandler();

    wxDir dir(wxGetCwd());
    wxArrayString files;
    wxString t;
    dir.GetFirst(&t, wxEmptyString, wxDIR_DIRS);
    do
    {
        m_richTextCtrl->AppendText(t);
        m_richTextCtrl->AppendText(_T("\n"));
    } while (dir.GetNext(&t));

    SplitterWindow1->Enable(true);
    m_richTextCtrl->SaveFile(_T("d:\\test.xml"));
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
    /* if fun's over, save it! */
    if (m_currentNoteItemId > 0)
    {
        saveAbstract(m_currentNoteItemId);
    }
    delete m_fileHandler;
    event.Veto();
    Destroy();
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

void IceNoteFrame::OnnoteTreeBeginDrag(wxTreeEvent& event)
{
}

void IceNoteFrame::OnnoteTreeBeginDrag1(wxTreeEvent& event)
{
}


void IceNoteFrame::OnCreateNotebook(wxCommandEvent& event)
{
    if (!noteTree->GetSelection().IsOk())
        noteTree->SelectItem(noteTree->GetRootItem());
    wxString name = wxGetTextFromUser(_T("Please enter the name of the notebook:"), PROG_TITLE);
    if (name.IsEmpty())
        return ; /* nothing to record */

    /* where is the parent? */
    wxTreeItemId i = noteTree->GetSelection();
    NoteTreeItemData* parent = (NoteTreeItemData*)noteTree->GetItemData(i);
    if (parent->getItemType() == NIT_NOTE) /* CURRENTLY ONLY ONE LAYER */
    {
        i = noteTree->GetItemParent(i);
        parent = (NoteTreeItemData*)noteTree->GetItemData(i);
    }
    int itemId = m_fileHandler->createNotebook(name, parent->getItemId());
    if (itemId > 0)
    {
        i = noteTree->AppendItem(i, name, 0, 0, new NoteTreeItemData(itemId, NIT_DIR));
        noteTree->SelectItem(i);
        noteTree->SetFocus();
    }
    else
        wxMessageBox(_T("Error occured while creating a notebook."), PROG_TITLE);
}

void IceNoteFrame::OnCreateNote(wxCommandEvent& event)
{
    if (!noteTree->GetSelection().IsOk())
        return; /* nothing chosen! */
    /* where is the parent? */
    wxTreeItemId i = noteTree->GetSelection();
    if (i == noteTree->GetRootItem())
    {
        wxMessageBox(_T("Would you please choose a notebook first?"), PROG_TITLE);
        return;
    }
    NoteTreeItemData* parent = (NoteTreeItemData*)noteTree->GetItemData(i);
    if (parent->getItemType() == NIT_NOTE)
    {
        i = noteTree->GetItemParent(i);
        parent = (NoteTreeItemData*)noteTree->GetItemData(i);
    }
    int itemId = m_fileHandler->createNote(parent->getItemId());
    if (itemId > 0)
    {
        i = noteTree->AppendItem(i, _T("Unnamed note"), 1, 1, new NoteTreeItemData(itemId, NIT_NOTE));
        /* init abstarct and save it! */
        m_currentAbstract = NoteItemAbstract(wxEmptyString, wxEmptyString, wxDateTime::Now(), wxDateTime::Now());
        saveAbstract(itemId);
        noteTree->SelectItem(i);
        noteTree->SetFocus();
    }
    else
        wxMessageBox(_T("Error occured while creating a new note."), PROG_TITLE);
}

void IceNoteFrame::OnUpdateBold(wxUpdateUIEvent& event)
{
    event.Check(m_richTextCtrl->IsSelectionBold());
}

void IceNoteFrame::OnUpdateItalic(wxUpdateUIEvent& event)
{
    event.Check(m_richTextCtrl->IsSelectionItalics());
}

void IceNoteFrame::OnUpdateUnderline(wxUpdateUIEvent& event)
{
    event.Check(m_richTextCtrl->IsSelectionUnderlined());
}

void IceNoteFrame::OnBold(wxCommandEvent& WXUNUSED(event))
{
    m_richTextCtrl->ApplyBoldToSelection();
}

void IceNoteFrame::OnItalic(wxCommandEvent& WXUNUSED(event))
{
    m_richTextCtrl->ApplyItalicToSelection();
}

void IceNoteFrame::OnUnderline(wxCommandEvent& WXUNUSED(event))
{
    m_richTextCtrl->ApplyUnderlineToSelection();
}

void IceNoteFrame::OnAlignLeft(wxCommandEvent& WXUNUSED(event))
{
    m_richTextCtrl->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_LEFT);
}

void IceNoteFrame::OnAlignCentre(wxCommandEvent& WXUNUSED(event))
{
    m_richTextCtrl->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_CENTRE);
}

void IceNoteFrame::OnAlignRight(wxCommandEvent& WXUNUSED(event))
{
    m_richTextCtrl->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_RIGHT);
}

void IceNoteFrame::OnUpdateAlignLeft(wxUpdateUIEvent& event)
{
    event.Check(m_richTextCtrl->IsSelectionAligned(wxTEXT_ALIGNMENT_LEFT));
}

void IceNoteFrame::OnUpdateAlignCentre(wxUpdateUIEvent& event)
{
    event.Check(m_richTextCtrl->IsSelectionAligned(wxTEXT_ALIGNMENT_CENTER));
}

void IceNoteFrame::OnUpdateAlignRight(wxUpdateUIEvent& event)
{
    event.Check(m_richTextCtrl->IsSelectionAligned(wxTEXT_ALIGNMENT_RIGHT));
}

void IceNoteFrame::OnDelNote(wxCommandEvent& WXUNUSED(event))
{
    if (!noteTree->GetSelection().IsOk())
        return; /* nothing chosen! */
    /* if root, oops, sorry sir */
    if (noteTree->GetRootItem() == noteTree->GetSelection())
    {
        wxMessageBox(_T("Sorry, but you cannot remove the notebook set, uninstall IceNote instead please!"), PROG_TITLE);
        return;
    }
    else
    {
        wxTreeItemId i = noteTree->GetSelection();
        NoteTreeItemData *item = (NoteTreeItemData*)(noteTree->GetItemData(i));
        if (wxMessageBox(wxString::Format(_T("Do you really want to remove %s '%s'?"),
                                          (item->getItemType() == NIT_DIR) ? _T("Notebook") : _T("Note"),
                                          m_fileHandler->getItemTitle(item->getItemId())),
                         PROG_TITLE, wxYES_NO) == wxYES)
        {
            wxTreeItemId newSelItem = noteTree->GetNextSibling(i);
            if (!newSelItem.IsOk()) /* if invalid, how about the parent? */
                newSelItem = noteTree->GetItemParent(i);
            //if (((NoteTreeItemData*)(noteTree->GetItemData(newSelItem)))->getItemType() == NIT_DIR)
            m_currentNoteItemId = 0; /* suppose it's root */
            if (m_fileHandler->deleteItem(item->getItemId())) /* if deleted succ */
            {
                /* delete it! */
                noteTree->Delete(i);
                /* move to the next */
                noteTree->SelectItem(newSelItem);
                noteTree->SetFocus();
            }
        }

    }
}

void IceNoteFrame::OnStyleSheet(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    if (m_richTextCtrl->HasSelection())
        range = m_richTextCtrl->GetSelectionRange();
    else
        range = wxRichTextRange(0, m_richTextCtrl->GetLastPosition()+1);

    int pages = wxRICHTEXT_FORMAT_FONT;

    wxRichTextFormattingDialog formatDlg(pages, this);
    formatDlg.GetStyle(m_richTextCtrl, range);

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(m_richTextCtrl, range, wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_OPTIMIZE|wxRICHTEXT_SETSTYLE_CHARACTERS_ONLY);
    }
}

void IceNoteFrame::OnSelChanged(wxTreeEvent& event)
{
    wxTreeItemId i = event.GetItem();
    NoteTreeItemData *item = (NoteTreeItemData*)noteTree->GetItemData(i);
    /* if it is a note, save the past one and load the new one */
    if (item->getItemType() == NIT_NOTE)
    {
        if (m_currentNoteItemId == item->getItemId()) /* if not changed */
            return;
        /* STEP1: Save the past one */
        if (m_currentNoteItemId > 0) /* if the prev is a note */
        {
            saveAbstract(m_currentNoteItemId);
            m_fileHandler->saveNote(m_currentNoteItemId, *m_richTextCtrl);
        }
        /* STEP2: Set and load the new one */
        m_currentNoteItemId = item->getItemId();
        m_fileHandler->openNote(m_currentNoteItemId, *m_richTextCtrl);
        loadAndShowAbstract(m_currentNoteItemId);
    }

    SplitterWindow1->Enable(m_currentNoteItemId != 0);
    if (m_currentNoteItemId == 0)
        loadAndShowAbstract(0);
}

void IceNoteFrame::loadAndShowAbstract(int itemId)
{
    if (itemId > 0)
    {
        m_fileHandler->getNoteAbstract(itemId, m_currentAbstract);
        m_edtTitle->SetValue(m_currentAbstract.getTitle());
        m_edtTags->SetValue(m_currentAbstract.getTags());
        m_edtCreatedTime->SetValue(m_currentAbstract.getCreatedTime().Format());
        m_edtLastModified->SetValue(m_currentAbstract.getLastModified().Format());
    }
    else
    {
        m_edtTitle->SetValue("");
        m_edtTags->SetValue("");
        m_edtCreatedTime->SetValue("");
        m_edtLastModified->SetValue("");
    }
}

void IceNoteFrame::saveAbstract(int itemId)
{
    if (m_edtTitle->GetValue().IsEmpty())
        m_edtTitle->SetValue(_T("Unnamed Note"));

    wxDateTime lastModifiedTime = wxDateTime::Now();
    m_edtLastModified->SetValue(lastModifiedTime.Format());
    NoteItemAbstract abstract(m_edtTitle->GetValue(),
                              m_edtTags->GetValue(),
                              m_currentAbstract.getCreatedTime(),
                              lastModifiedTime);
    m_currentAbstract = abstract;
    m_fileHandler->setNoteAbstract(itemId, m_currentAbstract);
}


void IceNoteFrame::buildNoteTreeFromFileHandler()
{
    map<int, wxTreeItemId> items; /* NoteItemId < -- > wxTreeItemId */
    /* back to blank! */
    noteTree->DeleteAllItems();
    /* add root */
    noteTree->AddRoot("Notebooks", -1, -1, new NoteTreeItemData());
    items.insert(map<int, wxTreeItemId>::value_type(0, noteTree->GetRootItem()));

    m_fileHandler->restartRelations();
    /* read it! */
    while (!m_fileHandler->isEof())
    {
        NoteRelation noteRelation;
        m_fileHandler->nextRelation(noteRelation); /* of course successful !!*/
        //wxMessageBox(wxString::Format("%d  %d",noteRelation.getParentId(),noteRelation.getChildId()),"hello re");
        map<int, wxTreeItemId>::iterator it = items.find(noteRelation.getParentId());
        if (it != items.end()) /* if we have found the parent */
        {
            int imageIndex = (noteRelation.getChildItemType() == NIT_DIR) ? 0 : 1;
            /* add it into the treeCtrl */
            wxTreeItemId item = noteTree->AppendItem(it->second, m_fileHandler->getItemTitle(noteRelation.getChildId()), imageIndex, imageIndex,
                                new NoteTreeItemData(noteRelation.getChildId(), noteRelation.getChildItemType()));
            if (noteRelation.getChildItemType() == NIT_DIR) /* add it! */
            {
                /* add it into the MAP ! */
                items.insert(map<int, wxTreeItemId>::value_type(noteRelation.getChildId(), item));
            }
        }
    }
}
