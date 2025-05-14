#include "SatelliteWidget.h"

#include <QVBoxLayout>

using namespace Editor;
using namespace Editor::GUI;

SatelliteWidget::SatelliteWidget()
{
	_table = new SatelliteTable;

	auto lay = new QVBoxLayout;
	setLayout(lay);
	lay->addWidget(_table);
}

void SatelliteWidget::init(std::shared_ptr<IContext> context)
{
	_context = context;

	QObject::connect(_context.get(), &IContext::requestedStatUpdate, this, [this]() {_table->update(_context);});
}

const Info& SatelliteWidget::info() const
{
	return _info;
}