cmake_minimum_required(VERSION 3.14)

project(2gis-test VERSION 0.1 LANGUAGES CXX)
set( TARGET_NAME ${PROJECT_NAME} )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Core Qml Quick QuickControls2 Charts REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Qml Quick QuickControls2 Charts REQUIRED)

file( GLOB_RECURSE HEADER_FILES "*.h" )
file( GLOB_RECURSE SOURCE_FILES "*.cpp" )
file( GLOB_RECURSE RESOURCE_FILES "*.qrc" )

add_executable(${TARGET_NAME} WIN32 ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

target_compile_definitions(${TARGET_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${TARGET_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::Charts
)
