#ifndef NOTEITEMABSTRACT_H
#define NOTEITEMABSTRACT_H

#include <wx/string.h>
#include <wx/datetime.h>
#include <wx/richtext/richtextctrl.h>


/* This class is used to share the info between FileHandler and
    front-side(GUI) */
class NoteItemAbstract
{
    public:
        NoteItemAbstract();
        NoteItemAbstract(wxString title, wxString tags, wxDateTime createdTime, wxDateTime lastModified);

        /* get them! */
        wxString getTitle()const;
        wxString getTags()const;
        wxDateTime getCreatedTime()const;
        wxDateTime getLastModified()const;

        void setTitile(wxString title);
        void setTags(wxString tags);
        void setCreateTime(wxDateTime time);
        void setLastModified(wxDateTime time);

        virtual ~NoteItemAbstract();
    protected:
    private:
        wxString m_title;           /* Note's title */
        wxString m_tags;            /* Note's tag */
        wxDateTime m_createdTime;   /* Note's Created Time */
        wxDateTime m_lastModified;  /* Note's LastModified Time */
};

#endif // NOTEITEMABSTRACT_H
