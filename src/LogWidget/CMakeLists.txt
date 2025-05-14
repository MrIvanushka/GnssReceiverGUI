project(LogWidget LANGUAGES CXX)

find_package(Qt5Widgets        REQUIRED)
find_package(Qt5Gui            REQUIRED)

set ( RESOURCES Resources/logResources.qrc)
qt5_add_resources(RESOURCES_QRCS ${RESOURCES})

add_library(${PROJECT_NAME} STATIC
	src/LogTable.h
	src/LogTable.cpp
	src/LogTableModel.h
	src/LogTableModel.cpp
	src/LogFilterPanel.h
	src/LogFilterPanel.cpp
	src/LogWidget.h
	src/LogWidget.cpp
	src/LogMessage.h

	${RESOURCES_QRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC ../Context/src)

target_link_libraries(${PROJECT_NAME}
	PUBLIC Context
)

target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Gui)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)