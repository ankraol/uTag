//
// Created by Anastasiia Krasnoselska on 9/28/20.
//

#include "DirectoryChooser.h"
#include "mainWin.h"

DirectoryChooser::DirectoryChooser(const std::string& dirName, mainWin* winPointer) : m_winPointer(winPointer),
                                                                                      m_dirName(dirName) {
    //set box
    set_orientation(Gtk::ORIENTATION_VERTICAL);

    //get directories names and pathes and set boxes
    m_dirName_Path = getDirs(dirName);
    for (const auto& [name, path] : m_dirName_Path) {
        m_dirBoxes.push_back(new Dir(name, path, winPointer));
    }

    //pack boxes into the main box
    for (auto& dirBox : m_dirBoxes)
        pack_start(*dirBox, Gtk::PackOptions::PACK_SHRINK);

    Glib::RefPtr<Gdk::Pixbuf> pb = Gdk::Pixbuf::create_from_file("./app/resources/prevDir.png", 25, 25);
    m_image.set(pb);
    m_prevDir.set_image(m_image);
    m_prevDir.set_relief(Gtk::RELIEF_NONE);
    m_prevDir.set_can_focus(false);
    m_prevDir.set_focus_on_click(false);
    pack_end(m_prevDir, Gtk::PackOptions::PACK_SHRINK);

    //connect signals
    m_prevDir.signal_clicked().connect(sigc::mem_fun(*this, &DirectoryChooser::prevDir));
}

void DirectoryChooser::prevDir() {
    if (m_dirName != ".") {
        std::string prevDir = m_dirName.substr(0, m_dirName.rfind('/'));
        m_winPointer->main_openDir(prevDir);
    }
}

void DirectoryChooser::MakeClean() {
    for (auto& widget : m_dirBoxes)
        remove(*widget);
}
