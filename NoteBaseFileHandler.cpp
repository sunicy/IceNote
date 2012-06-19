#include "NoteFileHandler.h"
#include <wx/filename.h>
#include <vector>

using namespace std;


#define CONFIG_FILE ".config"
<<<<<<< HEAD:NoteBaseFileHandler.cpp
NoteFileHandler::NoteFileHandler(wxString docDir):abfile(wxString::Format("%s\\%s", docDir, CONFIG_FILE))
{
    //ctor
    id = 0;
    abseek = 0;
    current_re_id = 0;
    //wxSetWorkingDirectory("##");
    current_path = docDir;
    NoteItemAbstract abt;
    listnode root(id,id,abseek,current_path,abt,NIT_DIR);
    tree.push_back(root);
    id ++;
    abseek ++;

    if (!abfile.Exists())
        abfile.Create();
    abfile.Open();

    init_tree(root);

=======

NoteRecord::NoteRecord(NoteItemType noteItemType, int itemId, int parentId, wxString notebookTitle) :
    m_itemType(noteItemType), m_itemId(itemId), m_paretnId(parentId), m_notebookTitle(notebookTitle), m_valid(true)
{}

NoteRecord::NoteRecord(NoteItemType noteItemType, int itemId, int parentId, const NoteItemAbstract& abstract) :
    m_itemType(noteItemType), m_itemId(itemId), m_paretnId(parentId),m_abstract(abstract), m_valid(true)
{}
NoteRecord::NoteRecord() : m_valid(true)
{}

NoteItemType NoteRecord::getItemType()
{
    return m_itemType;
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
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
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    wxDir dir(path);
    wxArrayString tmparray;
    dir.GetAllFiles(path,&tmparray,wxEmptyString,wxDIR_FILES);
    for(int i=0;i < tmparray.size();i ++)
    {
        /*
        #if defined(__WXMSW__)
            tmparray[i].replace("/","\");
        #elif defined(__UNIX__)
            tmparray[i].replace("\","/")
        #endif
        */

        files.Add(tmparray[i]);
        //wxMessageBox(tmparray[i],"file caution");
    }

    wxString r;
    if(!dir.GetFirst(&r,wxEmptyString,wxDIR_DIRS))
        return;
    do
    {
        files.Add(wxString::Format("%s\\%s",path,r));
        //wxMessageBox(files.Last(),"dir caution");
        //get_all_item(files.Last(),files);
    }while(dir.GetNext(&r));
=======
    return m_abstract;
}

wxString NoteRecord::getNoteFilename()
{
    if (m_itemType == NIT_NOTE)
        return wxString::Format(_T("icenote_%d"), m_itemId);
    else
        return wxEmptyString;
}
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp

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

<<<<<<< HEAD:NoteBaseFileHandler.cpp
    if(r.type == NIT_DIR)
    {
        wxDir tmpdir(r.path);
        //wxMessageBox(r.path,"caution");
        wxArrayString files;
        /*
        Notetraverser travers(files);
        tmpdir.Traverse(travers);
        */
        get_all_item(r.path,files);
        //tmpdir.GetAllFiles(r.path,&files,wxEmptyString);
        //wxMessageBox(wxString::Format("%d",files.Count()),"caution");
        //wxMessageBox(files[0],"caution");
        int num = files.Count();
        for(unsigned int i=0;i < num;i ++)
        {
            //wxMessageBox(files[i],"caution");
//wxMessageBox(wxFileName(files[i]).GetFullName(),"hello");
            if(wxFileName(files[i]).GetFullName().IsSameAs(".config"))
            {
                //wxMessageBox(files[i],"config caution");
                continue;
            }
            if(wxFile::Exists(files[i]))
            {
                NoteItemAbstract abt;
                listnode tmpnode(id,r.itemID,abseek,files[i],abt,NIT_NOTE);
                get_abstract(tmpnode,abt);
                tmpnode.abstract = abt;
                //wxMessageBox(wxString::Format("%s/%s/%s/%s",tmpnode.abstract.getTitle()),"getabs");
                wxMessageBox(tmpnode.abstract.getTitle(),"caution");
                tree.push_back(tmpnode);
                id ++;
                abseek += 4;
            }
            else
            {
                NoteItemAbstract abt;
                listnode tmpnode(id,r.itemID,abseek,files[i],abt,NIT_DIR);
                wxString title;
                get_title(tmpnode,title);
                tmpnode.abstract.setTitile(title);
                wxMessageBox(title,"caution");
                tree.push_back(tmpnode);
                id ++;
                abseek ++;
                init_tree(tmpnode);
            }
        }
    }
=======
void NoteRecord::setParentId(int parentId)
{
    m_paretnId = parentId;
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

void NoteRecord::setAbstract(NoteItemAbstract& abstract)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    listnode& tmp = tree[itemId];
    //wxString str;
    //get_title(tmp,str);
    return tmp.abstract.getTitle();
=======
    m_abstract = NoteItemAbstract(abstract);
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}


void NoteRecord::setValid(bool valid = true)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    wxString str;
    if(r.abseek < 0)
    {
        return 0;
    }
    str = abfile.GetFirstLine();
    for(int i=1;i < r.abseek;i ++)
    {
        str = abfile.GetNextLine();
    }
    abstr = str;
    r.modified = 1;
    return 1;
=======
    m_valid = valid;
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

bool NoteRecord::isValid()
{
    return m_valid;
}

<<<<<<< HEAD:NoteBaseFileHandler.cpp
    if(r.abseek < 0)
    {
        return 0;
    }

    m_title = abfile.GetFirstLine();
    for(int i=1;i < r.abseek;i ++)
=======
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
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
    {
        NoteItemAbstract abstract = noteRecord.getAbstract();
        file.AddLine(abstract.getTitle());
        file.AddLine(abstract.getTags());
        file.AddLine(abstract.getCreatedTime().Format());
        file.AddLine(abstract.getLastModified().Format());
    }
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    //m_title = abfile.GetCurrentLine();
    m_tags = abfile.GetNextLine();
    m_createdTime.ParseDateTime(abfile.GetNextLine());
    m_lastModified.ParseDateTime(abfile.GetNextLine());
    itemabs.setTitile(m_title);
    itemabs.setTags(m_tags);
    itemabs.setCreateTime(m_createdTime);
    itemabs.setLastModified(m_lastModified);
    r.abstract = itemabs;
    r.modified = 1;
    wxMessageBox(wxString::Format("%s/%s/%s/%s",m_title,m_tags,m_createdTime.Format(),m_lastModified.Format()),"getabs");
    return 1;
=======
    /* write back! */
    file.Write();
    return file;
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

wxTextFile& operator>>(wxTextFile& file, NoteRecord& noteRecord)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    wxMessageBox(wxString::Format("%d",parentId),"erro");
    listnode tmp = tree[parentId];
    wxDateTime now;
    NoteItemAbstract abt(wxString::Format("%d",id),"new note",now.Now(),now.Now());
    listnode tmpnode(id,parentId,abseek,wxString::Format("%s\\%d.xml",tmp.path,id),abt,NIT_NOTE);
    tmpnode.modified = 1;
    abseek += 4;
    id ++;

    tree.push_back(tmpnode);
    wxMessageBox(wxString::Format("%d  %d",tmpnode.itemID,tmpnode.parentID),"createnode");
    return tmpnode.itemID;

    //if(wxFile().Create(tmpnode.path))
    /*if(1)
    {
        tree.push_back(tmpnode);
        wxMessageBox(wxString::Format("%d  %d",tmpnode.itemID,tmpnode.parentID),"createnode");

        abfile.AddLine(wxString::Format("%d",id));
        abfile.AddLine("new note");
        abfile.AddLine(now.Now().Format());
        abfile.AddLine(now.Now().Format());
        abfile.Write();

        return tmpnode.itemID;
=======
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
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
    }
    return file;
}

<<<<<<< HEAD:NoteBaseFileHandler.cpp
    else
        return -1;*/
=======
NoteFileHandler::NoteFileHandler(wxString docDir) : m_cfgDir(docDir)
{
    loadItemTree();
    restartRelations(); /* reset! */
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
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
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    listnode& tmp = tree[itemId];
    if(tmp.modified != 0)
    {
        itemAbstract = tmp.abstract;
        return true;
    }

    return false;
=======
    for (; m_currentRelationPos < m_noteRecords.size(); m_currentRelationPos++)
        if (m_noteRecords[m_currentRelationPos].isValid()) /* skip all invalid nodes! */
        {
            noteRelation = m_noteRecords[m_currentRelationPos].getRelationWithParent();
            m_currentRelationPos++;
            return true; /* YES! */
        }
    return false; /* end of records! */
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

bool NoteFileHandler::isEof()
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    listnode& tmp = tree[itemId];
    wxString str;
    if(tmp.modified != 0)
    {
        return tmp.abstract.getTitle();
    }

    return "";
=======
    return m_currentRelationPos >= m_noteRecords.size();
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

bool NoteFileHandler::getNoteAbstract(int itemId, NoteItemAbstract& itemAbstract)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    listnode parent = tree[parentId];
    wxString t = wxString::Format("%s\\%d",parent.path,id);
    wxDir dir;
    wxMessageBox(t,parent.path);
    if(!dir.Make(t))
    {
        return -1;
    }

    NoteItemAbstract abt;
    listnode tmp(id,parentId,abseek,t,abt,NIT_DIR);
    tmp.abstract.setTitile("new");
    tree.push_back(tmp);
    //abfile.AddLine(notebookTitle);
    abseek ++;
    id ++;
    return tmp.itemID;
=======
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
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

bool NoteFileHandler::setNoteAbstract(int itemId, NoteItemAbstract& itemAbstract)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    listnode& tmp = tree[itemId];
    if(tmp.type == NIT_NOTE)
    {
        tmp.abseek = -1;
        wxRemoveFile(tmp.path);
    }
     else
        remove_dir(itemId);
    return true;
=======
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end()) /* if not found! */
        return false;
    m_noteRecords[it->second].setAbstract(itemAbstract);
    //saveItemTree();
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

int NoteFileHandler::createNote(int parentId)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    textCtrl.SaveFile(tree[itemId].path);
    return true;
=======
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
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

bool NoteFileHandler::deleteItem(int itemId)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    listnode tmp = tree[itemId];

    if(tmp.abseek < 0)
    {
        return false;
    }
    bool op;
    if (wxFile::Exists(tmp.path))
        op = textCtrl.LoadFile(tmp.path);
    else
    {
        textCtrl.Clear();
        op = true;
    }
    return op;
=======
    bool f = _deleteItem(itemId);
    //saveItemTree();
    return f;
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

/* if a note, delete it; otherwise delete all sub-nodes */
bool NoteFileHandler::_deleteItem(int itemId)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    listnode& tmp = tree[itemId];
    if(tmp.abseek < 0)
        return false;
    tmp.abstract = itemAbstract;
    tmp.modified = 1;
        /*
    if(itemId < id - 1)
    {
        for(int i=0;i < 4;i ++)
        {
            abfile.RemoveLine(tmp.abseek + i);
        }
        wxMessageBox(wxString::Format("%s/%s/%s/%s",itemAbstract.getTitle(),itemAbstract.getTags(),itemAbstract.getCreatedTime().Format(),itemAbstract.getLastModified().Format()),"setabs");
        abfile.InsertLine(itemAbstract.getTitle(),tmp.abseek);
        abfile.InsertLine(itemAbstract.getTags(),tmp.abseek + 1);
        abfile.InsertLine(itemAbstract.getCreatedTime().Format(),tmp.abseek + 2);
        abfile.InsertLine(itemAbstract.getLastModified().Format(),tmp.abseek + 3);
        abfile.Write();
    }
    else
    {
        abfile.AddLine(itemAbstract.getTitle());
        abfile.AddLine(itemAbstract.getTags());
        abfile.AddLine(itemAbstract.getCreatedTime().Format());
        abfile.AddLine(itemAbstract.getLastModified().Format());
        abfile.Write();
    }
    */
=======
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
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
    return true;
}

