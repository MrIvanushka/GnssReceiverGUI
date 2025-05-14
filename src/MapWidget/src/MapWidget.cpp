#include "MapWidget.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>

#include "QGeoView/QGVLayerOSM.h"
#include "QGeoView/QGVLayerGoogle.h"
#include "QGeoView/QGVLayerBing.h"
#include "QGeoView/QGVLayerBDGEx.h"
#include "Placemark.h"

#include "Log.h"

using namespace Editor;
using namespace Editor::GUI;

MapWidget::MapWidget()
{
    initNetwork();

    const QString customURI = "http://c.tile.stamen.com/watercolor/${z}/${x}/${y}.jpg";
    const QList<QPair<QString, QGVLayer*>> layers = {
        { "OSM", new QGVLayerOSM() },
        { "GOOGLE_SATELLITE", new QGVLayerGoogle(QGV::TilesType::Satellite) },
        { "GOOGLE_HYBRID", new QGVLayerGoogle(QGV::TilesType::Hybrid) },
        { "GOOGLE_SCHEMA", new QGVLayerGoogle(QGV::TilesType::Schema) },
        { "BING_SATELLITE", new QGVLayerBing(QGV::TilesType::Satellite) },
        { "BING_HYBRID", new QGVLayerBing(QGV::TilesType::Hybrid) },
        { "BING_SCHEMA", new QGVLayerBing(QGV::TilesType::Schema) },
        { "CUSTOM_OSM", new QGVLayerOSM(customURI) },
        { "BDGEx CTM25", new QGVLayerBDGEx(QGV::BDGExLayer::ctm25) },
        { "BDGEx CTM50", new QGVLayerBDGEx(QGV::BDGExLayer::ctm50) },
        { "BDGEx CTM100", new QGVLayerBDGEx(QGV::BDGExLayer::ctm100) },
        { "BDGEx CTM250", new QGVLayerBDGEx(QGV::BDGExLayer::ctm250) },
        { "BDGEx CTM Multi Scale", new QGVLayerBDGEx(QGV::BDGExLayer::ctmmultiescalas) },
        { "BDGEx CTM Multi Scale Mercator", new QGVLayerBDGEx(QGV::BDGExLayer::ctmmultiescalas_mercator) },
    };

    auto lay = new QVBoxLayout;
    setLayout(lay);

    auto formLay = new QFormLayout;
    lay->addLayout(formLay);
    formLay->setContentsMargins(0, 0, 0, 0);
    auto combobox = new QComboBox;
    formLay->addRow(QString::fromLocal8Bit("Стиль"), combobox);

    _geoMap = new QGVMap;
    lay->addWidget(_geoMap);
   
    for (auto pair : layers) {
        auto name = pair.first;
        auto layer = pair.second;
        layer->hide();
        _geoMap->addItem(layer);
        combobox->addItem(name);
    }
    layers[0].second->setVisible(true);

    auto target = _geoMap->getProjection()->boundaryGeoRect();
    _geoMap->cameraTo(QGVCameraActions(_geoMap).scaleTo(target));

    //example
    //_geoMap->addItem(new Placemark(QGV::GeoPos(55.9286016, 37.5197256), Placemark::Red));
}

void MapWidget::init(std::shared_ptr<IContext> context)
{
	_context = context;

    QObject::connect(_context.get(), &IContext::restarted, this, &MapWidget::clear);
    QObject::connect(_context.get(), &IContext::stopped, this, &MapWidget::updateLocation);
}

const Info& MapWidget::info() const
{
	return _info;
}

void MapWidget::initNetwork()
{
    /*
     * All "online" items required instance of QNetworkAccessManager.
     * Also it is recommended to use QNetworkCache for this manager to reduce
     * network load and speed-up download.
     */
    QDir("cacheDir").removeRecursively();
    mCache = new QNetworkDiskCache(this);
    mCache->setCacheDirectory("cacheDir");
    mManager = new QNetworkAccessManager(this);
    mManager->setCache(mCache);
    QGV::setNetworkManager(mManager);
}

void MapWidget::clear()
{
    for (auto item : _temporaryItems)
        _geoMap->removeItem(item);
}

void MapWidget::updateLocation()
{
    clear();
    auto receiverLocations = _context->storage()->receiverLocations();
    gnssRecv::math::Vector3 meanLocation(0,0,0);

    for (auto location : receiverLocations)
    {
        meanLocation = meanLocation + location;
    }
    meanLocation = gnssRecv::math::Vector3(meanLocation.x / receiverLocations.size(), meanLocation.y / receiverLocations.size(), meanLocation.z / receiverLocations.size());
    _geoMap->addItem(new Placemark(QGV::GeoPos(meanLocation.x, meanLocation.y), Placemark::Blue));
}