cmake_minimum_required(VERSION 3.19)
project(qtlean)
message("Sources: ${CMAKE_SOURCE_DIR}")
message("Build: ${CMAKE_BINARY_DIR}")

# Set vars
set(CMAKE_CXX_STANDARD 17)
set(QT_FEATURE_glib:INTERNAL ON)
set(QT_FEATURE_glibc:INTERNAL ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)
set(ASSETS src/assets)

# Includes
include(FindPackageHandleStandardArgs)

# Find reqs
find_package(Python3 3.6 EXACT COMPONENTS Interpreter Development)
message("Python3.6 library files: ${Python3_LIBRARIES}")
find_library(MONO NAMES mono-2.0)
message("Mono found: ${MONO}")
find_library(LIBMONO NAMES mono-native libmono-native)
message("LIBMONONATIVE found: ${LIBMONO}")
find_library(LIBMONOSGEN NAMES monosgen monosgen-2.0 libmonosgen libmonosgen-2.0)
message("LIBMONOSGEN found: ${LIBMONOSGEN}")
find_library(LIBTBB NAMES libtbb tbb)
message("LIBTBB found: ${LIBTBB}")

if (NOT Python3_LIBRARIES)
    message(WARNING "Python configuration could not be completed automatically. Please specify it youself under Lean/Common/Python/PythonRuntime.dll.config after installation.")
endif ()

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()
# Config
execute_process(COMMAND ${CMAKE_SOURCE_DIR}/configure ${CMAKE_SOURCE_DIR} ${Python3_LIBRARIES})
message("Moving assets")
execute_process(COMMAND cp -r ${CMAKE_SOURCE_DIR}/src/assets ${CMAKE_BINARY_DIR}/assets)


# Building
add_executable(${PROJECT_NAME} src/main.cpp src/QJsonModel.cpp src/QJsonModel.h src/TreeEditor.h src/TreeEditor.cpp src/MainWindow.cpp src/MainWindow.h src/MonoContainer.cpp src/MonoContainer.h)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} stdc++fs ${MONO} ${LIBMONO} ${LIBMONOSGEN} ${LIBTBB})

add_custom_target(copy_asset_files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        ${CMAKE_BINARY_DIR}/assets)
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${PROJECT_BINARY_DIR})
install(DIRECTORY ${ASSETS} DESTINATION ${PROJECT_BINARY_DIR})