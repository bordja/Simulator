
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

// Qt headers
#include <QApplication>
#include <QMessageBox>


#include "ArcGISRuntimeEnvironment.h"

#include "Simulator.h"
#include "polearray.h"
#include "collector.h"
#include "header.h"
using namespace Esri::ArcGISRuntime;
int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication application(argc, argv);

    Simulator applicationWindow;
    PoleArray poleArray;
    Collector c;
    applicationWindow.setMinimumWidth(800);
    applicationWindow.setMinimumHeight(600);
    applicationWindow.show();
    applicationWindow.updateStaticGraphic(poleArray.getGraphicPoints(),poleArray.getArraySize());
    c.readFileHeader(0);
    c.readDataFromFile(0);
    return application.exec();
}
