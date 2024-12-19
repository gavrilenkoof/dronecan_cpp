find_package(Qt6
    REQUIRED
    COMPONENTS
        QuickWidgets
        Widgets
        SerialPort
)

qt_add_library(Connection STATIC
    linkserial.h
    linkserial.cc
    linkmanager.h
    linkmanager.cc
)


target_link_libraries(Connection
    PRIVATE
        Qt6::Quick
        dronecan_cpp
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
        Qt6::SerialPort
        Core
)




target_include_directories(Connection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
