#include "window.hpp"


int main(int argc, char* argv[]) {
    MainWindow main_window;

    main_window.createWindow();
    main_window.mainLoop();

    return 0;
}
