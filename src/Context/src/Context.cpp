#include "Context.h"
#include "Log.h"

using namespace Editor;

Context::Context(std::unique_ptr<gnssRecv::IGnssProcessor> processor) :
	_processor{ std::move(processor) }
{
	qRegisterMetaType<IEditorDataInput::RecentDataPtr>("IEditorDataInput::RecentDataPtr");
}

std::shared_ptr<const gnssRecv::IGnssStorage> Context::storage() const
{
	return _processor->storage();
}

std::vector<gnssRecv::Stat> Context::stat(int PRN) const
{
	return _processor->satelliteStat(PRN);
}

bool Context::running() const
{
	return _processor->running();
}

uint64_t Context::statRequestUpdatePeriodMs() const
{
	return _statRequestUpdatePeriodMs;
}

void Context::restart(gnssRecv::ProtocolType protocol, DataInputPtr input)
{
	_dataInput = input;
	_processor->start(protocol, input);
	emit restarted();
	_runningThread = std::thread(&Context::run, this);
}

void Context::stop()
{
	_processor->stop();
	emit stopped();
	_runningThread.join();
	update();
}

void Context::run()
{
	while (_processor->running())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(_statRequestUpdatePeriodMs));
		update();
	}
}

void Context::update()
{
	emit requestedStatUpdate();
	auto data = _dataInput->popRecentData();
	emit receivedSignals(data);
}