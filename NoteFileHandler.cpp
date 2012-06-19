#include "NoteFileHandler.h"
#include <wx/filename.h>

#define CONFIG_FILE ".config"

NoteRecord::NoteRecord(NoteItemType noteItemType, int itemId, int parentId, wxString notebookTitle) :
    m_itemType(noteItemType), m_itemId(itemId), m_paretnId(parentId), m_notebookTitle(notebookTitle)
{}

NoteRecord::NoteRecord(NoteItemType noteItemType, int itemId, int parentId, const NoteItemAbstract& abstract) :
    m_itemType(noteItemType), m_itemId(itemId), m_paretnId(parentId),m_abstract(abstract)
{}

NoteItemType NoteRecord::getItemType()
{
    return m_itemType;
}

wxString NoteRecord::getItemTitle()
{
    if (m_itemType == NIT_DIR)
        return m_notebookTitle;
    else
        return m_abstract.getTitle();
}

int NoteRecord::getItemId()
{
    return m_itemId;
}

int NoteRecord::getParentId()
{
    return m_paretnId;
}

NoteRelation NoteRecord::getRelationWithParent()
{
    return NoteRelation(m_itemType, m_itemId, m_paretnId);
}

NoteItemAbstract NoteRecord::getAbstract()
{
    return m_abstract;
}

void NoteRecord::setItemType(NoteItemType noteItemType)
{
    m_itemType = noteItemType;
}

void NoteRecord::setItemTitle(wxString title)
{
    m_notebookTitle = title;
}

void NoteRecord::setItemId(int itemId)
{
    m_itemId = itemId;
}

void NoteRecord::setParentId(int parentId)
{
    m_paretnId = parentId;
}

void NoteRecord::setAbstract(NoteItemAbstract& abstract)
{
    m_abstract = NoteItemAbstract(abstract);
}


void NoteRecord::setValid(bool valid = true)
{
    m_valid = valid;
}

bool NoteRecord::isValid()
{
    return m_valid;
}

/* FOARMAT:
    ...
    ITEM_TYPE
    ITEM_ID
    PARENT_ID
    [NOTEBOOK_TITLE] <-- if notebook
    [
    NOTE_TITLE
    NOTE_TAGS       <-- if note
    NOTE_CREATED_TIME
    NOTE_MODIFIED_TIME
    ]
*/


wxTextFile& operator<<(wxTextFile& file, NoteRecord& noteRecord)
{
    /* Basic common info */
    file.AddLine(wxString::Format(_T("%d"), noteRecord.getItemType()));
    file.AddLine(wxString::Format(_T("%d"), noteRecord.getItemId()));
    file.AddLine(wxString::Format(_T("%d"), noteRecord.getParentId()));

    if (noteRecord.getItemType() == NIT_DIR) /* if a directory, just write the title */
        file.AddLine(noteRecord.getItemTitle());
    else /* note: save the abstract! */
    {
        NoteItemAbstract abstract(noteRecord.getAbstract());
        file.AddLine(abstract.getTitle());
        file.AddLine(abstract.getTags());
        file.AddLine(abstract.getCreatedTime().Format());
        file.AddLine(abstract.getLastModified().Format());
    }
    /* write back! */
    file.Write();
}

wxTextFile& operator>>(wxTextFile& file, NoteRecord& noteRecord)
{
    /* Basic common info */
    noteRecord.setItemType((NoteItemType)wxAtoi(file.GetNextLine()));
    noteRecord.setItemId(wxAtoi(file.GetNextLine()));
    noteRecord.setParentId(wxAtoi(file.GetNextLine()));

    if (noteRecord.getItemType() == NIT_DIR) /* if a directory, just write the title */
        noteRecord.setItemTitle(file.GetNextLine());
    else /* note: save the abstract! */
    {
        NoteItemAbstract abstract;
        abstract.setTitle(file.GetNextLine());
        abstract.setTags(file.GetNextLine());
        wxDateTime dt;
        dt.ParseDateTime(file.GetNextLine());
        abstract.setCreateTime(dt);
        dt.ParseDateTime(file.GetNextLine());
        abstract.setLastModified(dt);
    }
}

NoteFileHandler::NoteFileHandler(wxString docDir) : m_cfgDir(docDir)
{
    restartRelations(); /* reset! */
}

NoteFileHandler::~NoteFileHandler()
{
}

void NoteFileHandler::restartRelations()
{
    m_currentRelationPos = 0; /* goto the 0 */
}

bool NoteFileHandler::nextRelation(NoteRelation& noteRelation)
{

    m_currentRelationPos++;
}

bool NoteFileHandler::isEof()
{
}

bool NoteFileHandler::getNoteAbstract(int itemId, NoteItemAbstract& itemAbstract)
{
}

wxString NoteFileHandler::getItemTitle(int itemId)
{
}

bool NoteFileHandler::setNoteAbstract(int itemId, const NoteItemAbstract& itemAbstract)
{
}

int NoteFileHandler::createNote(int parentId)
{
}

int NoteFileHandler::createNotebook(wxString notebookTitle, int parentId)
{
}

bool NoteFileHandler::deleteItem(int itemId)
{
}

bool NoteFileHandler::saveNote(int itemId, wxRichTextCtrl& textCtrl)
{
}

bool NoteFileHandler::openNote(int itemId, wxRichTextCtrl& textCtrl)
{
}

void NoteFileHandler::loadItemTree()
{
    m_noteRecords.clear();
    m_itemIdMap.clear();
    /* add the root! */
    m_itemIdMap.insert(map<int, int>::value_type(0, -1));
    wxTextFile f(wxString::Format(_T("%s%s"), m_cfgDir, CONFIG_FILE));
    if (wxFile::Exists(f.GetName())) /* if exists, open & parse it */
    {
        f.Open();
        /* parse it! */
        while (!f.Eof())
        {
            NoteRecord record;
            vector<NoteRecord>::iterator it;
            f >> record;
            m_noteRecords.push_back(record);
            it = m_noteRecords.end(); it--;
            m_itemIdMap.insert(map<int, int>::value_type(record.getItemId(), m_noteRecords.size() - 1));
        }
        f.Close();
    }
}

void NoteFileHandler::saveItemTree()
{
    wxTextFile f(wxString::Format(_T("%s%s"), m_cfgDir, CONFIG_FILE));
    f.Create();
    for (vector<NoteRecord>::iterator it = m_noteRecords.begin(); it != m_noteRecords.end(); it++)
        f << *it;
    f.Write();
    f.Close();
}

