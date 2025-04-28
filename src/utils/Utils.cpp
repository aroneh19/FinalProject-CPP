#include "utils/Utils.h"
#include <cstdlib>


namespace Utils {
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    int getRandomInt(int min, int max) {
        return rand() % (max - min + 1) + min;
    }
}