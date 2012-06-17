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
//*)
#include "NoteFileHandler.h"

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
        /* deal with all things background*/
        NoteFileHandler *m_fileHandler;

        DECLARE_EVENT_TABLE()
};

#endif // ICENOTEMAIN_H
