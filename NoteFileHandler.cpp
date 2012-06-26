#include "NoteFileHandler.h"
#include <wx/filename.h>
#include <vector>

using namespace std;

#define CONFIG_FILE ".config"

NoteRecord::NoteRecord(NoteItemType noteItemType, int itemId, int parentId, wxString notebookTitle) :
    m_itemType(noteItemType), m_itemId(itemId), m_paretnId(parentId), m_notebookTitle(notebookTitle), m_valid(true)
{
}

NoteRecord::NoteRecord(NoteItemType noteItemType, int itemId, int parentId, const NoteItemAbstract& abstract) :
    m_itemType(noteItemType), m_itemId(itemId), m_paretnId(parentId),m_abstract(abstract), m_valid(true)
{
}
NoteRecord::NoteRecord() : m_valid(true)
{
}

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

wxString NoteRecord::getNoteFilename()
{
    if (m_itemType == NIT_NOTE)
        return wxString::Format(_T("icenote_%d"), m_itemId);
    else
        return wxEmptyString;
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
    NEXT_ITEMID
    ...
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
        NoteItemAbstract abstract = noteRecord.getAbstract();
        file.AddLine(abstract.getTitle());
        file.AddLine(abstract.getTags());
        file.AddLine(abstract.getCreatedTime().Format());
        file.AddLine(abstract.getLastModified().Format());
    }
    /* write back! */
    file.Write();
    return file;
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
        noteRecord.setAbstract(abstract);
    }
    return file;
}

NoteFileHandler::NoteFileHandler(wxString docDir) : m_cfgDir(docDir)
{
    loadItemTree();
    restartRelations(); /* reset! */
}

NoteFileHandler::~NoteFileHandler()
{
    saveItemTree();
}

void NoteFileHandler::restartRelations()
{
    m_currentRelationPos = 0; /* goto the 0 */
}

bool NoteFileHandler::nextRelation(NoteRelation& noteRelation)
{
    for (; m_currentRelationPos < m_noteRecords.size(); m_currentRelationPos++)
        if (m_noteRecords[m_currentRelationPos].isValid()) /* skip all invalid nodes! */
        {
            noteRelation = m_noteRecords[m_currentRelationPos].getRelationWithParent();
            m_currentRelationPos++;
            return true; /* YES! */
        }
    return false; /* end of records! */
}

bool NoteFileHandler::isEof()
{
    return m_currentRelationPos >= m_noteRecords.size();
}

bool NoteFileHandler::getNoteAbstract(int itemId, NoteItemAbstract& itemAbstract)
{
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end()) /* if not found! */
        return false;
    if (m_noteRecords[it->second].getItemType() == NIT_DIR)
        return false; /* notebooks don't have abstracts */
    itemAbstract = m_noteRecords[it->second].getAbstract();
    return true;
}

wxString NoteFileHandler::getItemTitle(int itemId)
{
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end()) /* if not found! */
        return wxEmptyString;
    return m_noteRecords[it->second].getItemTitle();
}

bool NoteFileHandler::setNoteAbstract(int itemId, NoteItemAbstract& itemAbstract)
{
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end()) /* if not found! */
        return false;
    m_noteRecords[it->second].setAbstract(itemAbstract);
    //saveItemTree();
}

int NoteFileHandler::createNote(int parentId)
{
    map<int, int>::iterator it = m_itemIdMap.find(parentId);
    if (it == m_itemIdMap.end() || m_noteRecords[it->second].getItemType() != NIT_DIR)
        return -1; /* invalid! */
    NoteRecord r;
    r.setParentId(parentId);
    r.setItemId(m_autoIncId);
    r.setItemType(NIT_NOTE);
    /* add it into vector and MAP! */
    m_noteRecords.push_back(r);
    m_itemIdMap.insert(map<int, int>::value_type(r.getItemId(), m_noteRecords.size() - 1));
    m_autoIncId++;
    //saveItemTree(); /* save it ! */
    return m_autoIncId - 1;
}

