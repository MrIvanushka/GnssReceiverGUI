#pragma once

#include "IContext.h"
#include "IGnssProcessor.h"
#include <thread>
#include <set>

namespace Editor
{

class Context : public IContext
{
	Q_OBJECT
public:
	Context(std::unique_ptr<gnssRecv::IGnssProcessor>);

	std::shared_ptr<const gnssRecv::IGnssStorage> storage() const override;

	std::vector<gnssRecv::Stat> stat(int PRN) const override;

	bool running() const override;

	uint64_t statRequestUpdatePeriodMs() const override;
public slots:
	void restart(gnssRecv::ProtocolType, DataInputPtr) override;

	void stop() override;
private:
	void run();

	void update();
private:
	const uint64_t _statRequestUpdatePeriodMs = 500;

	std::unique_ptr<gnssRecv::IGnssProcessor> _processor;

	DataInputPtr _dataInput;

	std::thread _runningThread;
};

}