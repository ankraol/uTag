#include "mainWin.h"

#include <utility>

void mainWin::main_openDir(std::string& path) {
    m_AudioList_Box->MakeClean();
    m_dirChooser->MakeClean();
    m_mainTripleBox.remove(*m_AudioList_Box);
    m_mainTripleBox.remove(*m_dirChooser);
    remove();
    AddWidgets(path);
    show_all_children();
}

void mainWin::AddWidgets(std::string &dirName) {
    //pack and set main triple box
    add(m_mainTripleBox);
    m_mainTripleBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    //fill side widget and .mp3 files list
    //no command-line arguments
    if (dirName.empty()) {
        m_dirChooser = new DirectoryChooser(".", this);
        m_AudioList_Box = new AudioList(".");
    } else { //directory name passed as command-line argument
        if (dirName[0] != '.' && dirName[1] != '/')
            dirName += "./";
        m_dirChooser = new DirectoryChooser(dirName, this);
        m_AudioList_Box = new AudioList(dirName);
    }

    //add side widget and .mp3 file listing to _mainBox
    m_mainTripleBox.pack_start(*m_dirChooser, Gtk::PackOptions::PACK_SHRINK);
    m_mainTripleBox.pack_start(*m_AudioList_Box, Gtk::PackOptions::PACK_EXPAND_WIDGET);
}

mainWin::mainWin(const std::string &dirName) {
    std::string m_dirName(dirName);
    //set up window
    set_default_size(900, 600);
    set_title("uTag");
    set_border_width(10);

    //pack and set main triple box
    AddWidgets(m_dirName);
    show_all_children();
}

mainWin::~mainWin() {
    delete m_dirChooser;
    delete m_AudioList_Box;
}
