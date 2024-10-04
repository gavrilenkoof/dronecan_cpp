find_package(Qt6
    REQUIRED
    COMPONENTS
        Core
        QuickWidgets
        Widgets
        SerialPort
)

qt_add_library(Core STATIC
    dccore.h
    dccore.cc
    linklistener.h
    linklistener.cc
)


target_link_libraries(Core
    PRIVATE
        Qt6::Quick
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
        Qt6::SerialPort
)




target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
