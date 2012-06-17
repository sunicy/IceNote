#include "NoteTreeItemData.h"

NoteTreeItemData::NoteTreeItemData()
{
    m_itemId = 0; /* It's a root! */
    m_itemType = NIT_DIR;
}
NoteTreeItemData::NoteTreeItemData(int itemId, NoteItemType noteItemType)
{
    m_itemId = itemId;
    m_itemType = noteItemType;
}

int NoteTreeItemData::getItemId()
{
    return m_itemId;
}

NoteItemType NoteTreeItemData::getItemType()
{
    return m_itemType;
}

NoteTreeItemData::~NoteTreeItemData()
{
    //dtor
}
