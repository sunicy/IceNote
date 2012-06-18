#include "NoteFileHandler.h"
#include <wx/filename.h>

#define CONFIG_FILE ".config"
NoteFileHandler::NoteFileHandler(wxString docDir):abfile(wxString::Format("%s/%s", docDir, CONFIG_FILE))
{
    //ctor
    id = 0;
    abseek = 0;
    current_re_id = 0;
    //wxSetWorkingDirectory("##");
    current_path = docDir;
    listnode root(id,id,abseek,current_path,NIT_DIR);
    tree.push_back(root);
    id ++;
    abseek ++;

    init_tree(root);


    if (!abfile.Exists())
        abfile.Create();
    abfile.Open();
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
    NoteRelation tmp_re(tmp.type,tmp.itemID,tmp.parentID);
    //wxMessageBox(wxString::Format("%d  %d",tmp.itemID,tmp.parentID),"re");
    current_re_id ++;
    noterelation = tmp_re;
    return true;
}


void NoteFileHandler::get_all_item(wxString& path,wxArrayString& files)
{
    wxDir dir(path);
    wxArrayString tmparray;
    dir.GetAllFiles(path,&tmparray,wxEmptyString,wxDIR_FILES);
    for(int i=0;i < tmparray.size();i ++)
    {
        files.Add(tmparray[i]);
        //wxMessageBox(tmparray[i],"file caution");
    }

    wxString r;
    if(!dir.GetFirst(&r,wxEmptyString,wxDIR_DIRS))
        return;
    do
    {
        files.Add(wxString::Format("%s/%s",path,r));
        //wxMessageBox(files.Last(),"dir caution");
        //get_all_item(files.Last(),files);
    }while(dir.GetNext(&r));

}


void NoteFileHandler::init_tree(listnode& r)
{
    /*
    tree.insert(tree.end(),r);
    id ++;
    abseek ++;
    */

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
                wxMessageBox(files[i],"config caution");
                continue;
            }
            if(wxFile::Exists(files[i]))
            {
                listnode tmpnode(id,r.itemID,abseek,files[i],NIT_NOTE);
                wxMessageBox(files[i],"caution");
                tree.push_back(tmpnode);
                id ++;
                abseek += 4;
            }
            else
            {
                listnode tmpnode(id,r.itemID,abseek,files[i],NIT_DIR);
                wxMessageBox(files[i],"caution");
                tree.push_back(tmpnode);
                id ++;
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
    m_createdTime.ParseDateTime(abfile.GetNextLine());
    m_lastModified.ParseDateTime(abfile.GetNextLine());
    itemabs.setTitile(m_title);
    itemabs.setTags(m_tags);
    itemabs.setCreateTime(m_createdTime);
    itemabs.setLastModified(m_lastModified);
    return 1;
}

int NoteFileHandler::createNote(int parentId)
{
    listnode tmp = tree[parentId];
    listnode tmpnode(id,parentId,abseek,wxString::Format("%s/%d",tmp.path,id),NIT_NOTE);
    abseek += 4;
    id ++;

    if(wxFile().Create(tmpnode.path))
    {
        wxDateTime now;
        tree.push_back(tmpnode);
        abfile.AddLine(wxString::Format("%d",id));
        abfile.AddLine("new note");
        abfile.AddLine(now.Now().Format());
        abfile.AddLine(now.Now().Format());
        return tmpnode.itemID;
    }

    else
        return -1;
}

/*????????*/
bool NoteFileHandler::isEof()
{
    if(current_re_id < id-1)
    {
        //wxMessageBox(wxString::Format("%d",current_re_id),"reId");
        return false;
    }

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

int NoteFileHandler::createNotebook(wxString notebookTitle, int parentId)
{
    listnode parent = tree[parentId];
    wxString t = wxString::Format("%s/%d",parent.path,id);
    wxDir dir;
    wxMessageBox(t,parent.path);
    if(!dir.Make(t))
    {
        return -1;
    }

    listnode tmp(id,parentId,abseek,t,NIT_DIR);
    abfile.AddLine(notebookTitle);
    abseek ++;
    id ++;
    return tmp.itemID;
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
    listnode tmp = tree[itemId];
    if(tmp.abseek < 0)
    {
        return false;
    }
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
        abfile.InsertLine(itemAbstract.getCreatedTime().Format(),tmp.abseek + 2);
        abfile.InsertLine(itemAbstract.getLastModified().Format(),tmp.abseek + 3);
    }
    else
    {
        abfile.AddLine(itemAbstract.getTitle());
        abfile.AddLine(itemAbstract.getTags());
        abfile.AddLine(itemAbstract.getCreatedTime().Format());
        abfile.AddLine(itemAbstract.getLastModified().Format());
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
