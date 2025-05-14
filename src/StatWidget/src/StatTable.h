#pragma once

#include <QStandardItemModel>
#include <QTableView>
#include "IContext.h"

namespace Editor
{
namespace GUI
{

class StatTable : public QTableView
{
	Q_OBJECT
public:
	StatTable();
public slots:
	void update(std::shared_ptr<IContext>);
private:
	QStandardItemModel _baseModel;
};

}
}