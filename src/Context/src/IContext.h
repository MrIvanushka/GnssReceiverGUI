#pragma once

#include <QObject>
#include "IGnssStorage.h"
#include "IEditorDataInput.h"
#include "Stat.h"

namespace Editor
{

Q_DECLARE_METATYPE(IEditorDataInput::RecentDataPtr);

class IContext : public QObject
{
	Q_OBJECT
public:
	typedef std::shared_ptr<IEditorDataInput> DataInputPtr;
public:
	virtual std::shared_ptr<const gnssRecv::IGnssStorage> storage() const = 0;

	virtual std::vector<gnssRecv::Stat> stat(int PRN) const = 0;

	virtual bool running() const = 0;

	virtual uint64_t statRequestUpdatePeriodMs() const = 0;
signals:
	void restarted();

	void stopped();

	void receivedSignals(IEditorDataInput::RecentDataPtr);

	void updatedLocation();

	void requestedStatUpdate();
public slots:
	virtual void restart(gnssRecv::ProtocolType, DataInputPtr) = 0;

	virtual void stop() = 0;
};

}