set -e

cd /cygdrive/c/Users/julia/CLionProjects/MiniGolfe/cmake-build-debug
/cygdrive/c/Users/julia/AppData/Local/JetBrains/CLion2024.1/cygwin_cmake/bin/cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
