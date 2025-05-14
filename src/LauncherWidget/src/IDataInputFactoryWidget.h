#pragma once

#include <QString>
#include <QGroupBox>

#include <memory>

#include "IEditorDataInput.h"

namespace Editor
{
namespace GUI
{

class IDataInputFactoryWidget : public QGroupBox
{
	Q_OBJECT
public:
	virtual QString name() const = 0;

	virtual std::shared_ptr<IEditorDataInput> makeInput() const = 0;
};

}
}