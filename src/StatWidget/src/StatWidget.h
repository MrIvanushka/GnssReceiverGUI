#pragma once

#include <QString>
#include "StatTable.h"
#include "ModuleWidget.h"

namespace Editor
{
namespace GUI
{

class StatWidget : public ModuleWidget
{
	Q_OBJECT
public:
	StatWidget();

	void init(std::shared_ptr<IContext> context) override;

	const Info& info() const override;
private:
	StatTable* _table;

	std::shared_ptr<IContext> _context;
	Info _info = Info(QString::fromLocal8Bit("Статистика"));
};

}
}