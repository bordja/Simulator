
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
#include "collector.h"
#include "header.h"
#include "pole.h"
#include <QThread>
#include <QObject>
using namespace Esri::ArcGISRuntime;

void setPoles();

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication application(argc, argv);

    Simulator applicationWindow;

    Collector collector(applicationWindow);
    QThread producerThread;
    collector.moveToThread(&producerThread);
    producerThread.start();
    QObject::connect(&collector, SIGNAL(finished()), &producerThread, SLOT(quit()));

    setPoles();
    applicationWindow.setMinimumWidth(800);
    applicationWindow.setMinimumHeight(600);
    applicationWindow.show();
    applicationWindow.updateStaticGraphic();

    collector.start();
    return application.exec();
}

void setPoles(){

    Pole* p1 = new Pole(19.8371305682558, 45.2403304784098, 3306801);
    Pole* p2 = new Pole(19.835852304712, 45.2400027202778, 3306959);
    Pole* p3 = new Pole(19.8381933428869, 45.2404551891655, 3284215);
    Pole* p4 = new Pole(19.8380630431273, 45.240062964672, 3283042);
    Pole* p5 = new Pole(19.8345589037287, 45.2392289539056, 3284450);
    Pole* p6 = new Pole(19.8348513016058, 45.2393106533107, 3284451);
    Pole* p7 = new Pole(19.8351439792443, 45.2393911669633, 3284452);
    Pole* p8 = new Pole(19.8354366979173, 45.2394728321365, 3284453);
    Pole* p9 = new Pole(19.8357333311793, 45.2395555802512, 3284454);
    Pole* p10 = new Pole(19.8360249884538, 45.2396369091563, 3284455);
    Pole* p11 = new  Pole(19.8363148966923, 45.2397191014189, 3284456);
    Pole* p12 = new  Pole(19.8366070640388, 45.2398011089359, 3284457);
    Pole* p13 = new  Pole(19.8369002197694, 45.2398815329502, 3284458);
    Pole* p14 = new  Pole(19.8371930346256, 45.2399637255231, 3284459);
    Pole* p15 = new  Pole(19.8374866431909, 45.2400457634268, 3284460);
    Pole* p16 = new  Pole(19.8377318114169, 45.2401146922195, 3284461);
    Pole* p17 = new  Pole(19.8381016120946, 45.2402188836176, 3284462);
    Pole* p18 = new  Pole(19.8383297186554, 45.2402825535426, 3284463);
    Pole* p19 = new  Pole(19.8378687935717, 45.2404175182494, 3284216);
    Pole* p20 = new  Pole(19.8376413350343, 45.2403226279311, 3284217);
    Pole* p21 = new  Pole(19.8373802633169, 45.2402358636158, 3284218);
    Pole* p22 = new  Pole(19.8370856323088, 45.240153329113, 3284219);
    Pole* p23 = new  Pole(19.8367990190159, 45.2400649180941, 3284220);
    Pole* p24 = new  Pole(19.8365166678869, 45.2399861694715, 3284221);
    Pole* p25 = new  Pole(19.8362317005224, 45.2399064576629, 3284222);
    Pole* p26 = new  Pole(19.8359449609075, 45.2398268710969, 3284223);
    Pole* p27 = new  Pole(19.8356629730005, 45.2397510396861, 3284224);
    Pole* p28 = new  Pole(19.8352936637815, 45.2396431018536, 3284225);
    Pole* p29 = new  Pole(19.8350034769239, 45.2395640447638, 3284226);
    Pole* p30 = new  Pole(19.8347233084554, 45.2394853139176, 3284227);
    Pole* p31 = new  Pole(19.8344366643589, 45.2394062464638, 3284228);
    Pole* p32 = new  Pole(19.8381560091267, 45.2398922192009, 3283041);

    poles.append(p1);
    poles.append(p2);
    poles.append(p3);
    poles.append(p4);
    poles.append(p5);
    poles.append(p6);
    poles.append(p7);
    poles.append(p8);
    poles.append(p9);
    poles.append(p10);
    poles.append(p11);
    poles.append(p12);
    poles.append(p13);
    poles.append(p14);
    poles.append(p15);
    poles.append(p16);
    poles.append(p17);
    poles.append(p18);
    poles.append(p19);
    poles.append(p20);
    poles.append(p21);
    poles.append(p22);
    poles.append(p23);
    poles.append(p24);
    poles.append(p25);
    poles.append(p26);
    poles.append(p27);
    poles.append(p28);
    poles.append(p29);
    poles.append(p30);
    poles.append(p31);
    poles.append(p32);
}
