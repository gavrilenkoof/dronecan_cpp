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
add_subdirectory(Connection)


target_link_libraries(dronecan_cpp
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Core
        Connection
        QmlControls
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
)


target_include_directories(dronecan_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
