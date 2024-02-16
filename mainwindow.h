#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgsmapcanvas.h>
#include <qgsvectorlayer.h>
#include <qgsgeometry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsmarkersymbollayer.h>
#include <QToolBar>
#include <qgsmaptoolpan.h>
#include <qgsmaptoolemitpoint.h>
#include <qgslabeling.h>
#include <qgsfield.h>
#include <qgsvectorlayerlabeling.h>
#include <qgspallabeling.h>
#include <qgsrulebasedrenderer.h>
#include <QStatusBar>
#include <qgssymbol.h>
#include <qgsgeometry.h>
#include <unistd.h>
#include <QThread>
#include <QTest>
#include "databasewindow.h"
#include "databasecontroller.h"
#include "FlyingObject.h"
#include "Plane.h"
#include "Missile.h"
#include "Launcher.h"
#include "settingswindow.h"
#include "qgscircle.h"
#include "qgscoordinatereferencesystem.h"
#include "loop.h"
#include "qgsrasterlayer.h"
#include "qgsannotationitem.h"
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QgsMapCanvas* map = nullptr;
    DatabaseController* controller = new DatabaseController("../ZRK115/zrkdb.sqlite");

    QgsVectorLayer* controlPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
    QgsVectorLayer* trajectoryPointsLayer = new QgsVectorLayer("Point", "Points", "memory");
    QgsVectorLayer* missileLayer = new QgsVectorLayer("Point", "Points", "memory");
    QgsVectorLayer* polylineLayer = new QgsVectorLayer("LineString?crs=epsg:4326", "line", "memory");
    QgsVectorLayer* circleLayer = new QgsVectorLayer("Polygon", "poly", "memory");
    QgsVectorLayer* radarLayer = new QgsVectorLayer("Polygon", "Poly", "memory");
    QgsVectorLayer* ringLayer = new QgsVectorLayer("LineString", "line", "memory");

    QgsVectorLayer* earthLayer = new QgsVectorLayer("../ZRK115/Zrk_on_map/map.shp", "earth", "ogr");
    QgsVectorLayer* oceanLayer = new QgsVectorLayer("../ZRK115/Ocean_map/ocean.shp", "water", "ogr");
    QgsVectorLayer* zrkLayer = new QgsVectorLayer("../ZRK115/Zrk_on_map/zrk.shp", "earth", "ogr");

    QgsRasterLayer* planeImageLayer = new QgsRasterLayer("../ZRK115/icons/plane1.svg", "planeImage");
    QgsRasterLayer* missileImageLayer = new QgsRasterLayer("../ZRK115/icons/missile.svg", "missileImage");

    QToolBar* toolBar;

    DatabaseWindow* dbWindow;
    SettingsWindow* stWindow;

    QVector<QgsPointXY> Points;
    QVector<QgsPoint> centersZrk;

    void addZrk(const QgsPoint &p, double r1, double r2);

    Ui::MainWindow *ui;

    int vector_point_size{0};

public slots:
    void addTrajectoryPoint(std::pair<double, double> p, double angle);
    void addMissilePoint(std::pair<double, double> p, double angle);
    void addPolyline(std::vector<std::pair<double, double>> p);
    void pingRadar(const std::vector<Launcher*>& launchers, double radius);

private slots:
    void activatePan();
    void clearAllPoints();
    void play();
    void activateSelecting();
    void showDbWindow();
    void addControlPoint(const QgsPointXY &point, Qt::MouseButton button);
    void changePlane();

};
#endif // MAINWINDOW_H
