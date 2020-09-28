#include "TagEditor.h"
#include "../src/AudioFileInfo.h"

void TagEditor::AddSongInfo(const SongInfo& info) {
    set_orientation(Gtk::ORIENTATION_VERTICAL);
    m_info = info;
    const auto& [artist, title, album, genre, path] = m_info;

    //set up childWidgets
    Glib::RefPtr<Gdk::Pixbuf> pb;
    try {
        pb = Gdk::Pixbuf::create_from_file("app/resources/covers/" + title + ".jpg", 200, 200);
    } catch (...) {
        pb = Gdk::Pixbuf::create_from_file("app/resources/music-placeholder.png", 200, 200);
    }
    m_Cover.set(pb);
    m_Cover.set_margin_left(30);
    m_Cover.set_margin_right(30);
    m_Cover.set_margin_bottom(30);

    m_Artist_label.set_label("Artist");
    m_Artist.set_text(artist);
    m_Title_label.set_label("Title:");
    m_Title.set_text(title);
    m_Album_label.set_label("Album:");
    m_Album.set_text(album);
    m_Genre_label.set_label("Genre:");
    m_Genre.set_text(genre);

    m_Artist.set_editable(false);
    m_Title.set_editable(false);
    m_Album.set_editable(false);
    m_Genre.set_editable(false);

    //focus settings
    m_Artist.set_can_focus(false);
    m_Title.set_can_focus(false);
    m_Album.set_can_focus(false);
    m_Genre.set_can_focus(false);

    m_Artist.set_has_frame(false);
    m_Title.set_has_frame(false);
    m_Album.set_has_frame(false);
    m_Genre.set_has_frame(false);

    //pack childWidgets
    pack_start(m_Cover, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Artist_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Artist, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Title_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Title, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Album_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Album, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Genre_label, Gtk::PackOptions::PACK_SHRINK);
    pack_start(m_Genre, Gtk::PackOptions::PACK_SHRINK);

    //show childWidgets
    show_all_children();
    show();
}

void TagEditor::HideSongInfo() {
    hide();
}

void TagEditor::MakeClean() {
    remove(m_Cover);
    remove(m_Artist);
    remove(m_Title);
    remove(m_Album);
    remove(m_Genre);
    remove(m_Album_label);
    remove(m_Title_label);
    remove(m_Artist_label);
    remove(m_Genre_label);
}

void TagEditor::editTags() {
    //set each entry as editable
    m_Artist.set_editable();
    m_Title.set_editable();
    m_Album.set_editable();
    m_Genre.set_editable();

    //focus settings
    m_Artist.set_can_focus(true);
    m_Title.set_can_focus(true);
    m_Album.set_can_focus(true);
    m_Genre.set_can_focus(true);

    m_Artist.set_has_frame(true);
    m_Title.set_has_frame(true);
    m_Album.set_has_frame(true);
    m_Genre.set_has_frame(true);
    //set limitations for text

}

void TagEditor::saveTags() {
    //set each entry as non-editable
    m_Artist.set_editable(false);
    m_Title.set_editable(false);
    m_Album.set_editable(false);
    m_Genre.set_editable(false);

    m_Artist.set_can_focus(false);
    m_Title.set_can_focus(false);
    m_Album.set_can_focus(false);
    m_Genre.set_can_focus(false);

    m_Artist.set_has_frame(false);
    m_Title.set_has_frame(false);
    m_Album.set_has_frame(false);
    m_Genre.set_has_frame(false);

    //refresh buffer m_info
    m_info = getChanges();
}

void TagEditor::discardTags() {
    auto [artist, title, album, genre, path] = m_info;

    //set text from buffer
    m_Artist.set_text(artist);
    m_Title.set_text(title);
    m_Album.set_text(album);
    m_Genre.set_text(genre);

    m_Artist.set_editable(false);
    m_Title.set_editable(false);
    m_Album.set_editable(false);
    m_Genre.set_editable(false);

    m_Artist.set_can_focus(false);
    m_Title.set_can_focus(false);
    m_Album.set_can_focus(false);
    m_Genre.set_can_focus(false);

    m_Artist.set_has_frame(false);
    m_Title.set_has_frame(false);
    m_Album.set_has_frame(false);
    m_Genre.set_has_frame(false);
}

SongInfo TagEditor::getChanges() {
    return std::make_tuple(std::string(m_Artist.get_text().c_str()), std::string(m_Title.get_text().c_str()),
                           std::string(m_Album.get_text().c_str()), std::string(m_Genre.get_text().c_str()), std::get<4>(m_info));
}
