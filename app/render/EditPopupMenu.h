#ifndef UTAG_EDITPOPUPMENU_H
#define UTAG_EDITPOPUPMENU_H

#include "gtkmm.h"

class MultiTagEditor;

class EditPopupMenu : public Gtk::Menu {
public:
    explicit EditPopupMenu(MultiTagEditor *multiTagEditor);

protected:
    //signal handlers
    void buttonPressed();

    //members
    Gtk::MenuItem m_editButton;
    MultiTagEditor *m_multiTagEditor;
    friend class ::MultiTagEditor;
};

#endif //UTAG_EDITPOPUPMENU_H
