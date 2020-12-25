# CMakeList.txt: проект CMake для ArgusSoftTest; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

find_package(OpenCV REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR}/bin)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (ArgusSoftTest "ArgusSoftTest.cpp" "ArgusSoftTest.h" "MainLoop.cpp" "MainLoop.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

target_link_libraries(ArgusSoftTest ${OpenCV_LIBS})
