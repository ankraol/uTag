#include <iostream>
#include "src/AudioFileInfo.h"
#include "render/mainWin.h"
#include "src/getDirs.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        auto app = Gtk::Application::create();
        mainWin main_win;
        return app->run(main_win);
    } else if (argc == 2) {
        auto app = Gtk::Application::create();
        mainWin main_win("./" + std::string(argv[1])); //check if dir is already starts with ./
        return app->run(main_win);
    } else {
        std::cerr << "usage: ./utag [directory]\n";
    }
    return 0;
}
