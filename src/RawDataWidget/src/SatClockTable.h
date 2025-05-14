#pragma once

#include <QStandardItemModel>
#include <QTableView>
#include <thread>
#include "IContext.h"

namespace Editor
{
namespace GUI
{

class SatClockTable : public QTableView
{
	Q_OBJECT
public:
	SatClockTable();
public slots:
	void update(std::shared_ptr<IContext>);
private:
	QStandardItemModel _baseModel;

	std::thread _runningThread;

	bool _running = false;
};

}
}