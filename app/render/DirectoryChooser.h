#ifndef UTAG_DIRECTORYCHOOSER_H
#define UTAG_DIRECTORYCHOOSER_H

#include <iostream>
#include <string>
#include "gtkmm.h"
#include "../src/getDirs.h"


class mainWin;
class Dir;

class DirectoryChooser : public Gtk::Box {
public:
    explicit DirectoryChooser(const std::string& dirName, mainWin* winPointer);

    void MakeClean();
protected:
    //signal handlers
    void prevDir();

    //members
    mainWin* m_winPointer;
    std::string m_dirName;
    Gtk::Button m_prevDir;
    Gtk::Image m_image;
    Dir_list m_dirName_Path;
    std::list<Dir*> m_dirBoxes;

    //friends
    friend class ::mainWin;
};

#endif //UTAG_DIRECTORYCHOOSER_H
