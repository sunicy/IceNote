#ifndef NOTEFILEHANDLER_H
#define NOTEFILEHANDLER_H

#include "NoteRelation.h"
#include "NoteItemAbstract.h"
#include "Notetraverser.h"
#include<fstream>
#include<vector>
#include<wx/dir.h>
#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/filefn.h>
using std::vector;

/* This is the core class concerning all file-handling of
    IceNote.
    The whole class could be divided into 3 parts:
        1. Building trees
        2. Fetching info
        3. Taking actions

    This class is a singleton. To simplify the programming
    procedure, we just leave it a member variable in Main class.
*/
class listnode
{
    public:

    listnode(int itemID,int parentID,int abseek,wxString path,NoteItemType type)
    {
        this->itemID = itemID;
        this->parentID = parentID;
        this->abseek = abseek;
        this->path = path;
        this->type = type;
    }
    listnode(const listnode& node)
    {

    }

        int itemID;
        int parentID;
        int abseek;
        wxString path;
        NoteItemType type;
};

WX_DECLARE_OBJARRAY(listnode,nodearray);
WX_DECLARE_OBJARRAY(NoteRelation,relationarray);

class NoteFileHandler
{
    public:
        NoteFileHandler(wxString docDir);
        virtual ~NoteFileHandler();

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
        wxString getNotebookTitle(int itemId);
        wxString getItemTitle(int itemId);

        bool setNoteAbstract(int itemId, const NoteItemAbstract& itemAbstract);

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

        /**/
        void init_tree(listnode& t);
        int get_abstract(listnode& r,NoteItemAbstract& itemabs);
        int get_title(listnode& r,wxString& abstr);
        void remove_dir(int itemid);
        void count_line(int itemid,int& lines);
        //void insert_abstract(listnode& r);

    protected:
    private:
        //wxDIR default_dir;
        vector<listnode> tree;
        vector<NoteRelation> relation;
        wxTextFile abfile;      /*the file include all the abstract content*/
        int abseek;       /*global var for the seek in abfile*/
        int current_re_id;  /*the id of the relation we get*/
        int id;     /*auto increase*/
};

#endif // NOTEFILEHANDLER_H
