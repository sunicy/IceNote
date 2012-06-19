#include "NoteFileHandler.h"
#include <wx/filename.h>


#define CONFIG_FILE ".config"
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
}

wxString NoteFileHandler::getItemTitle(int itemId)
{
    listnode& tmp = tree[itemId];
    //wxString str;
    //get_title(tmp,str);
    return tmp.abstract.getTitle();
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
    r.modified = 1;
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
    r.abstract = itemabs;
    r.modified = 1;
    wxMessageBox(wxString::Format("%s/%s/%s/%s",m_title,m_tags,m_createdTime.Format(),m_lastModified.Format()),"getabs");
    return 1;
}

int NoteFileHandler::createNote(int parentId)
{
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
    }

    else
        return -1;*/
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
    if(tmp.modified != 0)
    {
        itemAbstract = tmp.abstract;
        return true;
    }

    return false;
}

wxString NoteFileHandler::getNotebookTitle(int itemId)
{
    listnode& tmp = tree[itemId];
    wxString str;
    if(tmp.modified != 0)
    {
        return tmp.abstract.getTitle();
    }

    return "";
}

int NoteFileHandler::createNotebook(wxString notebookTitle, int parentId)
{
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
}

bool NoteFileHandler::deleteItem(int itemId)
{
    listnode& tmp = tree[itemId];
    if(tmp.type == NIT_NOTE)
    {
        tmp.abseek = -1;
        wxRemoveFile(tmp.path);
    }
     else
        remove_dir(itemId);
    return true;
}

bool NoteFileHandler::saveNote(int itemId, wxRichTextCtrl& textCtrl)
{
    textCtrl.SaveFile(tree[itemId].path);
    return true;
}

bool NoteFileHandler::openNote(int itemId, wxRichTextCtrl& textCtrl)
{
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
}

bool NoteFileHandler::setNoteAbstract(int itemId, const NoteItemAbstract& itemAbstract)
{
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
    return true;
}

void NoteFileHandler::remove_dir(int itemid)
{
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
    abfile.Write();
    abfile.Close();
}
