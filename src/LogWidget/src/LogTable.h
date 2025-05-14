#pragma once

#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QTableView>

namespace Editor
{
namespace GUI
{

class LogTable : public QTableView
{
public:
	LogTable(QSortFilterProxyModel* outer, QSortFilterProxyModel* inner);
public slots:
	void clear();

	void writeInfo(QString timestamp, QString message);

	void writeWarning(QString timestamp, QString message);

	void writeError(QString timestamp, QString message);
private:
	uint64_t _drawnLogsCount = 0;

	QIcon _info;
	QIcon _warn;
	QIcon _error;

	QStandardItemModel _baseModel;
};

}
}