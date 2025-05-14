#pragma once

#include "IDataInputFactoryWidget.h"

#include <QPushButton>
#include <QFileInfo>

namespace Editor
{
namespace GUI
{

class FileInputFactoryWidget : public IDataInputFactoryWidget
{
	Q_OBJECT
public:
	FileInputFactoryWidget();

	QString name() const override;

	std::shared_ptr<IEditorDataInput> makeInput() const override;
private slots:
	void selectSigsFile();
	void selectAbsoluteShiftFile();
private:
	const QString _name = QString::fromLocal8Bit("Из файла");

	QPushButton* _sigsPath;
	QPushButton* _absoluteShiftPath;
	QFileInfo _chosenSigsPath;
	QFileInfo _chosenAbsoluteShiftPath;
};

}
}