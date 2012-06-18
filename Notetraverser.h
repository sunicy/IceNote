#ifndef NOTETRAVERSER_H
#define NOTETRAVERSER_H

#include<wx/dir.h>
class Notetraverser:public wxDirTraverser
{
    public:
        Notetraverser(wxArrayString& files):m_files(files) { }

    virtual wxDirTraverseResult OnFile(const wxString& filename)
    {
       m_files.Add(filename);
       return wxDIR_CONTINUE;
    }

    virtual wxDirTraverseResult OnDir(const wxString& WXUNUSED(dirname))
    {
       // m_files.Add(WXUNUSED(dirname));
       return wxDIR_CONTINUE;
    }

    virtual wxDirTraverseResult OnOpenError(const wxString& dirname)
    {
       return wxDIR_IGNORE;
    }

    private:
        wxArrayString& m_files;
};

#endif
