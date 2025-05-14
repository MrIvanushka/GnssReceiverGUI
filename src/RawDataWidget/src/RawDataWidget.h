#pragma once

#include <QString>
#include <QSortFilterProxyModel>
#include <QStackedLayout>
#include <QComboBox>
#include "ModuleWidget.h"

namespace Editor
{
namespace GUI
{

class RawDataWidget : public ModuleWidget
{
	Q_OBJECT
public:
	RawDataWidget();

	void init(std::shared_ptr<IContext>) override;

	const Info& info() const override;
private slots:
	void onStart();
private:
	void clearLayout(QLayout*);
private:
	QComboBox* _tableSelector;
	QStackedLayout* _stackedLay;

	std::shared_ptr<IContext> _context;
	Info _info = Info(QString::fromLocal8Bit("—ырые данные"));
};

}
}