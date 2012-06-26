/***************************************************************
 * Name:      IceNoteMain.h
 * Purpose:   Defines Application Frame
 * Author:    T25 ()
 * Created:   2012-06-14
 * Copyright: T25 ()
 * License:
 **************************************************************/

#ifndef ICENOTEMAIN_H
#define ICENOTEMAIN_H

//(*Headers(IceNoteFrame)
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/toolbar.h>
#include <wx/panel.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/filedlg.h>
//*)
#include "NoteFileHandler.h"

    static const char *Notebook_XPM[] = {
    "16 16 52 1",
    "k c #BFEF92",
    "5 c #FFFFFF",
    "O c #535353",
    "s c #B6E888",
    "j c #B6E88A",
    ": c #81AA5E",
    "u c #9BD173",
    "y c #8AC563",
    "< c #A1DF6C",
    "@ c #B5B5B5",
    "x c #1C2F12",
    "n c #4E8333",
    "4 c #ABE478",
    "3 c #95D167",
    "w c #B3E983",
    "8 c #407B34",
    "$ c #54684A",
    "# c #919191",
    "d c #BDEE8F",
    "1 c #91CE62",
    "- c #5B8645",
    "h c #1B2D11",
    "e c #B6EA87",
    "_ c #A8A8A8",
    "9 c #AAC5A4",
    "+ c #F3F3F3",
    "q c #DBE6D8",
    ", c #75A157",
    "2 c #A6E272",
    "* c #4F4F4F",
    "& c #98DA61",
    "c c #1D3213",
    "r c #B8EC8A",
    "0 c #B1E880",
    "a c #528A35",
    "z c #A2D67B",
    "p c #A7DA7D",
    "i c #BBED8D",
    ". c None",
    "v c #508734",
    "6 c #E0E9DF",
    "t c #ADE281",
    "X c #686868",
    "o c #868686",
    "g c #A8DB80",
    "> c #54953A",
    "f c #59993E",
    "; c #9DDD66",
    "= c #61A43F",
    "7 c #AEE67B",
    "l c #72AD54",
    "b c #57993B",
    "_.XoXOXOXOXOXOX.",
    "_+@+@+@+@+@#@+@.",
    "$&*&*&*&*&*=*&*=",
    "-;:;:;:;:;:>,;:=",
    "=<<<<<<<<<<>1<<=",
    "=2222222222>322=",
    "=4555555554>654=",
    "=7589898957>957=",
    "=055q5q5q50>q50=",
    "=w59898985w>85w=",
    "=e55555555e>65e=",
    "=rtyyyyyytr>utr=",
    "=iiiiiiiiii>pii=",
    "asddddddddsfgdsa",
    "hyjkkkkkkjylzjyx",
    ".cv>>>>>>>>bn>c."
    };
    static const char *Note_XPM[] = {
    "16 16 36 1",
    "t c #BFEF92",
    "> c #FFFFFF",
    "q c #B6E888",
    "r c #B6E88A",
    "= c #81AA5E",
    "8 c #8AC563",
    "- c #A1DF6C",
    "O c #B5B5B5",
    "y c #1C2F12",
    ": c #ABE478",
    "4 c #B3E983",
    "< c #407B34",
    "+ c #54684A",
    "w c #BDEE8F",
    "& c #5B8645",
    "e c #1B2D11",
    "5 c #B6EA87",
    ". c #A8A8A8",
    "1 c #AAC5A4",
    "o c #F3F3F3",
    "3 c #DBE6D8",
    "; c #A6E272",
    "# c #4F4F4F",
    "@ c #98DA61",
    "u c #1D3213",
    "6 c #B8EC8A",
    "2 c #B1E880",
    "0 c #528A35",
    "9 c #BBED8D",
    "_ c None",
    "i c #508734",
    "7 c #ADE281",
    "X c #686868",
    "* c #9DDD66",
    "$ c #61A43F",
    ", c #AEE67B",
    "__._X_X_X_X_X___",
    "__.oOoOoOoOoO___",
    "__+@#@#@#@#@#$__",
    "__&*=*=*=*=*=$__",
    "__$----------$__",
    "__$;;;;;;;;;;$__",
    "__$:>>>>>>>>:$__",
    "__$,><1<1<1>,$__",
    "__$2>>3>3>3>2$__",
    "__$4>1<1<1<>4$__",
    "__$5>>>>>>>>5$__",
    "__$6788888876$__",
    "__$9999999999$__",
    "__0qwwwwwwwwq0__",
    "__e8rttttttr8y__",
    "___ui$$$$$$iu___"
    };

class IceNoteFrame: public wxFrame
{
    public:

        IceNoteFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~IceNoteFrame();

    private:
        bool ProcessEvent(wxEvent& event);

        //(*Handlers(IceNoteFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnRichTextCtrlPaint(wxPaintEvent& event);
        void OnMenuItem3Selected(wxCommandEvent& event);
        void OnnoteTreeBeginDrag(wxTreeEvent& event);
        void OnnoteTreeBeginDrag1(wxTreeEvent& event);

        //*)
        void OnCreateNotebook(wxCommandEvent& event);
        void OnCreateNote(wxCommandEvent& event);

        void OnUpdateBold(wxUpdateUIEvent& event);
        void OnUpdateItalic(wxUpdateUIEvent& event);
        void OnUpdateUnderline(wxUpdateUIEvent& event);
        void OnBold(wxCommandEvent& event);
        void OnItalic(wxCommandEvent& event);
        void OnUnderline(wxCommandEvent& event);

