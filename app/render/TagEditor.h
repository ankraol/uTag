#ifndef UTAG_TAGEDITOR_H
#define UTAG_TAGEDITOR_H

#include "gtkmm.h"

using SongInfo = std::tuple<std::string, std::string, std::string, std::string, std::string>;

class TagEditor : public Gtk::Box {
public:
    TagEditor() = default;

    void AddSongInfo(const SongInfo& info);
    void HideSongInfo();
    void MakeClean();

    void editTags(); //sets all entries as editable && remembers tags until "Save" button is pressed;
    void saveTags(); //processes changes;
    void discardTags(); //discard all changes;

    SongInfo getChanges(); //returns changes;


protected:
    //class members
    SongInfo m_info;

    //Gtk objects
    Gtk::Image m_Cover;
    Gtk::Label m_Artist_label;
    Gtk::Entry m_Artist;
    Gtk::Label m_Title_label;
    Gtk::Entry m_Title;
    Gtk::Label m_Album_label;
    Gtk::Entry m_Album;
    Gtk::Label m_Genre_label;
    Gtk::Entry m_Genre;
//    Gtk::Label m_Path;
};

#endif //UTAG_TAGEDITOR_H
