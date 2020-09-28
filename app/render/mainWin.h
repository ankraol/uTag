#pragma once

#include <string>
#include <gtkmm.h>
#include <iostream>
#include <tuple>
#include <array>
#include <utility>
#include "../src/setTags.h"
#include "../src/getDirs.h"
#include "DirectoryChooser.h"
#include "Dir.h"
#include "AudioList.h"

class mainWin : public Gtk::Window {
public:
    explicit mainWin(const std::string& dirName = "");
    ~mainWin();

    void AddWidgets(std::string &dirName);

protected:
    //signal handlers
    void main_openDir(std::string& path);

    //class members
    AudioList* m_AudioList_Box;
    DirectoryChooser* m_dirChooser;

    //GTK objects
    Gtk::Box m_mainTripleBox;

    friend void ::Dir::openDir();
    friend void ::DirectoryChooser::prevDir();
};
