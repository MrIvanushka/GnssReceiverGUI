#include "RawDataWidget.h"

#include <QVBoxLayout>
#include <QFormLayout>

#include "SatClockTable.h"
#include "EphemerisTable.h"
#include "Log.h"

using namespace Editor;
using namespace Editor::GUI;

RawDataWidget::RawDataWidget()
{
	auto lay = new QVBoxLayout;
	setLayout(lay);
	auto formLay = new QFormLayout;
	lay->addLayout(formLay);
	formLay->setContentsMargins(0, 0, 0, 0);

	_tableSelector = new QComboBox;
	formLay->addRow(QString::fromLocal8Bit("“ип навигационных данных"), _tableSelector);
	_tableSelector->setEnabled(false);

	_stackedLay = new QStackedLayout;
	lay->addLayout(_stackedLay);
	_stackedLay->setContentsMargins(0, 0, 0, 0);

	QObject::connect(_tableSelector, SIGNAL(currentIndexChanged(int)), _stackedLay, SLOT(setCurrentIndex(int)));
}

void RawDataWidget::init(std::shared_ptr<IContext> context)
{
	_context = context;

	QObject::connect(_context.get(), &IContext::restarted, this, &RawDataWidget::onStart);
}

const Info& RawDataWidget::info() const
{
	return _info;
}

void RawDataWidget::onStart()
{
	clearLayout(_stackedLay);
	_tableSelector->clear();
	_tableSelector->setEnabled(true);

	if (_context->storage()->protocolType() != gnssRecv::ProtocolType::GPS)
	{
		LOG_WARN("A widget cannot show data of current protocol");
		return;
	}

	auto satClockTable = new SatClockTable;
	auto ephemerisTable = new EphemerisTable;

	_stackedLay->addWidget(satClockTable);
	_stackedLay->addWidget(ephemerisTable);

	_tableSelector->addItem(QString::fromLocal8Bit("—путниковое врем€"));
	_tableSelector->addItem(QString::fromLocal8Bit("Ёфемеридные данные"));

	QObject::connect(_context.get(), &IContext::requestedStatUpdate, satClockTable,
		[satClockTable, ephemerisTable, this]()
		{
			satClockTable->update(_context);
			ephemerisTable->update(_context);
		});
}

void RawDataWidget::clearLayout(QLayout* lay)
{
	QLayoutItem* item;
	while ((item = lay->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}