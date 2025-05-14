#include "SatelliteTable.h"

#include <QHeaderView>
#include <QSizePolicy>
#include <unordered_map>
#include <ctime>

using namespace Editor::GUI;

SatelliteTable::SatelliteTable()
{
	setModel(&_baseModel);

	setShowGrid(false);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
	_baseModel.setColumnCount(4);

	verticalHeader()->setVisible(false);
	horizontalHeader()->setVisible(false);

	setSelectionBehavior(QAbstractItemView::SelectRows);
}

void SatelliteTable::update(std::shared_ptr<IContext> context)
{
	_baseModel.clear();

	const auto& availablePRNs = context->storage()->availableSatellites();
	if (availablePRNs.empty())
		return;

	for (auto i = 0u; i < availablePRNs.size(); ++i)
	{
		auto satStorage = context->storage()->getSatStorage(availablePRNs[i]);

		_baseModel.setItem(i, 0, new QStandardItem("PRN " + QString::number(availablePRNs[i])));

		switch (satStorage->trackingState())
		{
		case gnssRecv::TrackingState::LOST:
			_baseModel.setItem(i, 1, new QStandardItem(QString::fromLocal8Bit("Потерян")));
			break;
		case gnssRecv::TrackingState::SYNCRONIZING:
			_baseModel.setItem(i, 1, new QStandardItem(QString::fromLocal8Bit("Синхронизация")));
			break;
		case gnssRecv::TrackingState::COLLECTING_DATA:
			_baseModel.setItem(i, 1, new QStandardItem(QString::fromLocal8Bit("Сбор данных")));
			break;
		case gnssRecv::TrackingState::ACTIVE:
			_baseModel.setItem(i, 1, new QStandardItem(QString::fromLocal8Bit("Установлен приём")));
			break;
		}
		auto locationStr = "(" +
			QString::number(satStorage->location().x) + "; " +
			QString::number(satStorage->location().y) + "; " +
			QString::number(satStorage->location().z) + ")";
		_baseModel.setItem(i, 2, new QStandardItem(locationStr));


		QString satTime = "";
		auto satTimeReal = static_cast<time_t>(satStorage->secondsUTC());
		auto sec = satTimeReal % 60;
		auto min = (satTimeReal / 60) & 60;
		auto hour = (satTimeReal / 3600) % 24;
		char buf[32];
		std::tm* tmUtc = std::gmtime(&satTimeReal);
		auto tow = satStorage->satelliteTimeOfWeek();
		auto satTimeFrac = std::round(1000 * (tow - (long)tow));

		std::strftime(buf, sizeof(buf), "%d.%m.%Y, %H:%M:%S", tmUtc);
		_baseModel.setItem(i, 3, new QStandardItem(QString(buf) + "." + QString::number(satTimeFrac)));
	}
	resizeColumnsToContents();

	_baseModel.setRowCount(availablePRNs.size());
}