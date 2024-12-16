find_package(Qt6
    REQUIRED
    COMPONENTS
        QuickWidgets
        Widgets
        SerialPort
)

qt_add_library(Core STATIC
    linkmanager.h
    linkmanager.cc
    serialcan.h
    serialcan.cc
    canframe.h
    dccanard.h
    dccanard.cc
    dccanard_iface.h
    dccanard_iface.cc
)


target_link_libraries(Core
    PRIVATE
        Qt6::Quick
        Connection
        dronecan_cpp
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
        Qt6::SerialPort
        canard_tgt
)



target_include_directories(Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${slcan_SOURCE_DIR}
)
