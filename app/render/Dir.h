#ifndef UTAG_DIR_H
#define UTAG_DIR_H

#include <iostream>
#include <string>
#include <gtkmm.h>

class mainWin;

class Dir : public Gtk::Button {
public:
    explicit Dir(const std::string& dirName, std::string  dirPath, mainWin* winPointer);

protected:
    //signal handlers
    void openDir();

    //Gtk objects
    Gtk::Box m_buttonBox;
    Gtk::Image m_dirImage;
    Gtk::Label m_dirName_Label;

    //class member
    std::string m_dirPath;
    mainWin* m_winPointer;

    //friends
    friend class ::mainWin;
};
#endif //UTAG_DIR_H
