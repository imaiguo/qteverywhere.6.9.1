
cmake_minimum_required(VERSION 3.31)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(APPNAME "ScreenCaptureCrop")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(${APPNAME} LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

message("current Qt version is[" ${QT_VERSION_MAJOR}  "]")

set(SRC
        ./src/Main.cpp
        ./src/Menu.cpp
        ./src/Screen.cpp
        ./src/ScreenWidget.cpp
        ./src/ButtonWithTip.cpp
        ./src/RoundTip.cpp
        ./src/Tools.cpp
        ./src/FloatButton.cpp
        ./src/hotkey/NativeEventFilter.cpp
        ./src/hotkey/ShortcutRegister.cpp
        icon.rc
        ScreenCapture.qrc
)

include_directories(./src/hotkey)

add_executable(${APPNAME} WIN32
    ${SRC}
)

target_link_libraries(${APPNAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)
