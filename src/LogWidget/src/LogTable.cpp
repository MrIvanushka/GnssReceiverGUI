#include "LogTable.h"

#include <QHeaderView>

using namespace Editor::GUI;

LogTable::LogTable(QSortFilterProxyModel* outer, QSortFilterProxyModel* inner)
{
	inner->setSourceModel(&_baseModel);
	setModel(outer);

	Q_INIT_RESOURCE(logResources);

	setShowGrid(false);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	_baseModel.setRowCount(0);
	_baseModel.setColumnCount(4);

	horizontalHeader()->setVisible(false);


	horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
	horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

	setColumnWidth(0, rowHeight(0));
	setColumnWidth(1, 160);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setColumnHidden(1, true);

	_info = QIcon(":/Log/Icons/Info.png");
	_warn = QIcon(":/Log/Icons/Warning.png");
	_error = QIcon(":/Log/Icons/Error.png");
}

void LogTable::clear()
{
	_drawnLogsCount = 0;
	_baseModel.setRowCount(0);
}

void LogTable::writeInfo(QString timestamp, QString message)
{
	_baseModel.setRowCount(_drawnLogsCount + 1);

	_baseModel.setItem(_drawnLogsCount, 0, new QStandardItem(_info, ""));
	_baseModel.setItem(_drawnLogsCount, 1, new QStandardItem("INFO"));
	_baseModel.setItem(_drawnLogsCount, 3, new QStandardItem(timestamp));
	_baseModel.setItem(_drawnLogsCount, 2, new QStandardItem(message));

	++_drawnLogsCount;
}

void LogTable::writeWarning(QString timestamp, QString message)
{
	_baseModel.setRowCount(_drawnLogsCount + 1);

	_baseModel.setItem(_drawnLogsCount, 0, new QStandardItem(_warn, ""));
	_baseModel.setItem(_drawnLogsCount, 1, new QStandardItem("WARN"));
	_baseModel.setItem(_drawnLogsCount, 3, new QStandardItem(timestamp));
	_baseModel.setItem(_drawnLogsCount, 2, new QStandardItem(message));

	++_drawnLogsCount;
}

void LogTable::writeError(QString timestamp, QString message)
{
	_baseModel.setRowCount(_drawnLogsCount + 1);

	_baseModel.setItem(_drawnLogsCount, 0, new QStandardItem(_error, ""));
	_baseModel.setItem(_drawnLogsCount, 1, new QStandardItem("ERROR"));
	_baseModel.setItem(_drawnLogsCount, 3, new QStandardItem(timestamp));
	_baseModel.setItem(_drawnLogsCount, 2, new QStandardItem(message));

	++_drawnLogsCount;
}