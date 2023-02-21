#include "window.hpp"


int main(int argc, char* argv[]) {
    MainWindow main_window;

    main_window.create_window();
    main_window.main_loop();

    return 0;
}
