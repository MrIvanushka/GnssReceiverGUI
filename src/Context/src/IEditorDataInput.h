#pragma once

#include <QObject>

#include "IDataInput.h"
#include <unordered_map>

namespace Editor
{

class IEditorDataInput : public QObject, public gnssRecv::IDataInput
{
	Q_OBJECT
public:
	typedef int PRN;
	typedef double Signal;
	typedef std::shared_ptr<std::unordered_map<PRN, QVector<Signal>>> RecentDataPtr;
public:
	virtual RecentDataPtr popRecentData() = 0;
signals:
	void sentAll();
};

}