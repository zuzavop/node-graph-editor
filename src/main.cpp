#include "window.h"

int main(int argc, char* argv[]) {
    MainWindow main_window;

    if (main_window.createWindow()) {
        main_window.mainLoop();
    } else {
        return 1;
    }

    return 0;
}
