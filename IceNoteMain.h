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
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class IceNoteFrame: public wxFrame
{
    public:

        IceNoteFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~IceNoteFrame();

    private:

        //(*Handlers(IceNoteFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnRichTextCtrlPaint(wxPaintEvent& event);
        //*)

        //(*Identifiers(IceNoteFrame)
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
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem5;
        wxToolBar* toolBar;
        wxMenu* Menu3;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem15;
        wxMenuItem* MenuItem22;
        wxMenuItem* MenuItem13;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem20;
        wxMenuItem* MenuItem6;
        wxStatusBar* statusBar;
        wxMenuItem* MenuItem21;
        wxMenuItem* MenuItem16;
        wxMenuItem* MenuItem9;
        wxMenuItem* MenuItem18;
        wxMenu* Menu4;
        wxMenuItem* MenuItem19;
        wxMenu* MenuItem17;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ICENOTEMAIN_H
