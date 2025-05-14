#include "StatWidget.h"

#include <QVBoxLayout>

using namespace Editor;
using namespace Editor::GUI;

StatWidget::StatWidget()
{
	_table = new StatTable;

	auto lay = new QVBoxLayout;
	setLayout(lay);
	lay->addWidget(_table);
}

void StatWidget::init(std::shared_ptr<IContext> context)
{
	_context = context;

	QObject::connect(_context.get(), &IContext::requestedStatUpdate, this, [this]() {_table->update(_context);});
}

const Info& StatWidget::info() const
{
	return _info;
}