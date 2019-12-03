#include <iostream>
#include <Log/Log.h>

int main() {
    Log::setLevel(Log::LevelDebug);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}