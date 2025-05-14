#pragma once

#include <QString>
#include <QSortFilterProxyModel>
#include "LogTable.h"
#include "LogFilterPanel.h"
#include "ModuleWidget.h"
#include "Log.h"

namespace Editor
{
namespace GUI
{

class LogWidget : public ModuleWidget, public gnssRecv::ILoggerListener
{
	Q_OBJECT
public:
	LogWidget();

	void init(std::shared_ptr<IContext> context) override;

	const Info& info() const override;

	void handleLog(gnssRecv::Level, std::string text, std::string timestamp) override;
signals:
	void seeError(QString text, QString timestamp);
	void seeWarn(QString text, QString timestamp);
	void seeInfo(QString text, QString timestamp);
private:
	QSortFilterProxyModel _innerFilter;
	QSortFilterProxyModel _outerFilter;

	LogTable* _table;
	LogFilterPanel* _filterPanel;

	std::shared_ptr<IContext> _context;
	Info _info = Info(QString::fromLocal8Bit("Логи"));
};

}
}