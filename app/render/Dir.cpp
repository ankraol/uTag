//
// Created by Anastasiia Krasnoselska on 9/28/20.
//

#include "Dir.h"

#include <utility>
#include "mainWin.h"

void Dir::openDir() {
    m_winPointer->main_openDir(m_dirPath);
}

Dir::Dir(const std::string& dirName, std::string  dirPath, mainWin* winPointer)
        : m_dirName_Label(dirName), m_dirPath(std::move(dirPath)), m_winPointer(winPointer) {
    //set button
    set_relief(Gtk::ReliefStyle::RELIEF_NONE);

    //set main box
    m_buttonBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    //set folder icon
    Glib::RefPtr<Gdk::Pixbuf> pb = ((Gdk::Pixbuf::create_from_file("app/resources/macFolder_icon.png", 20, 20)));
    m_dirImage.set(pb);
    m_dirImage.set_margin_right(10);

    //connect signals
    signal_clicked().connect(sigc::mem_fun(*this, &Dir::openDir));

    //pack image and label
    m_buttonBox.pack_start(m_dirImage, Gtk::PackOptions::PACK_SHRINK);
    m_buttonBox.pack_start(m_dirName_Label);

    //add and show child Widgets
    add(m_buttonBox);
    show_all_children();
}
