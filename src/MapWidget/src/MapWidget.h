#pragma once

#include "ModuleWidget.h"

#include <QNetworkDiskCache>
#include <QDir>
#include <QNetworkAccessManager>
#include "QGeoView/QGVmap.h"

namespace Editor
{
namespace GUI
{

class MapWidget : public ModuleWidget
{
	Q_OBJECT
public:
	MapWidget();

	void init(std::shared_ptr<IContext> context) override;

	const Info& info() const override;
private:
	void initNetwork();
private slots:
	void clear();

	void updateLocation();
private:
	std::shared_ptr<IContext> _context;
	Info _info = Info(QString::fromLocal8Bit("Карта"));

	QGVMap* _geoMap;
	std::vector<QGVItem*> _temporaryItems;

	QNetworkDiskCache* mCache;
	QNetworkAccessManager* mManager;
};

}
}