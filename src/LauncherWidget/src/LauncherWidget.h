#pragma once

#include "ModuleWidget.h"

#include <QComboBox>
#include <QList>
#include <QPushButton>
#include "IDataInputFactoryWidget.h"

namespace Editor
{
namespace GUI
{

class LauncherWidget : public ModuleWidget
{
	Q_OBJECT
public:
	LauncherWidget();

	void init(std::shared_ptr<IContext> context) override;

	const Info& info() const override;
public slots:
	void handleStart();
	
	void handleStop();

	void handleStartButtonClick();
private:
	std::shared_ptr<IContext> _context;
	Info _info = Info(QString::fromLocal8Bit("”правление приЄмником"));

	QPushButton* _startButton;
	QComboBox* _protocolTypeSelector;
	QComboBox* _dataInputTypeSelector;
	QList<IDataInputFactoryWidget*> _dataInputFactories;
};

}
}