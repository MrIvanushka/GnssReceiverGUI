#pragma once

#include <QString>
#include <QSortFilterProxyModel>
#include <QCheckbox>
#include <QMenu>
#include "ModuleWidget.h"
#include "CustomPlot.h"

namespace Editor
{
namespace GUI
{

class GraphWidget : public ModuleWidget
{
	Q_OBJECT
public:
	GraphWidget();

	void init(std::shared_ptr<IContext> context) override;

	const Info& info() const override;
private slots:
	void clearGraphs();

	void receiveSignals(IEditorDataInput::RecentDataPtr);
private:
	QMenu* _graphFilterMenu;

	std::shared_ptr<IContext> _context;
	Info _info = Info(QString::fromLocal8Bit("График приёма миллисекундных отсчётов"));

	CustomPlot* _plot;

	int _currentSignalIndex;
	std::unordered_map<int, int> _prnToGraphIndex;
};

}
}