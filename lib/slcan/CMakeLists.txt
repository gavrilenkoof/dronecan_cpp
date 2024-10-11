cmake_minimum_required(VERSION 3.5)

if (POLICY CMP0048)
        cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)
project(slcan C CXX)


set(SLCAN_CPP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SLCAN_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

# Determine if the library is built as a subproject (using add_subdirectory) or if it is the main project.
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(MAIN_PROJECT ON)
endif()



add_library(slcan
    STATIC
        serialcan.cpp
        framecan.cpp
)

#target_link_libraries(slcan PUBLIC slcan_parser slcan_health_and_arming_checks slcan_receive)
install(TARGETS slcan
                EXPORT slcan
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/slcan)
install(EXPORT slcan
                FILE slcan.cmake
                DESTINATION lib/cmake/slcan
)


install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/slcanConfig.cmake
        DESTINATION lib/cmake/slcan
)
export(EXPORT slcan
              FILE "${CMAKE_CURRENT_BINARY_DIR}/slcan.cmake"
)

