project(MapWidget LANGUAGES CXX)

find_package(Qt5 REQUIRED COMPONENTS Location)
find_package(Qt5Widgets        REQUIRED)
find_package(Qt5Gui            REQUIRED)

add_subdirectory(QGeoViewMapWidget)

add_library(${PROJECT_NAME} STATIC
	src/MapWidget.h
	src/MapWidget.cpp

	src/Placemark.h
	src/Placemark.cpp
	
	${RESOURCES_QRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC ../Context/src)

target_link_libraries(${PROJECT_NAME}
	PUBLIC Context
	PUBLIC qgeoview
)

target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Gui)
target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Location)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)