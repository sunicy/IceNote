#ifndef NOTEFILEHANDLER_H
#define NOTEFILEHANDLER_H

#include "NoteRelation.h"
#include "NoteItemAbstract.h"
#include "Notetraverser.h"

#include <vector>
#include <map>

#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/filefn.h>
#include <wx/msgdlg.h>
#include <wx/datetime.h>

using namespace std;

/* This is the core class concerning all file-handling of
    IceNote.
    The whole class could be divided into 3 parts:
        1. Building trees
        2. Fetching info
        3. Taking actions

    This class is a singleton. To simplify the programming
    procedure, we just leave it a member variable in Main class.
*/
/* stores a single record from config file */
class NoteRecord
{
    public:
        NoteRecord();
        /* for a notebook */
        NoteRecord(NoteItemType noteItemType, int itemId, int parentId, wxString notebookTitle);
        /* for a note */
        NoteRecord(NoteItemType noteItemType, int itemId, int parentId, const NoteItemAbstract& abstract);

        /* some get info */
        NoteItemType getItemType();
        wxString getItemTitle();/* both for note and notebook */
        int getItemId();
        int getParentId();
        NoteRelation getRelationWithParent(); /* both */
        NoteItemAbstract getAbstract();/* only for notes */
        wxString getNoteFilename(); /* only for notes, returns the filename without FULL PATH */

        /* set info */
        void setItemType(NoteItemType noteItemType);
        void setItemTitle(wxString title); /* ONLY for NOTEBOOK */
        void setItemId(int itemId);
        void setParentId(int parentId);
        void setAbstract(NoteItemAbstract& abstract); /* only for note */

        void setValid(bool valid);
        bool isValid();

    private:
        NoteItemType m_itemType;
        int m_itemId;
        int m_paretnId;
        bool m_valid; /* whether this item is in use */
        NoteItemAbstract m_abstract;
        wxString m_notebookTitle; /* ONLY USED if it is a NOTEBOOK! */
};

/* for output */
wxTextFile& operator<<(wxTextFile& file, NoteRecord& noteRecord);
/* for input */
wxTextFile& operator>>(wxTextFile& file, NoteRecord& noteRecord);

class NoteFileHandler
{
    public:
        NoteFileHandler(wxString docDir);
        ~NoteFileHandler();

    /*
        PART I: Building Trees
        This part helps the outsiders to regard relationships as a relationship-list,
        and to show the item type(directory only or a note) as well.
        And the relationship between each two nodes as a vertice-pair-line,
        e.g, (1, 2) means 1 belongs to 2. The whole procedure is almost
        the same as reading records from a DB. */
        /* restart the ptr of relationship-list */
        void restartRelations();
        /* fetch the next line, true if secc*/
        bool nextRelation(NoteRelation& noteRelation);
        /* Well, well, finally, comes to the end, eeeeeeh?! */
        bool isEof();

    /*
        PART II: Fetching Info */
        /* fill "itemAbstract" with the abstract, and returns true if succ */
        bool getNoteAbstract(int itemId, NoteItemAbstract& itemAbstract);

        /* get the notebook title, specifying the ItemId; returns -1 if failed */
        wxString getItemTitle(int itemId);

        bool setNoteAbstract(int itemId, NoteItemAbstract& itemAbstract);

    /*
        PART III: Taking actions */
        /* try to create a note, specifying its parent's ItemId,
            and returns the new ItemId if succ, and -1 if failed */
        int createNote(int parentId);

        /* try to create a notebook, and returns the new ItemId if succ,
            -1 if failed */
        int createNotebook(wxString notebookTitle, int parentId);

        /* removing
            1.the notebook together with all the notes in it;
            OR 2. just one note which is specified*/
        bool deleteItem(int itemId);

        /* save and open functions, true if succ */
        bool saveNote(int itemId, wxRichTextCtrl& textCtrl);
        bool openNote(int itemId, wxRichTextCtrl& textCtrl);

    protected:
    private:
        /* stores all the records in a linear list */
        vector<NoteRecord> m_noteRecords;
        /* from ItemId to the record! */
        map<int, int> m_itemIdMap;
        wxTextFile m_cfgFile;      /*the file include all the abstract content*/

        int m_currentRelationPos; /* used for "restartRelation" and "nextRelation" */
        int m_autoIncId;           /* the next ItemId */
        wxString m_cfgDir; /* working dir! */

        void loadItemTree();
        void saveItemTree();

        /* delete the item recursively */
        bool _deleteItem(int itemId);
};

#endif // NOTEFILEHANDLER_H
