#include "EphemerisTable.h"

#include <QHeaderView>
#include <QSizePolicy>
#include <unordered_map>
#include "Log.h"
#include "IGPSSatStorage.h"

using namespace Editor::GUI;

EphemerisTable::EphemerisTable()
{
	setModel(&_baseModel);

	setShowGrid(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	horizontalHeader()->setVisible(true);
	verticalHeader()->setVisible(true);

	horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

	setSelectionBehavior(QAbstractItemView::SelectRows);
}

void EphemerisTable::update(std::shared_ptr<IContext> context)
{
	_baseModel.clear();

	const auto& availablePRNs = context->storage()->availableSatellites();
	if (availablePRNs.empty())
		return;

	QStringList horizontalHeader;
	for (auto i = 0u; i < availablePRNs.size(); ++i)
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
		auto msg = castedStorage->lastEphemeris();

		double ir = msg.inclinationRate();

		_baseModel.setItem(0, i, new QStandardItem(QString::number(msg.iode())));
		_baseModel.setItem(1, i, new QStandardItem(QString::number(msg.deltaN())));
		_baseModel.setItem(2, i, new QStandardItem(QString::number(msg.m0())));
		_baseModel.setItem(3, i, new QStandardItem(QString::number(msg.e())));
		_baseModel.setItem(4, i, new QStandardItem(QString::number(msg.sqrtOfA())));
		_baseModel.setItem(5, i, new QStandardItem(QString::number(msg.tOE())));
		_baseModel.setItem(6, i, new QStandardItem(QString::number(msg.aodo())));
		_baseModel.setItem(7, i, new QStandardItem(QString::number(msg.omega0())));
		_baseModel.setItem(8, i, new QStandardItem(QString::number(msg.i0())));
		_baseModel.setItem(9, i, new QStandardItem(QString::number(msg.omega())));
		_baseModel.setItem(10, i, new QStandardItem(QString::number(msg.ascendingRate())));
		_baseModel.setItem(11, i, new QStandardItem(QString::number(msg.inclinationRate())));
		_baseModel.setItem(12, i, new QStandardItem(QString::number(msg.cRS())));
		_baseModel.setItem(13, i, new QStandardItem(QString::number(msg.cUC())));
		_baseModel.setItem(14, i, new QStandardItem(QString::number(msg.cUS())));
		_baseModel.setItem(15, i, new QStandardItem(QString::number(msg.cIC())));
		_baseModel.setItem(16, i, new QStandardItem(QString::number(msg.cIS())));
		_baseModel.setItem(17, i, new QStandardItem(QString::number(msg.cRC())));
	}

	_baseModel.setHorizontalHeaderLabels(horizontalHeader);

	QStringList verticalHeader =
	{
		"IODE",								//0
		"Mean motion correction",			//1
		"Mean anomaly",						//2
		"Eccentricity",						//3
		"Sqrt of semimajor",				//4
		"t_OE",								//5
		"AODO",								//6
		"Longtitude of ascending node",		//7
		"Inclination",						//8
		"Argument of periapsis",			//9
		"Ascending rate",					//10
		"Inclination rate",					//11
		"C_RS",								//12
		"C_UC",								//13
		"C_US",								//14
		"C_IC",								//15
		"C_IS",								//16
		"C_RC"								//17
	};

	_baseModel.setVerticalHeaderLabels(verticalHeader);
	resizeColumnsToContents();

	_baseModel.setColumnCount(availablePRNs.size());
	_baseModel.setRowCount(17);
}