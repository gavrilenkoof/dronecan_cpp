cmake_minimum_required(VERSION 3.16)

project(dronecan_cpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


list(APPEND QGC_RESOURCES
    ${CMAKE_SOURCE_DIR}/dronecan.qrc
)

find_package(Qt6 6.2
    COMPONENTS
        Quick
        SerialPort
    REQUIRED
)

qt_add_executable(appdronecan_cpp
    src/main.cc
    ${QGC_RESOURCES}
)



add_subdirectory(lib)
add_subdirectory(src)

#qt_add_qml_module(appdronecan_cpp
#    URI dronecan_cpp
#    VERSION 1.0
#    QML_FILES main.qml
#)

#set_target_properties(appdronecan_cpp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
#    WIN32_EXECUTABLE TRUE
#)

target_link_libraries(appdronecan_cpp
    PUBLIC
        dronecan_cpp
    PRIVATE
        Qt6::Quick
        Qt6::SerialPort

)


