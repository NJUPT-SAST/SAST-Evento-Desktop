cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/.cmake/)
include(GetGitRevisionDescription)

project(SAST_Evento_Desktop VERSION 0.3 LANGUAGES CXX)

set(FLUENTUI_BUILD_EXAMPLES OFF)

add_subdirectory(libs)

#配置通用编译
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "" FORCE)
endif()

#设置可执行文件输出目录
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/debug)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/release)
endif()

find_package(Qt6 REQUIRED COMPONENTS Quick Svg Network HttpServer Concurrent)

if(QT_VERSION VERSION_GREATER_EQUAL "6.3")
    qt_standard_project_setup()
else()
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    SAST_Evento.qrc
)

file(GLOB_RECURSE SOURCE_IMPORT_PATHS
    ${CMAKE_SOURCE_DIR}/src/controller/ui/*.h
    ${CMAKE_SOURCE_DIR}/src/controller/ui/*.cpp
    ${CMAKE_SOURCE_DIR}/src/domain/model/*.h
    ${CMAKE_SOURCE_DIR}/src/domain/model/*.cpp
)
foreach(filepath ${SOURCE_IMPORT_PATHS})
    string(REPLACE "${CMAKE_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND SOURCE_IMPORT_FILES ${filename})
endforeach(filepath)

if(QT_KNOWN_POLICY_QTP0001)
    qt_policy(SET QTP0001 OLD)
endif()

set(VERSION_RC_PATH "")
set(WIN32_MANIFEST_PATH "")
if(WIN32)
    set(VERSION_RC_PATH ${CMAKE_SOURCE_DIR}/SAST_Evento.rc)
    configure_file(
        ${CMAKE_SOURCE_DIR}/.cmake/version_exe.rc.in
        ${VERSION_RC_PATH}
    )
    configure_file(
        ${CMAKE_SOURCE_DIR}/.cmake/InstallerScript.iss.in
        ${CMAKE_SOURCE_DIR}/action-cli/InstallerScript.iss
    )
    set(WIN32_MANIFEST_PATH ${CMAKE_SOURCE_DIR}/app.manifest)
endif()

if(APPLE)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})

    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${spectral_VERSION})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${spectral_VERSION})

    set(ICON_NAME "app.icns")
    set(${PROJECT_NAME}_MAC_ICON "${CMAKE_SOURCE_DIR}/${ICON_NAME}")
    set(MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})
    set_property(SOURCE "${${PROJECT_NAME}_MAC_ICON}" PROPERTY
        MACOSX_PACKAGE_LOCATION Resources)
endif()

#添加可执行文件
qt_add_executable(SAST_Evento_Desktop MACOSX_BUNDLE
    ${${PROJECT_NAME}_MAC_ICON}
    ${SOURCE_FILES}
    ${VERSION_RC_PATH}
    ${WIN32_MANIFEST_PATH}
)

qt_add_qml_module(SAST_Evento_Desktop
    URI SAST_Evento
    VERSION 1.0
    SOURCES ${SOURCE_IMPORT_FILES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/.cmake/Info.plist.in")

target_include_directories(SAST_Evento_Desktop
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/src/controller
    ${CMAKE_SOURCE_DIR}/src/controller/ui
    ${CMAKE_SOURCE_DIR}/src/domain/entity
    ${CMAKE_SOURCE_DIR}/src/domain/model
    ${CMAKE_SOURCE_DIR}/src/domain/exception
    ${CMAKE_SOURCE_DIR}/src/infrastructure
    ${CMAKE_SOURCE_DIR}/src/infrastructure/helper
    ${CMAKE_SOURCE_DIR}/libs/Qt-Based-JsonDeserialiser
)

#设置属性
set_target_properties(SAST_Evento_Desktop PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

#链接库
if (FLUENTUI_BUILD_STATIC_LIB)
    target_link_libraries(SAST_Evento_Desktop PRIVATE
        Qt6::Quick
        Qt6::Svg
        Qt6::Network
        Qt6::HttpServer
        Qt6::Concurrent
        fluentui
        fluentuiplugin
        FramelessHelper::Core
        FramelessHelper::Quick
    )
else()
    target_link_libraries(SAST_Evento_Desktop PRIVATE
        Qt6::Quick
        Qt6::Svg
        Qt6::Network
        Qt6::HttpServer
        Qt6::Concurrent
        fluentuiplugin
        FramelessHelper::Core
        FramelessHelper::Quick
    )
endif()

#安装
install(TARGETS SAST_Evento_Desktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
