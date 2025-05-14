project(EditorWidget LANGUAGES CXX)

find_package(Qt5Widgets        REQUIRED)
find_package(Qt5Gui            REQUIRED)

add_library(${PROJECT_NAME} STATIC
	src/EditorWidget.h
	src/EditorWidget.cpp
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ../AdvancedDockingSystem/include
	PUBLIC ../GraphWidget/src
	PUBLIC ../LauncherWidget/src
	PUBLIC ../LogWidget/src
	PUBLIC ../MapWidget/src
	PUBLIC ../RawDataWidget/src
	PUBLIC ../SatelliteWidget/src
	PUBLIC ../StatWidget/src
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC GraphWidget
	PUBLIC LauncherWidget
	PUBLIC LogWidget
	PUBLIC MapWidget
	PUBLIC RawDataWidget
	PUBLIC SatelliteWidget
	PUBLIC StatWidget
)

target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Gui)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)