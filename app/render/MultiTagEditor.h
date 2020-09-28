#ifndef UTAG_MULTITAGEDITOR_H
#define UTAG_MULTITAGEDITOR_H

#include <gtkmm.h>
#include "EditPopupMenu.h"

class AudioList;

class MultiTagEditor : public Gtk::Box {
public:
    explicit MultiTagEditor(AudioList* audioList_pointer) : m_audioList_pointer(audioList_pointer) {};

    void setSelection(std::vector<Glib::ustring> selected_rows, std::vector<Gtk::TreeModel::Path> selected_paths);

    void EditTags();
    void DiscardChanges();
    void SaveChanges();

    friend void ::EditPopupMenu::buttonPressed();

protected:
    //selection
    std::vector<Glib::ustring> m_selected_rows;
    std::vector<Gtk::TreeModel::Path> m_selected_paths;
    AudioList* m_audioList_pointer;

    //buttons
    Gtk::Box m_buttonsBox;
    Gtk::Button m_saveButton;
    Gtk::Button m_discardButton;

    //editable fields
    Gtk::Label m_label;
    Gtk::Image m_image;
    Gtk::Label m_Artist_label;
    Gtk::Entry m_Artist;
    Gtk::Label m_Title_label;
    Gtk::Entry m_Title;
    Gtk::Label m_Album_label;
    Gtk::Entry m_Album;
    Gtk::Label m_Genre_label;
    Gtk::Entry m_Genre;
};

#endif //UTAG_MULTITAGEDITOR_H
