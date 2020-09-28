#include "MultiTagEditor.h"
#include "AudioList.h"
#include "../src/setTags.h"

void MultiTagEditor::EditTags() {
    set_orientation(Gtk::ORIENTATION_VERTICAL);
    Glib::RefPtr<Gdk::Pixbuf> pb = Gdk::Pixbuf::create_from_file("./app/resources/playlist_icon.png", 200, 200);

    m_image.set(pb);
    pack_start(m_image, Gtk::PackOptions::PACK_SHRINK);

    //set labels
    m_Artist_label.set_label("Artist:");
    m_Title_label.set_label("Title:");
    m_Album_label.set_label("Album:");
    m_Genre_label.set_label("Genre:");
    m_label.set_label("CONSIDER: Empty fields will not be modified.");
    m_label.set_margin_top(20);

    //buttons box
    m_buttonsBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    m_saveButton.set_label("Save");
    m_saveButton.set_relief(Gtk::RELIEF_NONE);
    m_discardButton.set_label("Discard");
    m_discardButton.set_relief(Gtk::RELIEF_NONE);
    m_buttonsBox.pack_start(m_saveButton, Gtk::PackOptions::PACK_EXPAND_WIDGET);
    m_buttonsBox.pack_start(m_discardButton, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    m_saveButton.signal_clicked().connect(sigc::mem_fun(*this, &MultiTagEditor::SaveChanges));
    m_discardButton.signal_clicked().connect(sigc::mem_fun(*this, &MultiTagEditor::DiscardChanges));

    //pack
    pack_start(m_Artist_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Artist, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Title_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Title, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Album_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Album, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Genre_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Genre, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_label, Gtk::PackOptions::PACK_SHRINK);
    pack_end(m_buttonsBox, Gtk::PackOptions::PACK_SHRINK);

    show_all_children();

}

void MultiTagEditor::setSelection(std::vector<Glib::ustring> selected_rows, std::vector<Gtk::TreeModel::Path> selected_paths) {
    m_selected_rows = std::move(selected_rows);
    m_selected_paths = std::move(selected_paths);
}

void MultiTagEditor::DiscardChanges() {
    //set them empty
    m_Artist.set_text("");
    m_Title.set_text("");
    m_Album.set_text("");
    m_Genre.set_text("");

    //hide all widgets
    m_image.hide();
    m_Artist.hide();
    m_Artist_label.hide();
    m_Title_label.hide();
    m_Title.hide();
    m_Album_label.hide();
    m_Album.hide();
    m_Genre_label.hide();
    m_Genre.hide();
    m_saveButton.hide();
    m_discardButton.hide();
    m_buttonsBox.hide();
    m_label.hide();
    m_audioList_pointer->MultiEditor_closed();
}

void MultiTagEditor::SaveChanges() {
    auto it = m_selected_paths.begin();

    for (const auto& path : m_selected_rows) {
        m_audioList_pointer->setSelectedRow(*it);
        SongInfo info = std::make_tuple(m_Artist.get_text().c_str(), m_Title.get_text().c_str(),
                                        m_Album.get_text().c_str(), m_Genre.get_text().c_str(),
                                        path.c_str());
        setTags(info);
        m_audioList_pointer->RefreshData(info);
        ++it;
    }
    DiscardChanges();
    m_audioList_pointer->MultiEditor_closed();
}
