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
    serialcan.h
    serialcan.cc
)


target_link_libraries(Connection
    PRIVATE
        Qt6::Quick
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
        Qt6::SerialPort
)




target_include_directories(Connection PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