        void OnAlignLeft(wxCommandEvent& event);
        void OnAlignCentre(wxCommandEvent& event);
        void OnAlignRight(wxCommandEvent& event);

        void OnUpdateAlignLeft(wxUpdateUIEvent& event);
        void OnUpdateAlignCentre(wxUpdateUIEvent& event);
        void OnUpdateAlignRight(wxUpdateUIEvent& event);

        void OnDelNote(wxCommandEvent& event);

        void OnSelChanged(wxTreeEvent& event);

        void OnStyleSheet(wxCommandEvent& event);

        void OnUpdateRichTextCtrlEnabled(wxUpdateUIEvent& event);

        void OnAddPicture(wxCommandEvent& event);
        void OnUpdateAddPicture(wxUpdateUIEvent& event);

        /* Something about CLIPBOARD */
        void OnCut(wxCommandEvent& event);
        void OnCopy(wxCommandEvent& event);
        void OnUpdateCutCopy(wxUpdateUIEvent& event);
        void OnPaste(wxCommandEvent& event);
        void OnUpdatePaste(wxUpdateUIEvent& event);

        void OnSelAll(wxCommandEvent& event);

        void loadAndShowAbstract(int itemId);
        void saveAbstract(int itemId);

        void buildNoteTreeFromFileHandler();

        //(*Identifiers(IceNoteFrame)
        static const long ID_TREECTRL;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL4;
        static const long ID_PANEL3;
        static const long ID_RICHTEXTCTRL1;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_SPLITTERWINDOW;
        static const long ID_NEW_NOTEBOOK;
        static const long ID_NEW_NOTE;
        static const long ID_DEL_NOTE;
        static const long ID_EXPORT;
        static const long ID_IMPORT;
        static const long ID_QUIT;
        static const long ID_CUT;
        static const long ID_COPY;
        static const long ID_PASTE;
        static const long ID_SELALL;
        static const long ID_WORD_COUNT;
        static const long ID_ADD_PIC;
        static const long ID_IMPORT_TEXT;
        static const long ID_STYLESHEET;
        static const long ID_TEXT_ALIGNMENT_LEFT;
        static const long ID_TEXT_ALIGNMENT_CENTER;
        static const long ID_TEXT_ALIGNMENT_RIGHT;
        static const long ID_INC_INDENT;
        static const long ID_DEC_INDENT;
        static const long ID_MENUITEM1;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TOOLBARITEM1;
        static const long ID_TOOLBARITEM2;
        static const long ID_TOOLBARITEM7;
        static const long ID_BOLD;
        static const long ID_ITALIC;
        static const long ID_UNDERLINE;
        static const long ID_TOOLBARITEM4;
        static const long ID_TOOLBARITEM5;
        static const long ID_TOOLBARITEM6;
        static const long ID_TOOLBARITEM3;
        static const long ID_TOOLBAR1;
        //*)

        //(*Declarations(IceNoteFrame)
        wxMenuItem* mnCopy;
        wxToolBarToolBase* ToolBarItem4;
        wxMenuItem* mnAddPicture;
        wxToolBarToolBase* ToolBarItem9;
        wxRichTextCtrl* m_richTextCtrl;
        wxMenuItem* mnCut;
        wxToolBarToolBase* ToolBarItem3;
        wxToolBarToolBase* ToolBarItem12;
        wxMenuItem* mnParaCenter;
        wxMenuItem* mnStyle;
        wxTextCtrl* m_edtCreatedTime;
        wxStaticText* StaticText2;
        wxToolBarToolBase* ToolBarItem11;
        wxToolBar* toolBar;
        wxMenu* Menu3;
        wxToolBarToolBase* ToolBarItem10;
        wxTextCtrl* m_edtTitle;
        wxMenuItem* MenuItem1;
        wxMenuItem* mnImport;
        wxMenuItem* mnParaRight;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxMenuItem* mnCreateNote;
        wxMenuItem* mnUndo;
        wxPanel* Panel3;
        wxToolBarToolBase* ToolBarItem6;
        wxTextCtrl* m_edtLastModified;
        wxMenuItem* mnParaLeft;
        wxToolBarToolBase* ToolBarItem1;
        wxMenuItem* mnExport;
        wxMenuItem* mnRedo;
        wxMenuItem* mnParaDecIndent;
        wxMenuItem* mnCreateNotebook;
        wxMenuItem* mnParaIncIndent;
        wxStatusBar* statusBar;
        wxToolBarToolBase* ToolBarItem5;
        wxTreeCtrl* noteTree;
        wxTextCtrl* m_edtTags;
        wxMenuItem* mnPaste;
        wxSplitterWindow* listEditSplitter;
        wxMenuItem* mnWordCount;
        wxToolBarToolBase* ToolBarItem8;
        wxSplitterWindow* SplitterWindow1;
        wxMenuItem* mnImportText;
        wxStaticText* StaticText4;
        wxToolBarToolBase* ToolBarItem2;
        wxMenu* Menu4;
        wxMenuItem* mnSelectAll;
        wxMenu* MenuItem17;
        wxToolBarToolBase* ToolBarItem7;
        //*)

        /* the ItemId of the current note */
        int m_currentNoteItemId; /* 0 if it is root */

        NoteItemAbstract m_currentAbstract;
        /* deal with all things background*/
        NoteFileHandler *m_fileHandler;

        DECLARE_EVENT_TABLE()
};

#endif // ICENOTEMAIN_H