bool NoteFileHandler::saveNote(int itemId, wxRichTextCtrl& textCtrl)
{
<<<<<<< HEAD:NoteBaseFileHandler.cpp
    int next = itemid + 1;
    while(tree[next].parentID == itemid)
    {
        if(tree[next].type == NIT_NOTE)
        {
            tree[next].abseek = -1;
            wxRemoveFile(tree[next].path);
        }
        else
        {
            tree[next].abseek = -1;
            remove_dir(next);
            wxRmdir(tree[next].path);
        }
        next ++;
    }
=======
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end())
        return false; /* invalid! */
    textCtrl.SaveFile(wxString::Format(_T("%s/%s"), m_cfgDir, m_noteRecords[it->second].getNoteFilename()), wxRICHTEXT_TYPE_XML);
    return true;
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
}

bool NoteFileHandler::openNote(int itemId, wxRichTextCtrl& textCtrl)
{
    map<int, int>::iterator it = m_itemIdMap.find(itemId);
    if (it == m_itemIdMap.end())
        return false; /* invalid! */
    textCtrl.LoadFile(wxString::Format(_T("%s/%s"), m_cfgDir, m_noteRecords[it->second].getNoteFilename()), wxRICHTEXT_TYPE_XML);
    return true;
}

<<<<<<< HEAD:NoteBaseFileHandler.cpp
void NoteFileHandler::reset_config(listnode& r)
{
    if(r.type == NIT_DIR)
    {
        wxDir tmpdir(r.path);
        wxArrayString files;
        get_all_item(r.path,files);

        for(int i=0;i < files.size();i ++)
            wxMessageBox(files[i],"get_item");

        int num = files.Count();
        for(unsigned int i=0;i < num;i ++)
        {
            if(wxFileName(files[i]).GetFullName().IsSameAs(".config"))
            {
                continue;
            }
            if(wxFile::Exists(files[i]))
            {
                int j=0;
                for(j=0;j < tree.size();j ++)
                {
                    if(tree[j].path.IsSameAs(files[i]))
                    {
                        wxMessageBox(files[i],"setfile config");
                        abfile.AddLine(tree[j].abstract.getTitle());
                        abfile.AddLine(tree[j].abstract.getTags());
                        abfile.AddLine(tree[j].abstract.getCreatedTime().Format());
                        abfile.AddLine(tree[j].abstract.getLastModified().Format());
                        break;
                    }
                }
            }
            else
            {
                listnode tmpnode = tree[0];
                for(int j=0;j < tree.size();j ++)
                {
                    if(tree[j].path.IsSameAs(files[i]))
                    {
                        wxMessageBox(files[i],"setdir config");
                        abfile.AddLine(tree[j].abstract.getTitle());
                        tmpnode = tree[j];
                        break;
                    }
                }
                reset_config(tmpnode);
            }
            abfile.Write();
        }
    }
}

NoteFileHandler::~NoteFileHandler()
{
    //dtor
    abfile.Clear();
    //abfile.Create();
    //abfile.Open();
    wxMessageBox("woca","hello");
    reset_config(tree[0]);

    for(unsigned int i=0;i > tree.size();i ++)
    {
        listnode& parent = tree[i];
        listnode& me = tree[i];

        if(me.abseek >= 0)
        {
            if(me.type == NIT_DIR)
            {
                abfile.AddLine(me.abstract.getTitle());
            }
            else if(me.type == NIT_NOTE)
            {
                abfile.AddLine(me.abstract.getTitle());
                abfile.AddLine(me.abstract.getTags());
                abfile.AddLine(me.abstract.getCreatedTime().Format());
                abfile.AddLine(me.abstract.getLastModified().Format());
            }
        }

        if(me.abseek < -10)
=======
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
>>>>>>> SimpleFileHandler:NoteFileHandler.cpp
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
    abfile.Write();
    abfile.Close();
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

