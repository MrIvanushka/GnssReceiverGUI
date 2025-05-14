#include "FileInput.h"
#include "Log.h"

using namespace Editor::GUI;

FileInput::FileInput(QFileInfo sigs, QFileInfo timestamps)
{   
    _recentData = std::make_shared<std::unordered_map<PRN, QVector<Signal>>>();

    _inFile.open(sigs.absoluteFilePath().toStdString().c_str());

    if (!_inFile.is_open())
    {
        LOG_ERROR("FileInput couldn't open ", sigs.absoluteFilePath().toStdString());
        return;
    }

    _timestamps.open(timestamps.absoluteFilePath().toStdString().c_str());

    if (!_timestamps.is_open())
    {
        LOG_ERROR("FileInput couldn't open ", timestamps.absoluteFilePath().toStdString());
        return;
    }

    LOG_INFO("Input files are successfully opened");

    std::string firstLine;
    if (!std::getline(_inFile, firstLine))
    {
        LOG_ERROR("Input file is empty");
        return;
    }
    auto splittedLine = QString::fromStdString(firstLine).split(" ");
    _prns = std::vector<PRN>(splittedLine.size());
    for (int i = 0u; i < splittedLine.size(); ++i)
        _prns[i] = splittedLine[i].toInt();

    _hasData = true;
}

FileInput::~FileInput()
{
    LOG_INFO("Input file is successfully closed");
    _inFile.close();
}

bool FileInput::getSignal(double* signal, double* timestamp, int* PRN)
{
    if (!_hasData)
        return false;

    if (!_lastLineSig.empty())
    {
        *signal = _lastLineSig.front();
        *timestamp = _lastLineTime.front();
        *PRN = _prns[_prns.size() - _lastLineSig.size()];
        _lastLineSig.pop();
        _lastLineTime.pop();
        (*_recentData)[*PRN].push_back(*signal);
        return true;
    }

    if (!_inFile.is_open())
    {
        _hasData = false;
        emit sentAll();
        LOG_ERROR("FileInput source runtime error");
        return false;
    }
    std::string newLineSig;
    if (!std::getline(_inFile, newLineSig))
    {
        _hasData = false;
        emit sentAll();
        LOG_INFO("FileInput provided all data from file");
        return false;
    }
    std::string newLineTime;
    if (!std::getline(_timestamps, newLineTime))
    {
        LOG_ERROR("Signal and timestamp files have different size");
        _hasData = false;
        emit sentAll();
        return false;
    }

    auto splittedLineSig = QString::fromStdString(newLineSig).split(" ");
    auto splittedLineTime = QString::fromStdString(newLineTime).split(" ");
    if (splittedLineSig.size() != splittedLineTime.size())
    {
        LOG_ERROR("Signal and timestamp files have different size");
        _hasData = false;
        emit sentAll();
        return false;
    }
    for (int i = 1u; i < splittedLineSig.size(); ++i)
    {
        _lastLineSig.push(splittedLineSig[i].toFloat());
        _lastLineTime.push(splittedLineTime[i].toFloat());
    }
    *PRN = _prns[0];
    *signal = splittedLineSig[0].toFloat();
    *timestamp = splittedLineTime[0].toFloat();
    (*_recentData)[*PRN].push_back(*signal);
    return true;
}

FileInput::RecentDataPtr FileInput::popRecentData()
{
    auto ret = _recentData;
    _recentData = std::make_shared<std::unordered_map<PRN, QVector<Signal>>>();
    return ret;
}