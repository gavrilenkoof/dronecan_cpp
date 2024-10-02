find_package(Qt6
    REQUIRED
    COMPONENTS
        Core
        QuickWidgets
        Widgets
        Qml
        Quick
        Gui
)

qt_add_library(QmlControls STATIC
    dcpallete.h
    dcpallete.cc
)


target_link_libraries(QmlControls
    PRIVATE
        Qt6::Quick
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
        Qt6::Gui
)




target_include_directories(QmlControls PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
