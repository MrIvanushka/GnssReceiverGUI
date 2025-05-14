#pragma once

#include "IEditorDataInput.h"

#include <QFileInfo>
#include <QString>

#include <fstream>
#include <queue>

namespace Editor
{
namespace GUI
{

class FileInput : public IEditorDataInput
{
public:
	FileInput(QFileInfo sigs, QFileInfo timestamps);

	~FileInput();

	bool getSignal(double* signal, double* timestamp, int* PRN) override;

	RecentDataPtr popRecentData() override;
private:
	std::vector<PRN> _prns;

	std::queue<float> _lastLineSig;
	std::queue<float> _lastLineTime;

	std::ifstream _inFile;

	std::ifstream _timestamps;

	bool _hasData = true;

	RecentDataPtr _recentData;
};

}
}