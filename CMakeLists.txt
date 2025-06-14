cmake_minimum_required(VERSION 3.20)
project(AxiomArmDriver VERSION 0.1.0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(PROJECT_CXX_STANDARD ${CMAKE_CXX_STANDARD})

option(BUILD_AXARM_DRIVER_EXAMPLE "Build AxiomArmDriver Example." ON)

include(AxiomArmDriverFindHyPWM)

file(GLOB_RECURSE AXARM_DRIVER_SOURCES src/*.cpp)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${AXARM_DRIVER_SOURCES})

if (NOT TARGET ${PROJECT_NAME}::${PROJECT_NAME})
    add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
endif ()

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} PUBLIC HyPWM::HyPWM)

if (BUILD_AXARM_DRIVER_EXAMPLE)
    include(AxiomArmDriverExample)
endif ()

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)