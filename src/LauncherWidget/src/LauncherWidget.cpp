#include "LauncherWidget.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QStackedLayout>

#include "FileInputFactoryWidget.h"

using namespace Editor;
using namespace Editor::GUI;

LauncherWidget::LauncherWidget()
{
	auto lay = new QVBoxLayout;
	setLayout(lay);

	auto formLay = new QFormLayout;
	lay->addLayout(formLay);
	formLay->setContentsMargins(0, 0, 0, 0);

	_protocolTypeSelector = new QComboBox;
	formLay->addRow(QString::fromLocal8Bit("Тип навигационных данных"), _protocolTypeSelector);
	_protocolTypeSelector->addItem("GPS");
	
	_dataInputTypeSelector = new QComboBox;
	formLay->addRow(QString::fromLocal8Bit("Способ приёма входных данных"), _dataInputTypeSelector);

	_dataInputFactories.append(new FileInputFactoryWidget);
	auto stackedLay = new QStackedLayout;
	lay->addLayout(stackedLay);
	stackedLay->setContentsMargins(0, 0, 0, 0);

	for (auto inputFactory : _dataInputFactories)
	{
		_dataInputTypeSelector->addItem(inputFactory->name());
		stackedLay->addWidget(inputFactory);
	}

	_startButton = new QPushButton(QString::fromLocal8Bit("Старт"));
	QObject::connect(_startButton, &QPushButton::clicked, this, &LauncherWidget::handleStartButtonClick);
	lay->addWidget(_startButton);

	QObject::connect(_dataInputTypeSelector, SIGNAL(currentIndexChanged(int)), stackedLay, SLOT(setCurrentIndex(int)));
}

void LauncherWidget::init(std::shared_ptr<IContext> context)
{
	_context = context;

	QObject::connect(_context.get(), &IContext::restarted, this, &LauncherWidget::handleStart);
	QObject::connect(_context.get(), &IContext::stopped, this, &LauncherWidget::handleStop);
}

const Info& LauncherWidget::info() const
{
	return _info;
}

void LauncherWidget::handleStart()
{
	_startButton->setText(QString::fromLocal8Bit("Стоп"));

	for (auto inputFactory : _dataInputFactories)
		inputFactory->setEnabled(false);

	_protocolTypeSelector->setEnabled(false);
	_dataInputTypeSelector->setEnabled(false);
}

void LauncherWidget::handleStop()
{
	_startButton->setText(QString::fromLocal8Bit("Старт"));

	for (auto inputFactory : _dataInputFactories)
		inputFactory->setEnabled(true);

	_protocolTypeSelector->setEnabled(true);
	_dataInputTypeSelector->setEnabled(true);
}

void LauncherWidget::handleStartButtonClick()
{
	if (_context->running())
	{
		_context->stop();
		return;
	}

	auto input = _dataInputFactories[_dataInputTypeSelector->currentIndex()]->makeInput();
	if (!input)
		return;
	_context->restart(gnssRecv::ProtocolType::GPS, input);

	QObject::connect(input.get(), &IEditorDataInput::sentAll, _context.get(), &IContext::stop);
}