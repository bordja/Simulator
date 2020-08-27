
// Copyright 2019 ESRI
//
// All rights reserved under the copyright laws of the United States
// and applicable international laws, treaties, and conventions.
//
// You may freely redistribute and use this sample code, with or
// without modification, provided you include the original copyright
// notice and use restrictions.
//
// See the Sample code usage restrictions document for further information.
//

// C++ API headers
#include "Basemap.h"

// Other headers
#include "Simulator.h"

#include "Map.h"
#include "MapGraphicsView.h"
#include "pole.h"
#include <QTimer>
#include "collector.h"
using namespace Esri::ArcGISRuntime;

Simulator::Simulator(QWidget* parent /*=nullptr*/):
    QMainWindow(parent)
{

    // Create the Widget view
    m_mapView = new MapGraphicsView(this);

    // Create a map using the topographic Basemap
    m_map = new Map(Basemap::imagery(this), this);

    // Set map to map view
    m_mapView->setMap(m_map);

    // set the mapView as the central widget
    setCentralWidget(m_mapView);

    // set view center
    const Point center(19.8371305682558, 45.2403304784098, SpatialReference::wgs84());
    m_mapView->setViewpointCenter(center, 5000);

    staticOverlay = new GraphicsOverlay(this);
    dynamicOverlay = new GraphicsOverlay(this);
    m_mapView->graphicsOverlays()->append(staticOverlay);
    m_mapView->graphicsOverlays()->append(dynamicOverlay);

}

void Simulator::updateStaticGraphic(){

    QList<Pole*>::const_iterator it = poles.begin();
    for(;it!=poles.end();++it){
        this->staticOverlay->graphics()->append((*it)->getGraphicPoint());
    }
}

void Simulator::updateDynamicGraphic(QList<Pedestrian*>* pedestrians, QList<Vehicle*>* vehicles)
{
    this->dynamicOverlay->graphics()->clear();

    QList<Pedestrian*>::const_iterator it = pedestrians->begin();
    QList<Vehicle*>::const_iterator kt = vehicles->begin();
    for(;it!=pedestrians->end();++it){
        this->dynamicOverlay->graphics()->append((*it)->getGraphicPoint());
    }

    for(;kt!=vehicles->end();++kt){
        this->dynamicOverlay->graphics()->append((*kt)->getGraphicPoint());
    }
    pedestrians->clear();
    vehicles->clear();
    emit graphicUpdated();

}


// destructor
Simulator::~Simulator()
{
}
