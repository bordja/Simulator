
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

#ifndef SIMULATOR_H
#define SIMULATOR_H

namespace Esri
{
namespace ArcGISRuntime
{
class Map;
class MapGraphicsView;
class GraphicsOverlay;
class Graphic;
}
}

#include <QMainWindow>
#include "file.h"
class Simulator : public QMainWindow
{
    Q_OBJECT
public:
    explicit Simulator(QWidget* parent = nullptr);
    ~Simulator() override;
    void updateStaticGraphic();
public slots:
    void updateDynamicGraphic(File** f);
signals:
    void graphicUpdated();
private:
    Esri::ArcGISRuntime::Map*                   m_map = nullptr;
    Esri::ArcGISRuntime::MapGraphicsView*       m_mapView = nullptr;
    Esri::ArcGISRuntime::GraphicsOverlay*       staticOverlay = nullptr;
    Esri::ArcGISRuntime::GraphicsOverlay*       dynamicOverlay = nullptr;
};

#endif // SIMULATOR_H
