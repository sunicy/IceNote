#include "NoteFileHandler.h"

#include <wx/msgdlg.h>

NoteFileHandler::NoteFileHandler(wxString docPath) : m_relationPos(0), m_relationCount(18)
{
    //ctor
}

NoteFileHandler::~NoteFileHandler()
{
    //dtor
}

void NoteFileHandler::restartRelations()
{
}

bool NoteFileHandler::nextRelation(NoteRelation& noteRelation)
{
    if (isEof())
        return false;
    if (m_relationPos % 3 == 0) /* NOTEBOOK */
    {
        NoteRelation r(NIT_DIR, m_relationPos + 1, 0);
        noteRelation = r;
    }
    else
    {
        NoteRelation r(NIT_DIR, m_relationPos + 1, 0);
        noteRelation = NoteRelation(NIT_NOTE, m_relationPos + 1, m_relationPos + 1 - m_relationPos % 3);
    }
    m_relationPos++;
    return true;
}

bool NoteFileHandler::isEof()
{
    return (m_relationPos >= 20);
}

bool NoteFileHandler::getNoteAbstract(int itemId, NoteItemAbstract& itemAbstract)
{
    itemAbstract = NoteItemAbstract(getItemTitle(itemId), _T("Hello"), wxDateTime::Now(), wxDateTime::Now());
    return true;
}

bool NoteFileHandler::setNoteAbstract(int itemId, const NoteItemAbstract& itemAbstract)
{
    return true;
}


wxString NoteFileHandler::getNotebookTitle(int itemId)
{
    return _T("");
}

wxString NoteFileHandler::getItemTitle(int itemId)
{
    /*
        NOTEBOOK
        |----NOTE
        |----NOTE
        NOTEBOOK
        |----NOTE
        ...
    */
    if (itemId % 3 == 1) /* NOTEBOOK */
        return wxString::Format("Notebook %d", (itemId + 2) / 3);
    else
        return wxString::Format("Note %d", itemId - (itemId + 2) / 3);
}

int NoteFileHandler::createNote(int parentId)
{
    return ++m_relationCount;
}

int NoteFileHandler::createNotebook(wxString notebookTitle)
{
    return ++m_relationCount;
}

bool NoteFileHandler::deleteItem(int itemId)
{
    return true;
}

bool NoteFileHandler::saveNote(int itemId, wxRichTextCtrl& textCtrl)
{
    //wxMessageBox(wxString::Format(_T("%d saved"), itemId), _T(""));
}

bool NoteFileHandler::openNote(int itemId, wxRichTextCtrl& textCtrl)
{
    //wxMessageBox(wxString::Format(_T("%d opened"), itemId), _T(""));
}
