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
    toolbox.h
    toolbox.cc
)

add_subdirectory(Core)
add_subdirectory(QmlControls)


target_link_libraries(dronecan_cpp
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Core
        QmlControls
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
)


