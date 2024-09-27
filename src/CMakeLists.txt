find_package(Qt6
    REQUIRED
    COMPONENTS
        Core
        QuickWidgets
        Widgets
)



qt_add_library(dronecan_cpp STATIC
    dronecanapp.cc
    dronecanapp.h
)


target_link_libraries(dronecan_cpp
    PRIVATE
        Qt6::Quick
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
)
