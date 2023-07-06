cmake_minimum_required(VERSION 3.16)

project(SAST_Evento VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(FLUENTUI_BUILD_EXAMPLES OFF)
set(FLUENTUI_BUILD_FRAMELESSHEPLER OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSAST_Evento
    main.cpp
)

qt_add_qml_module(appSAST_Evento
    URI SAST_Evento
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(appSAST_Evento PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSAST_Evento
    PRIVATE Qt6::Quick
    fluentuiplugin
)

install(TARGETS appSAST_Evento
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(FluentUI)
