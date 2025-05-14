#pragma once

#include <QString>
#include "SatelliteTable.h"
#include "ModuleWidget.h"

namespace Editor
{
namespace GUI
{

class SatelliteWidget : public ModuleWidget
{
	Q_OBJECT
public:
	SatelliteWidget();

	void init(std::shared_ptr<IContext> context) override;

	const Info& info() const override;
private:
	SatelliteTable* _table;

	std::shared_ptr<IContext> _context;
	Info _info = Info(QString::fromLocal8Bit("Обнаруженные спутники"));
};

}
}