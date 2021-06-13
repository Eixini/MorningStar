cmake_minimum_required(VERSION 3.5)

project(MorningStar_Reliza LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5Multimedia)

if(ANDROID)
  add_library(MorningStar_Reliza SHARED
    main.cpp
    morningstar.cpp
    morningstar.h
    info.cpp
    info.h
    nettime.cpp
    nettime.h
    note.cpp
    note.h
    randnum.cpp
    randnum.h
    timer.cpp
    timer.h
    radio.cpp
    radio.h
    textanalysis.cpp
    textanalysis.h
    settings.cpp
    settings.h

    notemodel.h
    notemodel.cpp
    notetypedelegate.h
    notetypedelegate.cpp

    morningstar_resources.qrc

    QNixieNumber/qnixienumber.h
    QNixieNumber/qnixienumber.cpp
    QNixieNumber/qnixienumber_resource.qrc
  )
else()
  add_executable(MorningStar_Reliza
    main.cpp
    morningstar.cpp
    morningstar.h
    info.cpp
    info.h
    nettime.cpp
    nettime.h
    note.cpp
    note.h
    randnum.cpp
    randnum.h
    timer.cpp
    timer.h
    radio.cpp
    radio.h
    textanalysis.cpp
    textanalysis.h
    settings.cpp
    settings.h

    notemodel.h
    notemodel.cpp
    notetypedelegate.h
    notetypedelegate.cpp

    morningstar_resources.qrc

    QNixieNumber/qnixienumber.h
    QNixieNumber/qnixienumber.cpp
    QNixieNumber/qnixienumber_resource.qrc
  )
endif()

target_link_libraries(MorningStar_Reliza PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MorningStar_Reliza PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
