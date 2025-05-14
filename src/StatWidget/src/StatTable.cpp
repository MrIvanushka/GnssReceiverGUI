#include "StatTable.h"

#include <QHeaderView>
#include <QSizePolicy>
#include <unordered_map>

using namespace Editor::GUI;

StatTable::StatTable()
{
	setModel(&_baseModel);

	setShowGrid(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	horizontalHeader()->setVisible(true);
	verticalHeader()->setVisible(true);

	horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

	setSelectionBehavior(QAbstractItemView::SelectRows);
}

void StatTable::update(std::shared_ptr<IContext> context)
{
	_baseModel.clear();

	const auto& availablePRNs = context->storage()->availableSatellites();
	if (availablePRNs.empty())
		return;

	std::vector<std::vector<gnssRecv::Stat>> wholeStat;

	QStringList horizontalHeader;
	for (auto prn : availablePRNs)
	{
		horizontalHeader.append(QString::number(prn));
		wholeStat.push_back(context->stat(prn));
	}
	uint32_t rowCount = 0;
	for (const auto& stat : wholeStat[0])
	{
		rowCount += 1 + stat.values().size();
	}

	_baseModel.setHorizontalHeaderLabels(horizontalHeader);

	QStringList verticalHeader;
	uint32_t currentIndex = 0;
	for (auto statIdx = 0u; statIdx < wholeStat[0].size(); ++statIdx)
	{
		verticalHeader.append(QString::fromLocal8Bit(wholeStat[0][statIdx].name().c_str()));
		++currentIndex;
		//setSpan(currentIndex, 0, 1, availablePRNs.size());
		for (const auto& statPair : wholeStat[0][statIdx].values())
		{
			verticalHeader.append(QString::fromLocal8Bit(wholeStat[0][statIdx].paramName(statPair.first).c_str()));
			for(auto col = 0u; col < availablePRNs.size(); ++col)
				_baseModel.setItem(currentIndex, col, new QStandardItem(QString::number(wholeStat[col][statIdx].value(statPair.first))));
			++currentIndex;
		}
	}
	_baseModel.setVerticalHeaderLabels(verticalHeader);
	resizeColumnsToContents();

	_baseModel.setColumnCount(availablePRNs.size());
	_baseModel.setRowCount(rowCount);
}