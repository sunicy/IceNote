#include "NoteRelation.h"

NoteRelation::NoteRelation()
{
    m_childItemType = NIT_DIR;
    m_childId = 0;
    m_parentId = 0;
}

NoteRelation::~NoteRelation()
{
    //dtor
}

NoteRelation::NoteRelation(NoteItemType childItemType, int childId, int parentId)
{
    m_childItemType = childItemType;
    m_childId = childId;
    m_parentId = parentId;
}

int NoteRelation::getParentId()
{
    return m_parentId;
}

int NoteRelation::getChildId()
{
    return m_childId;
}

NoteItemType NoteRelation::getChildItemType()
{
    return m_childItemType;
}
