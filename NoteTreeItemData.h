#ifndef NOTETREEITEMDATA_H
#define NOTETREEITEMDATA_H

#include <wx/treebase.h>
#include "NoteRelation.h"

class NoteTreeItemData : public wxTreeItemData
{
    public:
        NoteTreeItemData();
        NoteTreeItemData(int itemId, NoteItemType noteItemType);
        int getItemId();
        NoteItemType getItemType();

        virtual ~NoteTreeItemData();
    protected:
    private:
        int m_itemId; /* Item Id of current item */
        NoteItemType m_itemType;

};

#endif // NOTETREEITEMDATA_H
