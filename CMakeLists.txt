cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(IOS)
    add_definitions(-DIOS)
endif()

if(ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/android/android")
endif()


project(unixcmd LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

set(basic_setup_args KEEP_RPATHS)

if(ANDROID)
    set(basic_setup_args ${basic_setup_args} NO_OUTPUT_DIRS)
endif()

conan_basic_setup(${basic_setup_args})

find_package(
    Qt6
        COMPONENTS
            Core
            Widgets
            Qml
            Quick
            QuickControls2
            QuickTemplates2
            QmlWorkerScript
        REQUIRED
)

if(ANDROID)
    add_library(unixcmd SHARED)
    set_property(
        TARGET
            unixcmd
        PROPERTY
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/android-build/libs/${ANDROID_ABI}"
    )
else()
    add_executable(unixcmd)

    #add_definitions(-DBUILD_STATIC)
endif()

set(
    SOURCES
        qml/main.qml
        src/DirectoryView.cpp
        src/DirectoryView.h
        src/DirectoryViewModel.cpp
        src/DirectoryViewModel.h
        src/UnixCmdWindow.cpp
        src/UnixCmdWindow.h
)

qt6_add_resources(SOURCES qml.qrc)

target_sources(unixcmd PUBLIC main.cpp ${SOURCES})

target_link_libraries(
    unixcmd
        Qt6::Widgets
        Qt6::Qml
        Qt6::QmlModels
        Qt6::QmlWorkerScript
        Qt6::QuickTemplates2
        Qt6::QuickControls2
        Qt6::Quick
        Qt6::Gui
        Qt6::Core
        Qt6::Network
)

target_link_directories(
    unixcmd
        PRIVATE
            ${CONAN_QT_ROOT}/plugins/platforms
            ${CONAN_QT_ROOT}/qml/QtQml
            ${CONAN_QT_ROOT}/qml/QtQuick.2
            ${CONAN_QT_ROOT}/qml/QtQml/Models.2
            ${CONAN_QT_ROOT}/qml/QtQml/WorkerScript.2
            ${CONAN_QT_ROOT}/qml/QtQuick/Controls.2
            ${CONAN_QT_ROOT}/qml/QtQuick/Window.2
            ${CONAN_QT_ROOT}/qml/QtQuick/Layouts
            ${CONAN_QT_ROOT}/qml/QtQuick/Templates.2
            ${CONAN_QT_ROOT}/qml/Qt/labs/qmlmodels
)

if(IOS)
    if(IS_CI_BUILD)
        set_property(TARGET unixcmd PROPERTY XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Sign identity")
        set_property(TARGET unixcmd PROPERTY XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "TeamID")
        set_property(TARGET unixcmd PROPERTY XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO")
    endif()

    set_property(TARGET unixcmd APPEND_STRING PROPERTY LINK_FLAGS " -Wl,-e,_qt_main_wrapper")

    set_target_properties(
        unixcmd
            PROPERTIES
                MACOSX_BUNDLE TRUE
                MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/ios/Info.plist"
                XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
                XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES FALSE
                XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
                XCODE_ATTRIBUTE_ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon"
    )
endif()
