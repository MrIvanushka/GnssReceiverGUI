#include "LogFilterPanel.h"

#include <QHBoxLayout>
#include <QAction>

using namespace Editor::GUI;

LogFilterPanel::LogFilterPanel(QSortFilterProxyModel* first, QSortFilterProxyModel* second)
{
	Q_INIT_RESOURCE(logResources);

	_textFilter = first;
	_buttonFilter = second;

	auto lay = new QHBoxLayout;
	lay->setContentsMargins(0, 0, 0, 0);
	setLayout(lay);

	_lineEdit = new QLineEdit;
	lay->addWidget(_lineEdit);

	_lineEdit->setPlaceholderText(QString::fromLocal8Bit("¬ведите фильтр"));

	_infoButton = makeToolButton(QIcon(":/Log/Icons/Info.png"));
	lay->addWidget(_infoButton);
	_warnButton = makeToolButton(QIcon(":/Log/Icons/Warning.png"));
	lay->addWidget(_warnButton);
	_errorButton = makeToolButton(QIcon(":/Log/Icons/Error.png"));
	lay->addWidget(_errorButton);

	connect(_lineEdit, &QLineEdit::textChanged, this, [this](QString text) {
		_textFilter->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::RegExp2));
		_textFilter->setFilterKeyColumn(2);
		});
}

QString LogFilterPanel::filter() const
{
	return "";
}

QToolButton* LogFilterPanel::makeToolButton(QIcon icon)
{
	auto toolButton = new QToolButton;
	toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	auto act = new QAction();
	act->setIcon(icon);
	act->setText("0");
	act->setCheckable(true);
	QObject::connect(act, &QAction::triggered, this, &LogFilterPanel::updateButtonFilter);
	toolButton->setDefaultAction(act);
	return toolButton;
}

void LogFilterPanel::handleError()
{
	_errorCount += 1;
	_errorButton->defaultAction()->setText(QString::number(_errorCount));
}

void LogFilterPanel::handleInfo()
{
	_infoCount += 1;
	_infoButton->defaultAction()->setText(QString::number(_infoCount));
}

void LogFilterPanel::handleWarn()
{
	_warnCount += 1;
	_warnButton->defaultAction()->setText(QString::number(_warnCount));
}

void LogFilterPanel::updateButtonFilter()
{
	QString regexp = "";

	if (!_infoButton->defaultAction()->isChecked())
	{
		regexp += "INFO";
	}
	if (!_warnButton->defaultAction()->isChecked())
	{
		if (regexp != "")
			regexp += "|";
		regexp += "WARN";
	}
	if (!_errorButton->defaultAction()->isChecked())
	{
		if (regexp != "")
			regexp += "|";
		regexp += "ERROR";
	}
	if (regexp == "")
	{
		regexp = "NOTHING";
	}
	_buttonFilter->setFilterRegExp(QRegExp(regexp, Qt::CaseInsensitive, QRegExp::RegExp2));
	_buttonFilter->setFilterKeyColumn(1);
}