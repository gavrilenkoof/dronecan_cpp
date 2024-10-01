find_package(Qt6
    REQUIRED
    COMPONENTS
        Core
        QuickWidgets
        Widgets
        Qml
)


qt_add_library(dronecan_cpp STATIC
    dronecanapp.h
    dronecanapp.cc
    toolsbox.h
    toolsbox.cc
)

add_subdirectory(Core)


target_link_libraries(dronecan_cpp
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Core
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
)


