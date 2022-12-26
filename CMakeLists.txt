cmake_minimum_required(VERSION 3.5)

project(GraphProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES GraphProject_ru_RU.ts)

set(PROJECT_SOURCES
        main.cpp
        src/View/mainwindow.ui
        src/View/mainwindow.h
        src/View/mainwindow.cpp
        src/View/mainwindow.ui
        src/View/ui_mainwindow.h
        src/IObservable.h
        src/IObserver.h
        src/SolverModel/AdjacencyMatrix.cpp
        src/SolverModel/AdjacencyMatrix.h
        src/SolverModel/Graph.cpp
        src/SolverModel/Graph.h
        src/SolverModel/GraphSplitter.h
        src/SolverModel/SolverModel.cpp
        src/SolverModel/SolverModel.h
        src/SolverModel/SplitAlgorithms/GetAllHyperCubes.cpp
        src/SolverModel/SplitAlgorithms/GetAllGrids.cpp
        src/SolverModel/SplitAlgorithms/GetAllBinaryTrees.cpp
        src/SolverModel/SplitAlgorithms/GetAllLines.cpp
        ${TS_FILES}
        src/View/ViewEdge.cpp src/View/ViewEdge.h
        src/View/ViewVertex.cpp src/View/ViewVertex.h src/View/GraphWidget.cpp src/View/GraphWidget.h src/View/ViewAbstractFactory.h src/View/itemdelegate.h)

qt_wrap_ui(PROJECT_SOURCES src/View/mainwindow.ui)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GraphProject
        MANUAL_FINALIZATION
        MACOSX_BUNDLE
        ${app_icon_macos}
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GraphProject APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(GraphProject SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GraphProject
                ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(GraphProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(GraphProject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS GraphProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GraphProject)
endif()


