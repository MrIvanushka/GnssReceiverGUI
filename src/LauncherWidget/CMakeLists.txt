project(LauncherWidget LANGUAGES CXX)

find_package(Qt5Widgets        REQUIRED)
find_package(Qt5Gui            REQUIRED)

set ( RESOURCES Resources/launcherResources.qrc)
qt5_add_resources(RESOURCES_QRCS ${RESOURCES})

set(ModuleWidget
	src/LauncherWidget.cpp
	src/LauncherWidget.h
)
source_group(ModuleWidget FILES ${ModuleWidget})

set(Interfaces
	src/IDataInputFactoryWidget.h
)
source_group(Interfaces FILES ${Interfaces})

set(FileInput
	src/FileInput.h
	src/FileInput.cpp
	src/FileInputFactoryWidget.h
	src/FileInputFactoryWidget.cpp
)
source_group(FileInput FILES ${FileInput})

add_library(${PROJECT_NAME} STATIC
	${FileInput}
	${Interfaces}
	${ModuleWidget}

	${RESOURCES_QRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC ../Context/src)

target_link_libraries(${PROJECT_NAME}
	PUBLIC Context
)

target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_link_libraries (${PROJECT_NAME} PUBLIC Qt5::Gui)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)