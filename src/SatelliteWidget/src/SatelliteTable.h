#pragma once

#include <QStandardItemModel>
#include <QTableView>
#include "IContext.h"

namespace Editor
{
namespace GUI
{

class SatelliteTable : public QTableView
{
	Q_OBJECT
public:
	SatelliteTable();
public slots:
	void update(std::shared_ptr<IContext>);
private:
	QStandardItemModel _baseModel;
};

}
}