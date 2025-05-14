#include "SatClockTable.h"

#include <QHeaderView>
#include <QSizePolicy>
#include <unordered_map>
#include "Log.h"
#include "IGPSSatStorage.h"

using namespace Editor::GUI;

SatClockTable::SatClockTable()
{
	setModel(&_baseModel);

	setShowGrid(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	horizontalHeader()->setVisible(true);
	verticalHeader()->setVisible(true);

	horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

	setSelectionBehavior(QAbstractItemView::SelectRows);
}

void SatClockTable::update(std::shared_ptr<IContext> context)
{
	_baseModel.clear();

	const auto& availablePRNs = context->storage()->availableSatellites();
	if (availablePRNs.empty())
		return;

	QStringList horizontalHeader;
	for (auto i=0u; i < availablePRNs.size(); ++i)
	{
		horizontalHeader.append(QString::number(availablePRNs[i]));
		auto currentSatStorage = context->storage()->getSatStorage(availablePRNs[i]);
		if (!currentSatStorage)
		{
			LOG_ERROR("Cannot get storage with PRN ", availablePRNs[i]);
			return;
		}
		auto castedStorage = std::dynamic_pointer_cast<const gnssRecv::IGPSSatStorage>(currentSatStorage);
		if (!castedStorage)
		{
			LOG_ERROR("Storage for PRN ", availablePRNs[i], " has no GPS type");
			return;
		}
		auto msg = castedStorage->lastSatClock();

		_baseModel.setItem(0, i, new QStandardItem(QString::number(msg.weekNumber())));
		_baseModel.setItem(1, i, new QStandardItem(QString::number(msg.uraIndex())));
		_baseModel.setItem(2, i, new QStandardItem(QString::number(msg.svHealth())));
		if(msg.l2pDataFlag())
			_baseModel.setItem(3, i, new QStandardItem("True"));
		else
			_baseModel.setItem(3, i, new QStandardItem("False"));
		_baseModel.setItem(4, i, new QStandardItem(QString::number(msg.tGD())));
		_baseModel.setItem(5, i, new QStandardItem(QString::number(msg.iodc())));
		_baseModel.setItem(6, i, new QStandardItem(QString::number(msg.tOC())));
		_baseModel.setItem(7, i, new QStandardItem(QString::number((double)msg.af2())));
		_baseModel.setItem(8, i, new QStandardItem(QString::number(msg.af1())));
		_baseModel.setItem(9, i, new QStandardItem(QString::number(msg.af0())));
	}

	_baseModel.setHorizontalHeaderLabels(horizontalHeader);

	QStringList verticalHeader = 
	{
		"Week number",
		"URA index",
		"SV Health",
		"L2 P Data Flag",
		"t_GD",
		"IODC",
		"t_OC",
		"a_f2",
		"a_f1",
		"a_f0"
	};
	
	_baseModel.setVerticalHeaderLabels(verticalHeader);
	resizeColumnsToContents();

	_baseModel.setColumnCount(availablePRNs.size());
	_baseModel.setRowCount(10);
}