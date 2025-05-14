#pragma once

#include <QString>

namespace Editor
{
namespace GUI
{

struct LogMessage
{
	enum Type { Info, Warn, Error };

	Type type;

	QString message;
};

}
}