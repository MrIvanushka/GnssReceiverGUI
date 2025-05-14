#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QFileInfo>


#include "Context.h"
#include "ModuleWidget.h"

#include "ads/ContainerWidget.h"
#include "ads/SectionContent.h"

namespace Editor
{
namespace GUI
{

class EditorWidget : public QMainWindow
{
	Q_OBJECT
public:
	EditorWidget();
private:
	SectionWidget* makeSection(Editor::ModuleWidget* widget, DropArea dropArea = DropArea::InvalidDropArea, SectionWidget* parent = nullptr);
private:
	std::shared_ptr<Context> _context;

	ContainerWidget* _container;
	QList<ModuleWidget*> _widgets;
};

}
}