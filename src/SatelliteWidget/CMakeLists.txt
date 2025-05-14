project(SatelliteWidget LANGUAGES CXX)

find_package(Qt5Widgets        REQUIRED)
find_package(Qt5Gui            REQUIRED)

add_library(${PROJECT_NAME} STATIC
	src/SatelliteTable.h
	src/SatelliteTable.cpp
	src/SatelliteWidget.h
	src/SatelliteWidget.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ../Context/src)

target_link_libraries(${PROJECT_NAME}
	PUBLIC Context
)

target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Gui)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)