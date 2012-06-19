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

wxString NoteItemAbstract::getTitle()const
{
    return m_title;
}

wxString NoteItemAbstract::getTags()const
{
    return m_tags;
}

wxDateTime NoteItemAbstract::getCreatedTime()const
{
    return m_createdTime;
}

wxDateTime NoteItemAbstract::getLastModified()const
{
    return m_lastModified;
}

void NoteItemAbstract::setTitile(wxString title)
{
    m_title = title;
}

void NoteItemAbstract::setTags(wxString tags)
{
    m_tags = tags;
}

void NoteItemAbstract::setCreateTime(wxDateTime time)
{
    m_createdTime = time;
}

void NoteItemAbstract::setLastModified(wxDateTime time)
{
    m_lastModified = time;
}

void NoteItemAbstract::setTitle(wxString title)
{
    m_title = title;
}

