#include "NoteItemAbstract.h"

NoteItemAbstract::NoteItemAbstract()
{
    //ctor
}

NoteItemAbstract::~NoteItemAbstract()
{
    //dtor
}

NoteItemAbstract::NoteItemAbstract(wxString title, wxString tags, wxDateTime createdTime, wxDateTime lastModified)
{
    m_title = title;
    m_tags = tags;
    m_createdTime = createdTime;
    m_lastModified = lastModified;
}

wxString NoteItemAbstract::getTitle()
{
    return m_title;
}

wxString NoteItemAbstract::getTags()
{
    return m_tags;
}

wxDateTime NoteItemAbstract::getCreatedTime()
{
    return m_createdTime;
}

wxDateTime NoteItemAbstract::getLastModified()
{
    return m_lastModified;
}

