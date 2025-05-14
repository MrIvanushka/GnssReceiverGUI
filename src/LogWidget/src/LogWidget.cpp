#include "LogWidget.h"

#include <QVBoxLayout>
#include "LogFilterPanel.h"

using namespace Editor;
using namespace Editor::GUI;

LogWidget::LogWidget()
{
	_outerFilter.setSourceModel(&_innerFilter);

	_table = new LogTable(&_outerFilter, &_innerFilter);

	auto lay = new QVBoxLayout;
	setLayout(lay);
	_filterPanel = new LogFilterPanel(&_outerFilter, &_innerFilter);
	lay->addWidget(_filterPanel);
	lay->addWidget(_table);

	gnssRecv::Logger::instance().addListener(this);
	QObject::connect(this, &QObject::destroyed, this, [this]() { gnssRecv::Logger::instance().removeListener(this); });

	QObject::connect(this, &LogWidget::seeInfo, _filterPanel, &LogFilterPanel::handleInfo);
	QObject::connect(this, &LogWidget::seeWarn, _filterPanel, &LogFilterPanel::handleWarn);
	QObject::connect(this, &LogWidget::seeError, _filterPanel, &LogFilterPanel::handleError);
	QObject::connect(this, &LogWidget::seeInfo, _table, &LogTable::writeInfo);
	QObject::connect(this, &LogWidget::seeWarn, _table, &LogTable::writeWarning);
	QObject::connect(this, &LogWidget::seeError, _table, &LogTable::writeError);
}

void LogWidget::init(std::shared_ptr<IContext> context)
{
	_context = context;
}

const Info& LogWidget::info() const
{
	return _info;
}

void LogWidget::handleLog(gnssRecv::Level level, std::string text, std::string timestamp)
{
	switch (level)
	{
	case gnssRecv::Level::Info:
		emit seeInfo(QString::fromLocal8Bit(timestamp.c_str()), QString::fromLocal8Bit(text.c_str()));
		break;
	case gnssRecv::Level::Warn:
		emit seeWarn(QString::fromLocal8Bit(timestamp.c_str()), QString::fromLocal8Bit(text.c_str()));
		break;
	case gnssRecv::Level::Error:
		emit seeError(QString::fromLocal8Bit(timestamp.c_str()), QString::fromLocal8Bit(text.c_str()));
		break;
	}
}