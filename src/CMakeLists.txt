cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 2.0 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_compile_options(-std=c++17 -g -Wall -Wextra -Werror)
set (CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Wextra -Werror"
    )
    
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Single Directory for all"
    )

    # find_package(OpenGL REQUIRED)
    # find_package(GLUT REQUIRED)
    # find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets OpenGL REQUIRED)
    
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS GLUT)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS GLUT)

set(PROJECT_SOURCES
        main.cpp
        View/mainwindow.cc
        View/glwidget.cc
        View/stylehelper.cc
        View/mainwindow.ui
        View/res/res.qrc
        Model/model.cc
        Model/parser.cc
        Model/affine.cc
        Model/parser.cc
        Controller/controller.cc
)

set(QGIFIMAGE
        Libs/gifimage/qgifimage.cpp
        Libs/3rdParty/giflib/dgif_lib.c
        Libs/3rdParty/giflib/gif_lib.h
        Libs/3rdParty/giflib/egif_lib.c
        Libs/3rdParty/giflib/gif_err.c
        Libs/3rdParty/giflib/gif_font.c
        Libs/3rdParty/giflib/gif_hash.c
        Libs/3rdParty/giflib/gifalloc.c
        Libs/3rdParty/giflib/quantize.c
)

#add_library(gifimage STATIC Libs/gifimage/qgifimage.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${QGIFIMAGE}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer SHARED
            ${PROJECT_SOURCES}
            ${QGIFIMAGE}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer
            ${PROJECT_SOURCES}
            ${QGIFIMAGE}
        )
    endif()
endif()

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    ${OPENGL_LIBRARIES}
#    gifimage
    # ${GLUT_LIBRARY}
    )

set_target_properties(3DViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION} 
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()

include(CTest)
enable_testing()

add_subdirectory(tests)
