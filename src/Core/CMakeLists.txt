find_package(Qt6
    REQUIRED
    COMPONENTS
        Core
        QuickWidgets
        Widgets
)

qt_add_library(Core STATIC
    dccore.h
    dccore.cc
)


target_link_libraries(Core
    PRIVATE
        Qt6::Quick
    PUBLIC
        Qt6::Core
        Qt6::QuickWidgets
        Qt6::Widgets
)




target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
