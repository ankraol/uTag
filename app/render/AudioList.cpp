#include "AudioList.h"
#include "mainWin.h"

AudioList::AudioList(const std::string &dirName) : m_dirName(dirName) {
    m_tagEditor = new TagEditor;
    m_multiTagEditor = new MultiTagEditor(this);
    m_multiSelectionMenu = new EditPopupMenu(m_multiTagEditor);
    DisplayFiles(dirName);
}

void AudioList::DisplayFiles(const std::string& dirName) {
    m_dirName = dirName;
    //Get songs from a directory
    m_songCollection = getFiles_fromDir(dirName);

    //Scrolled Window set
    m_scrollWin.add(m_treeView_Playlist);
    m_scrollWin.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    pack_start(m_scrollWin, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    //side panel with song tags info and control bottom header;
    m_Editor_ButtonsBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    pack_start(m_Editor_ButtonsBox, Gtk::PackOptions::PACK_SHRINK);
    m_Editor_ButtonsBox.pack_start(*m_tagEditor, Gtk::PackOptions::PACK_SHRINK);
    m_controlButtons_Box.set_margin_top(30);
    m_Editor_ButtonsBox.pack_end(m_controlButtons_Box, Gtk::PackOptions::PACK_SHRINK);

    //pack multiSelection window
    pack_start(*m_multiTagEditor, Gtk::PackOptions::PACK_SHRINK);

    //Tree Model set
    m_listStore_Playlist = Gtk::ListStore::create(m_columns);
    m_treeView_Playlist.set_model(m_listStore_Playlist);
    //set multiple selection
    m_treeView_Playlist.get_selection()->set_mode(Gtk::SelectionMode::SELECTION_MULTIPLE);
    m_multipleSelection = m_treeView_Playlist.get_selection();

    //Tree View Filling
    Gtk::TreeModel::Row row;
    for (const auto& [artist, title, album, genre, path] : m_songCollection) {
        row = *(m_listStore_Playlist->append());
        row[m_columns.m_artist] = artist;
        row[m_columns.m_title] = title;
        row[m_columns.m_album] = album;
        row[m_columns.m_genre] = genre;
        row[m_columns.m_path] = path;
    }
    m_treeView_Playlist.remove_all_columns();
    m_treeView_Playlist.append_column("Artist", m_columns.m_artist);
    m_treeView_Playlist.append_column("Title", m_columns.m_title);
    m_treeView_Playlist.append_column("Album", m_columns.m_album);
    m_treeView_Playlist.append_column("Genre", m_columns.m_genre);
    m_treeView_Playlist.append_column("Path", m_columns.m_path);

    //signal connection
    m_treeView_Playlist.signal_row_activated().connect(sigc::mem_fun(*this,
                                                                     &AudioList::selectFile));
    m_editButton.signal_clicked().connect(sigc::mem_fun(*this, &AudioList::editTag));
    m_save_exitButton.signal_clicked().connect(sigc::mem_fun(*this, &AudioList::save_Exit));
    m_multipleSelection->signal_changed().connect(sigc::mem_fun(*this, &AudioList::selection_changed));

    //making sortable columns
    for (int i = 0; i < 5; ++i) {
        auto column = m_treeView_Playlist.get_column(i);
        column->set_sort_column(i);
    }
    show_all_children();
}

void AudioList::selection_changed() {
    if (m_multipleSelection->count_selected_rows() > 1) {
        //manage opened editors
        m_multipleEditorOpened = true;
        if (m_singleEditorOpened) {
            m_tagEditor->HideSongInfo();
            m_editButton.hide();
            m_save_exitButton.hide();
            m_singleEditorOpened = false;
        }

        std::vector<Gtk::TreeModel::Path> selected_rows = m_multipleSelection->get_selected_rows();
        auto it = selected_rows.begin();

        std::vector<Glib::ustring> paths;

        for (; it != selected_rows.end(); ++it) {
            Gtk::TreeModel::iterator iter = m_listStore_Playlist->get_iter(*it);
            Gtk::TreeRow row = *iter;

            paths.push_back(row[m_columns.m_path]);
        }
        m_multiTagEditor->setSelection(paths, selected_rows);
        m_multiSelectionMenu->popup_at_pointer(nullptr);
    }
}

void AudioList::editTag() {
    if (m_editPressed) {
        //Discard
        m_editPressed = false;
        m_tagEditor->discardTags();
        m_editButton.set_label("Edit");
        m_save_exitButton.set_label("Exit");
    } else {
        //Edit
        m_editPressed = true;
        m_editButton.set_label("Discard");
        m_save_exitButton.set_label("Save");
        m_tagEditor->editTags();
    }
}

void AudioList::save_Exit() {
    if (m_exitPressed) {
        m_exitPressed = false;
        //hide EditTag sidebar and buttons
        m_tagEditor->HideSongInfo();
        m_controlButtons_Box.hide();
    } else {
        //"Save" button
        m_exitPressed = true;
        m_tagEditor->saveTags();
        m_save_exitButton.set_label("Exit");
        m_editButton.set_label("Edit");
        //set new tags to file
        setTags(m_tagEditor->getChanges());
        RefreshData(m_tagEditor->getChanges());
    }
    m_singleEditorOpened = false;
}

void AudioList::setSelectedRow(Gtk::TreeModel::Path path) {
    m_path = std::move(path);
}

void AudioList::RefreshData(const SongInfo& info) {
    const auto& [artist, title, album, genre, path] = info;
    Gtk::TreeModel::iterator iter = m_listStore_Playlist->get_iter(m_path);

    if (iter) {
        Gtk::TreeModel::Row row = *iter;
        if (!artist.empty())
            row[m_columns.m_artist] = artist;
        if (!title.empty())
            row[m_columns.m_title] = title;
        if (!album.empty())
            row[m_columns.m_album] = album;
        if (!genre.empty())
            row[m_columns.m_genre] = genre;
    }
}

void AudioList::selectFile(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
    if (m_multipleSelection->count_selected_rows() == 1) {

        //manage opened Editors
        m_singleEditorOpened = true;
        if (m_multipleEditorOpened) {
            m_multiTagEditor->DiscardChanges();
            m_multipleEditorOpened = false;
        }

        m_path = path;
        Gtk::TreeModel::iterator iter = m_listStore_Playlist->get_iter(path);
        if(iter) {
            Gtk::TreeModel::Row row = *iter;
            SongInfo song = std::make_tuple(std::string((Glib::ustring) row[m_columns.m_artist]),
                                            std::string((Glib::ustring) row[m_columns.m_title]),
                                            std::string((Glib::ustring) row[m_columns.m_album]),
                                            std::string((Glib::ustring) row[m_columns.m_genre]),
                                            std::string((Glib::ustring) row[m_columns.m_path]));
            m_tagEditor->AddSongInfo(song);

            //add "Edit" and "Save" buttons;
            m_controlButtons_Box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
            m_editButton.set_label("Edit");
            m_editButton.set_relief(Gtk::RELIEF_NONE);
            m_save_exitButton.set_label("Exit");
            m_save_exitButton.set_relief(Gtk::RELIEF_NONE);
            m_controlButtons_Box.pack_start(m_editButton, Gtk::PackOptions::PACK_EXPAND_PADDING);
            m_controlButtons_Box.pack_start(m_save_exitButton, Gtk::PackOptions::PACK_EXPAND_PADDING);
            m_controlButtons_Box.show_all_children();
            m_controlButtons_Box.show();
        }
    }
}

void AudioList::MakeClean() {
    m_scrollWin.remove();
    m_editButton.remove();
    m_save_exitButton.remove();
    m_Editor_ButtonsBox.remove(m_editButton);
    m_Editor_ButtonsBox.remove(m_save_exitButton);

    remove(m_treeView_Playlist);
    remove(m_scrollWin);
    m_listStore_Playlist->clear();
    m_tagEditor->MakeClean();
    remove(*m_tagEditor);
    m_songCollection.clear();
    m_exitPressed = false;
    m_editPressed = false;
}

AudioList::~AudioList() {
    delete m_tagEditor;
    delete m_multiTagEditor;
    delete m_multiSelectionMenu;
}
