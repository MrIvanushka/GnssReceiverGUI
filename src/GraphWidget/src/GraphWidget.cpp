#include "GraphWidget.h"

#include <QVBoxLayout>
#include <QToolButton>
#include "Log.h"

using namespace Editor;
using namespace Editor::GUI;

GraphWidget::GraphWidget()
{
	auto lay = new QVBoxLayout;
	setLayout(lay);

	auto formLay = new QFormLayout;
	lay->addLayout(formLay);
	formLay->setContentsMargins(0, 0, 0, 0);

	_graphFilterMenu = new QMenu();
	auto toolButton = new QToolButton();
	toolButton->setText(QString::fromLocal8Bit("Выберите..."));
	toolButton->setMenu(_graphFilterMenu);
	toolButton->setPopupMode(QToolButton::InstantPopup);
	toolButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	formLay->addRow(QString::fromLocal8Bit("Фильтр по спутникам"), toolButton);
	QCPRange xrange = { 0, 200 };
	QCPRange yrange = { -1000, 1000 };
	QString ylabel = "Imagine value";
	QString xlabel = "Signal number";

	_plot = new CustomPlot(nullptr);
	_plot->setMinimumSize(400, 300);
	_plot->xAxis->setRange(xrange);
	_plot->xAxis->setLabel(xlabel);
	_plot->yAxis->setRange(yrange);
	_plot->yAxis->setLabel(ylabel);
	_plot->setHorizontalAxisLimit(0);
	//_plot->setVerticalAxisLimit(0);
	_plot->SetEditable(false);
	_plot->legend->setVisible(true);

	lay->addWidget(_plot);
}

void GraphWidget::init(std::shared_ptr<IContext> context)
{
	_context = context;

	QObject::connect(context.get(), &IContext::restarted, this, &GraphWidget::clearGraphs);
	QObject::connect(context.get(), &IContext::receivedSignals, this, &GraphWidget::receiveSignals);
	//_context->addReceiver(this);
}

const Info& GraphWidget::info() const
{
	return _info;
}

void GraphWidget::clearGraphs()
{
	_plot->clearGraphs();
	_currentSignalIndex = 0;
	_prnToGraphIndex.clear();
	_graphFilterMenu->clear();
}

void GraphWidget::receiveSignals(IEditorDataInput::RecentDataPtr data)
{
	if (data->empty())
	{
		_currentSignalIndex += _context->statRequestUpdatePeriodMs();
		return;
	}
	bool graphCountChanged = false;

	QVector<double> keys(data->begin()->second.size());

	for (auto i = 0u; i < keys.size(); ++i)
		keys[i] = _currentSignalIndex + i;
	_currentSignalIndex += keys.size();

	for (const auto& el : *data)
	{
		if (!_prnToGraphIndex.contains(el.first))
		{
			auto idx = _plot->graphCount();
			_prnToGraphIndex[el.first] = idx;
			_plot->addGraph();
			_plot->graph(_plot->graphCount() - 1)->setVisible(false);
			graphCountChanged = true;
			auto name = QString("PRN ") + QString::number(el.first);
			_plot->graph(idx)->setName(name);
			QAction* action = new QAction(name, this);
			action->setCheckable(true);
			action->setChecked(false);
			_graphFilterMenu->addAction(action);
			QObject::connect(action, &QAction::triggered, this, [this, idx](bool enabled) { _plot->graph(idx)->setVisible(enabled); _plot->replot(); });
		}
		auto graphIndex = _prnToGraphIndex[el.first];
		_plot->graph(graphIndex)->addData(keys, el.second);
	}

	auto graphCount = _plot->graphCount();
	for (float i = 0; i < graphCount; ++i)
	{
		_plot->graph(i)->setPen(QPen(QColor(20 + 200.0 / graphCount * i, 70 * (1.6 - i / graphCount), 150, 150), 3));
	}
}