int NoteFileHandler::createNotebook(wxString notebookTitle, int parentId)
{
    map<int, int>::iterator it = m_itemIdMap.find(parentId);
    if (it == m_itemIdMap.end() || m_noteRecords[it->second].getItemType() != NIT_DIR)
        return -1; /* invalid! */
    NoteRecord r;
    r.setParentId(parentId);
    r.setItemId(m_autoIncId);
    r.setItemType(NIT_DIR);
    r.setItemTitle(notebookTitle);
    /* add it into vector and MAP! */
    m_noteRecords.push_back(r);
    m_itemIdMap.insert(map<int, int>::value_type(r.getItemId(), m_noteRecords.size() - 1));
    m_autoIncId++;
    //saveItemTree(); /* save it! */
    return m_autoIncId - 1;
}

bool NoteFileHandler::deleteItem(int itemId)
{
    bool f = _deleteItem(itemId);
    //saveItemTree();
    return f;
}

/* if a note, delete it; otherwise delete all sub-nodes */
bool NoteFileHandler::_deleteItem(int itemId)
{
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end())
        return false; /* invalid! */
    /* mark itself as invalid */
    m_noteRecords[it->second].setValid(false);

    /* well, directory? let's recursively handle it! */
    if (m_noteRecords[it->second].getItemType() == NIT_DIR)
    {
        for (int i = it->second + 1; i < m_noteRecords.size(); i++)
            if (m_noteRecords[i].getParentId() == itemId) /* if is a child */
                deleteItem(m_noteRecords[i].getItemId());
    }

    /* if it is the last element in vector, delete it right now */
    if (it->second == m_noteRecords.size() - 1)
        m_noteRecords.erase(m_noteRecords.end() - 1);
    /* remove itself from the map */
    m_itemIdMap.erase(it);
    return true;
}

bool NoteFileHandler::saveNote(int itemId, wxRichTextCtrl& textCtrl)
{
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end())
        return false; /* invalid! */
    textCtrl.SaveFile(wxString::Format(_T("%s/%s"), m_cfgDir, m_noteRecords[it->second].getNoteFilename()), wxRICHTEXT_TYPE_XML);
    return true;
}

bool NoteFileHandler::openNote(int itemId, wxRichTextCtrl& textCtrl)
{
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end())
        return false; /* invalid! */
    if (wxFile::Exists(wxString::Format(_T("%s/%s"), m_cfgDir, m_noteRecords[it->second].getNoteFilename())))
        textCtrl.LoadFile(wxString::Format(_T("%s/%s"), m_cfgDir, m_noteRecords[it->second].getNoteFilename()), wxRICHTEXT_TYPE_XML);
    else
        textCtrl.Clear();
    return true;
}

void NoteFileHandler::loadItemTree()
{
    m_noteRecords.clear();
    m_itemIdMap.clear();
    /* add the root! */
    m_itemIdMap.insert(map<int, int>::value_type(0, 0));
    NoteRecord r(NIT_DIR, 0, -1, _T(""));
    m_noteRecords.push_back(r);
    wxTextFile f(wxString::Format(_T("%s/%s"), m_cfgDir, CONFIG_FILE));
    m_autoIncId = 1; /* never be ZERO! cuz root = zero */

    if (wxFile::Exists(f.GetName())) /* if exists, open & parse it */
    {
        f.Open();
        //f.GetFirstLine();
        /* parse it! */
        m_autoIncId = wxAtoi(f.GetFirstLine());

        while (!f.Eof())
        {
            if (f.GetNextLine() == wxEmptyString)
                break; /* empty line! */
            else
                f.GetPrevLine();
            NoteRecord record;
            vector<NoteRecord>::iterator it;
            f >> record;
            //wxMessageBox(record.getItemTitle(), _T("!"));
            m_noteRecords.push_back(record);
            it = m_noteRecords.end(); it--;
            m_itemIdMap.insert(map<int, int>::value_type(record.getItemId(), m_noteRecords.size() - 1));
        }
        f.Close();
    }
}

void NoteFileHandler::saveItemTree()
{
    wxTextFile f(wxString::Format(_T("%s/%s"), m_cfgDir, CONFIG_FILE));
    f.Create();
    f.AddLine(wxString::Format(_T("%d"), m_autoIncId));
    /* skip the ROOT! */
    for (vector<NoteRecord>::iterator it = m_noteRecords.begin() + 1; it != m_noteRecords.end(); it++)
        if (it->isValid()) /* ignore all invalid nodes! */
            f << *it;
    f.Write();
    f.Close();
}

