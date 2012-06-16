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
#include <wx/menu.h>
#include <wx/splitter.h>
#include <wx/toolbar.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

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
        //*)

        //(*Identifiers(IceNoteFrame)
        static const long ID_TREECTRL;
        static const long ID_RICHTEXTCTRL;
        static const long ID_SPLITTERWINDOW;
        static const long idMenuCreateNote;
        static const long idMenuCreateNotebook;
        static const long idMenuExport;
        static const long idMenuImport;
        static const long idMenuQuit;
        static const long idMenuUndo;
        static const long idMenuRedo;
        static const long idMenuCut;
        static const long idMenuCopy;
        static const long idMenuPaste;
        static const long idMenuSelectAll;
        static const long idMenuWordCount;
        static const long idMenuAddPicture;
        static const long idMenuImportText;
        static const long idMenuStyle;
        static const long idMenuAlignLeft;
        static const long idMenuAlignCenter;
        static const long idMenuAlignRight;
        static const long idMenuIncIndent;
        static const long idMenuDecIndent;
        static const long ID_MENUITEM1;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TOOLBAR1;
        //*)

        //(*Declarations(IceNoteFrame)
        wxMenuItem* mnCopy;
        wxRichTextCtrl* mainText;
        wxMenuItem* mnAddPicture;
        wxMenuItem* mnCut;
        wxMenuItem* mnParaCenter;
        wxMenuItem* mnStyle;
        wxToolBar* toolBar;
        wxMenu* Menu3;
        wxMenuItem* mnImport;
        wxMenuItem* mnParaRight;
        wxMenuItem* mnCreateNote;
        wxMenuItem* mnUndo;
        wxMenuItem* mnParaLeft;
        wxMenuItem* mnExport;
        wxMenuItem* mnRedo;
        wxMenuItem* mnParaDecIndent;
        wxMenuItem* mnCreateNotebook;
        wxMenuItem* mnParaIncIndent;
        wxStatusBar* statusBar;
        wxTreeCtrl* noteTree;
        wxMenuItem* mnPaste;
        wxSplitterWindow* listEditSplitter;
        wxMenuItem* mnWordCount;
        wxMenuItem* mnImportText;
        wxMenu* Menu4;
        wxMenuItem* mnSelectAll;
        wxMenu* MenuItem17;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ICENOTEMAIN_H
