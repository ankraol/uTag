#ifndef UTAG_AUDIOLIST_H
#define UTAG_AUDIOLIST_H

#include <gtkmm.h>
#include "MultiTagEditor.h"
#include "TagEditor.h"

class EditPopupMenu;

using SongInfo = std::tuple<std::string, std::string, std::string, std::string, std::string>;

class AudioList : public Gtk::Box {
public:

    explicit AudioList(const std::string& dirName);
    AudioList() = default;
    ~AudioList();

    void DisplayFiles(const std::string& dirName);
    void RefreshData(const SongInfo& info);
    void MakeClean();

    void setSelectedRow(Gtk::TreeModel::Path path);
    void MultiEditor_closed() {m_multipleEditorOpened = false; };

    friend void MultiTagEditor::SaveChanges();
protected:
    //signal handlers;
    void selectFile(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column); //when .mp3 File from list selected;
    void editTag(); //when "Edit" button pressed, must change to "Discard" button;
    void save_Exit(); //when "Save"/"Exit" button pressed;
    void selection_changed();

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            if (size() == 0) {
                add(m_artist);
                add(m_title);
                add(m_album);
                add(m_genre);
                add(m_path);
            }
        };

        Gtk::TreeModelColumn<Glib::ustring> m_title;
        Gtk::TreeModelColumn<Glib::ustring> m_artist;
        Gtk::TreeModelColumn<Glib::ustring> m_album;
        Gtk::TreeModelColumn<Glib::ustring> m_genre;
        Gtk::TreeModelColumn<Glib::ustring> m_path;
    };

    ModelColumns m_columns;
    //class members
    Gtk::TreeModel::Path m_path; //selected row
    std::string m_dirName; //current location
    std::list<SongInfo> m_songCollection;
    TagEditor* m_tagEditor{};

    //triggers
    bool m_editPressed = false;
    bool m_exitPressed = false;

    bool m_multipleEditorOpened = false;
    bool m_singleEditorOpened = false;

    //GTK objects
    Gtk::ScrolledWindow m_scrollWin;
    Gtk::TreeView m_treeView_Playlist;
    Glib::RefPtr<Gtk::ListStore> m_listStore_Playlist;
    Glib::RefPtr<Gtk::TreeSelection> m_multipleSelection;
    EditPopupMenu *m_multiSelectionMenu{};
    MultiTagEditor *m_multiTagEditor{};

    //bottom header for "Edit" and "Save" buttons;
    Gtk::Box m_Editor_ButtonsBox;
    Gtk::Box m_controlButtons_Box;
    Gtk::Button m_save_exitButton;
    Gtk::Button m_editButton;
};

#endif //UTAG_AUDIOLIST_H
