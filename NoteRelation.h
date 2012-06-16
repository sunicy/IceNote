#ifndef NOTERELATION_H
#define NOTERELATION_H

enum NoteItemType {
    NIT_DIR,    /* it's a pure directory */
    NIT_NOTE    /* it IS a note! */
};
/* this class aims at offering the relationship between a certain
    pair of nodes in the NoteTree.
    Surely NoteRelation is always packed by FileHandler,
    and be sent to GUI */
class NoteRelation
{
    public:
        NoteRelation();
        NoteRelation(NoteItemType childItemType, int childId, int parentId);

        int getParentId();  /* Parent of the pair */
        int getChildId();   /* Child of the pair */
        NoteItemType getChildItemType(); /* What's the type of the child? */

        virtual ~NoteRelation();
    protected:
    private:
        int m_parentId;
        int m_childId;
        NoteItemType childItemType; /* What's the type of the child? */
};

#endif // NOTERELATION_H
