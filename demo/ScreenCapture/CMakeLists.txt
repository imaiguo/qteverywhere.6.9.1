
cmake_minimum_required(VERSION 3.31)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(APPNAME "FloatWidget")
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
        ./src/Capture.cpp
)

add_executable(${APPNAME}
    ${SRC}
)

target_link_libraries(${APPNAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)
