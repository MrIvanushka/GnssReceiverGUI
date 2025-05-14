#include "EditorWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QFileDialog>
#include <QMenuBar>
#include <QAction>

#include "GraphWidget.h"
#include "LogWidget.h"
#include "LauncherWidget.h"
#include "MapWidget.h"
#include "RawDataWidget.h"
#include "SatelliteWidget.h"
#include "StatWidget.h"

#include "Ads/SectionTitleWidget.h"
#include "GnssProcessor.h"

using namespace Editor::GUI;

EditorWidget::EditorWidget()
{
	_context = std::make_shared<Context>(std::move(std::make_unique<gnssRecv::GnssProcessor>()));

	resize(1920, 1080);
	QMenu* windowMenu = menuBar()->addMenu(QString::fromLocal8Bit("Окно"));

	_container = new ContainerWidget();
	this->setCentralWidget(_container);

	auto logModule = new LogWidget;
	auto graphModule = new GraphWidget;
	auto launcherModule = new LauncherWidget;
	auto mapModule = new MapWidget;
	auto rawDataModule = new RawDataWidget;
	auto satelliteModule = new SatelliteWidget;
	auto statModule = new StatWidget;
	_widgets = { logModule, graphModule, launcherModule, mapModule, rawDataModule, satelliteModule, statModule };

	makeSection(graphModule, TopDropArea);
	makeSection(launcherModule, TopDropArea);
	makeSection(satelliteModule, BottomDropArea);
	auto mapSection = makeSection(mapModule, RightDropArea);
	makeSection(logModule, BottomDropArea, mapSection);
	auto statSection = makeSection(statModule, RightDropArea);
	makeSection(rawDataModule, BottomDropArea, statSection);

	auto madeMenu = _container->createContextMenu();

	for(auto action : madeMenu->actions())
		windowMenu->addAction(action);
}

SectionWidget* EditorWidget::makeSection(Editor::ModuleWidget* widget, DropArea dropArea, SectionWidget* parent)
{
	widget->init(_context);
	auto section = SectionContent::newSectionContent(widget->info().name(), _container, new QLabel(widget->info().name()), widget);
	if (dropArea != InvalidDropArea)
	{
		return _container->addSectionContent(section, parent, dropArea);
	}
	else
	{
		_container->addSectionContent(section, NULL, CenterDropArea);
		_container->hideSectionContent(section);
		return nullptr;
	}
}