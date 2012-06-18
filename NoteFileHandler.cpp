#include "NoteFileHandler.h"

#define CONFIG_FILE ".config"
NoteFileHandler::NoteFileHandler(wxString docDir):abfile(wxString::Format("%s/%s", docDir, CONFIG_FILE))
{
    //ctor
    id = 0;
    abseek = 0;
    current_re_id = 0;
    //wxSetWorkingDirectory("##");
    listnode root(id,id,abseek,docDir,NIT_DIR);

    init_tree(root);

    if (!abfile.Open())
        abfile.Create();
}

void NoteFileHandler::restartRelations()
{
    current_re_id = 0;
}

bool NoteFileHandler::nextRelation(NoteRelation& noterelation)
{
    int next_re = current_re_id + 1;

    listnode& tmp = tree[next_re];
    if(tmp.abseek < 0)
        return false;
    NoteRelation tmp_re(tmp.type,tmp.parentID,tmp.itemID);
    noterelation = tmp_re;
    return true;
}

void NoteFileHandler::init_tree(listnode& r)
{
    tree.insert(tree.end(),r);
    id ++;

    if(r.type == NIT_DIR)
    {
        wxDir tmpdir(r.path);
        wxArrayString files;
        /*
        Notetraverser travers(files);
        tmpdir.Traverse(travers);
        */
        tmpdir.GetAllFiles(r.path,&files,wxEmptyString,wxDIR_FILES|wxDIR_DIRS);
        for(unsigned int i=0;i < files.Count();i ++)
        {
            if(wxFile::Exists(files[i]))
            {
                listnode tmpnode(id,r.itemID,abseek,tmpdir.GetName()+files[i],NIT_NOTE);
                tree.insert(tree.end(),tmpnode);
                id ++;
                abseek += 4;
            }
            else
            {
                listnode tmpnode(id,r.itemID,abseek,files[i],NIT_DIR);
                abseek ++;
                init_tree(tmpnode);
            }
        }
    }
}

wxString NoteFileHandler::getItemTitle(int itemId)
{
    listnode& tmp = tree[itemId];
    wxString str;
    get_title(tmp,str);
    return str;
}

int NoteFileHandler::get_title(listnode& r,wxString& abstr)
{
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
    return 1;
}

int NoteFileHandler::get_abstract(listnode& r,NoteItemAbstract& itemabs)
{
    wxString m_title;           /* Note's title */
    wxString m_tags;            /* Note's tag */
    wxDateTime m_createdTime;   /* Note's Created Time */
    wxDateTime m_lastModified;  /* Note's LastModified Time */

    if(r.abseek < 0)
    {
        return 0;
    }
    m_title = abfile.GetFirstLine();
    for(int i=1;i < r.abseek;i ++)
    {
        m_title = abfile.GetNextLine();
    }
    //m_title = abfile.GetCurrentLine();
    m_tags = abfile.GetNextLine();
    m_createdTime.ParseDate(abfile.GetNextLine());
    m_lastModified.ParseDate(abfile.GetNextLine());
    itemabs.setTitile(m_title);
    itemabs.setTags(m_tags);
    itemabs.setCreateTime(m_createdTime);
    itemabs.setLastModified(m_lastModified);
    return 1;
}

int NoteFileHandler::createNote(int parentId)
{
    listnode tmpnode(id,parentId,abseek,"",NIT_NOTE);
    abseek += 4;
    id ++;

    if(wxFile().Create(wxT("unsave"+id)))
        return tmpnode.itemID;
    else
        return -1;
}

/*????????*/
bool NoteFileHandler::isEof()
{
    return true;
}

bool NoteFileHandler::getNoteAbstract(int itemId, NoteItemAbstract& itemAbstract)
{
    listnode& tmp = tree[itemId];
    if(get_abstract(tmp,itemAbstract))
        return true;
    return false;
}

wxString NoteFileHandler::getNotebookTitle(int itemId)
{
    listnode& tmp = tree[itemId];
    wxString str;
    if(get_title(tmp,str))
        return str;
    return "";
}

int NoteFileHandler::createNotebook(wxString notebookTitle)
{
    return 0;
}

bool NoteFileHandler::deleteItem(int itemId)
{
    listnode& tmp = tree[itemId];
    tmp.abseek = -1;
    return true;
}

bool NoteFileHandler::saveNote(int itemId, wxRichTextCtrl& textCtrl)
{
    return true;
}

bool NoteFileHandler::openNote(int itemId, wxRichTextCtrl& textCtrl)
{
    return true;
}

bool NoteFileHandler::setNoteAbstract(int itemId, const NoteItemAbstract& itemAbstract)
{
    listnode& tmp = tree[itemId];
    if(tmp.abseek < 0)
        return false;
    if(itemId < id - 1)
    {
        for(int i=0;i < 4;i ++)
        {
            abfile.RemoveLine(tmp.abseek + i);
        }
        abfile.InsertLine(itemAbstract.getTitle(),tmp.abseek);
        abfile.InsertLine(itemAbstract.getTags(),tmp.abseek + 1);
        abfile.InsertLine(itemAbstract.getCreatedTime().Format(wxT("%Y-%m-%d"),wxDateTime::A_EST),tmp.abseek + 2);
        abfile.InsertLine(itemAbstract.getLastModified().Format(wxT("%Y-%m-%d"),wxDateTime::A_EST),tmp.abseek + 3);
    }
    else
    {
        abfile.AddLine(itemAbstract.getTitle());
        abfile.AddLine(itemAbstract.getTags());
        abfile.AddLine(itemAbstract.getCreatedTime().Format(wxT("%Y-%m-%d"),wxDateTime::A_EST));
        abfile.AddLine(itemAbstract.getLastModified().Format(wxT("%Y-%m-%d"),wxDateTime::A_EST));
    }
    return true;
}

void NoteFileHandler::remove_dir(int itemid)
{
    int next = itemid + 1;
    while(tree[next].parentID == itemid)
    {
        if(tree[next].type == NIT_NOTE)
        {
            wxRemoveFile(tree[next].path);
        }
        else
        {
            remove_dir(next);
            wxRmdir(tree[next].path);
        }
        next ++;
    }
}

void NoteFileHandler::count_line(int itemid,int& lines)
{
    int next = itemid + 1;
    while(tree[next].parentID == itemid)
    {
        if(tree[next].type == NIT_NOTE)
        {
            lines += 4;
        }
        else
        {
            lines += 1;
            count_line(next,lines);
        }
        next ++;
    }
}

NoteFileHandler::~NoteFileHandler()
{
    //dtor
    for(unsigned int i=1;i < tree.size()-1;i ++)
    {
        listnode& parent = tree[i-1];
        listnode& me = tree[i];

        if(me.abseek < 0)
        {
            int psize = 0;
            int msize = 0;
            if(parent.type == NIT_DIR)
            {
                 psize = 1;
            }
            else
            {
                psize = 4;
            }

            if(me.type == NIT_DIR)
            {
                count_line(me.itemID,msize);
            }
            else
            {
                msize = 4;
            }


            for(int j=parent.abseek+psize;j < parent.abseek+psize+msize;j ++)
            {
                abfile.RemoveLine(j);
            }
            if(me.type == NIT_NOTE)
            {
                wxRemoveFile(me.path);
            }
            else
            {
                remove_dir(me.itemID);
            }
        }
    }
}
