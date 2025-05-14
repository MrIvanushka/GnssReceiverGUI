#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QSortFilterProxyModel>
#include "LogMessage.h"
#include "Log.h"

#include <QAbstractTableModel>

namespace Editor
{
namespace GUI
{
	QAbstractTableModel;

class LogFilterPanel : public QWidget
{
	Q_OBJECT
public:
	LogFilterPanel(QSortFilterProxyModel* first, QSortFilterProxyModel* second);

	QString filter() const;
signals:
	void filterChanged();
public slots:
	void handleError();
	void handleInfo();
	void handleWarn();
private:
	QToolButton* makeToolButton(QIcon icon);
private slots:
	void updateButtonFilter();
private:
	QSortFilterProxyModel* _textFilter;
	QSortFilterProxyModel* _buttonFilter;
	QLineEdit* _lineEdit;

	QToolButton* _infoButton;
	QToolButton* _warnButton;
	QToolButton* _errorButton;

	uint64_t _errorCount = 0;
	uint64_t _warnCount = 0;
	uint64_t _infoCount = 0;
};

}
}