find_package(Qt6
    REQUIRED
    COMPONENTS
        Core
        QuickWidgets
        Widgets
)


qt_add_library(dronecan_cpp STATIC
    dronecanapp.h
    dronecanapp.cc
    dronecansetup.h
    dronecansetup.cc
    dronecanmain.cc
    dronecanmain.h
)

add_subdirectory(Core)


target_link_libraries(dronecan_cpp
    PRIVATE
        Qt6::Quick
        Core
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
)
