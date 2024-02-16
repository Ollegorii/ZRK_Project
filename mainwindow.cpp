#include "mainwindow.h"
#include "./ui_mainwindow.h"

//drawline

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controlPointsLayer->startEditing();

    QgsFeatureRenderer* layerRenderer= controlPointsLayer->renderer();
    QgsSingleSymbolRenderer *mSingleRenderer = QgsSingleSymbolRenderer::convertFromRenderer(layerRenderer);
    QgsMarkerSymbol* symbol = new  QgsMarkerSymbol();
    QVariantMap mp;
    mp[QString("name")]= QVariant("plane.svg");
    mp[QString("size")]= QVariant("6");

    QgsSvgMarkerSymbolLayer svglayer("../ZRK115/icons/plane.svg");
    QgsSymbolLayer* svgsymbol=svglayer.create(mp);
    auto newsym=     symbol->createSimple(mp);
    newsym->changeSymbolLayer(0,svgsymbol);
    mSingleRenderer->setSymbol(newsym);
    controlPointsLayer->setRenderer(mSingleRenderer);
    controlPointsLayer->triggerRepaint();
    controlPointsLayer->dataProvider()->addAttributes({QgsField("fid", QVariant::Int)});
    controlPointsLayer->updateFields();

    controlPointsLayer->setLabelsEnabled(true);
    QgsPalLayerSettings pls;
    pls.fieldName = "fid";
    pls.placement = QgsPalLayerSettings::Placement::Line;
    QgsVectorLayerSimpleLabeling* simple_label = new QgsVectorLayerSimpleLabeling(pls);
    controlPointsLayer->setLabeling(simple_label);
    controlPointsLayer->commitChanges();


    dbWindow = new DatabaseWindow(controller);
    stWindow = new SettingsWindow(controller);

    map = new QgsMapCanvas(this);
    map->setLayers({planeImageLayer, missileImageLayer, controlPointsLayer, trajectoryPointsLayer, missileLayer, polylineLayer, circleLayer, radarLayer, ringLayer, earthLayer, oceanLayer});
    map->setExtent(earthLayer->extent());
    map->enableAntiAliasing(true);
    QgsCoordinateReferenceSystem crs("EPSG:4326");
    map->setDestinationCrs(crs);
    map->refresh();
    this->setCentralWidget(map);
    centersZrk = {{36, 60}, {44, 51}, {64, 64}, {91, 58}};

    addZrk(centersZrk[0], 3, 4);
    addZrk(centersZrk[1], 3, 4);
    addZrk(centersZrk[2], 3, 4);
    addZrk(centersZrk[3], 3, 4);
    this->setMinimumSize(1200, 800);
    //this->setMinimumSize(1900, 990);

    toolBar = new QToolBar(this);

    QAction* activateDbWindow = new QAction(QIcon("../ZRK115/icons/db_icon.svg"), "База данных", toolBar);
    QAction* activatePanAction = new QAction(QIcon("../ZRK115//icons/grab.svg"), "Пан", toolBar);
    QAction* activateSelectMode = new QAction(QIcon("../ZRK115/icons/select.svg"), "Выбор начальной и конечной точек", toolBar);
    QAction* playAction = new QAction(QIcon("../ZRK115/icons/play.svg"), "Запуск", toolBar);
    QAction* clearAction = new QAction(QIcon("../ZRK115/icons/back2.svg"), "Очистить точки", toolBar);
    QAction* planeAction = new QAction(QIcon("../ZRK115/icons/settings.svg"), "Очистить точки", toolBar);

    toolBar->addAction(activatePanAction);
    toolBar->addSeparator();
    toolBar->addAction(activateSelectMode);
    toolBar->addSeparator();
    toolBar->addAction(playAction);
    toolBar->addSeparator();
    toolBar->addAction(clearAction);
    toolBar->addSeparator();
    toolBar->addAction(activateDbWindow);
    toolBar->addSeparator();
    toolBar->addAction(planeAction);

    connect(activatePanAction, &QAction::triggered, this, &MainWindow::activatePan);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearAllPoints);
    connect(activateSelectMode, &QAction::triggered, this, &MainWindow::activateSelecting);
    connect(playAction, &QAction::triggered, this, &MainWindow::play);
    connect(activateDbWindow, &QAction::triggered, this, &MainWindow::showDbWindow);
    connect(planeAction, &QAction::triggered, this, &MainWindow::changePlane);

    this->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
}

MainWindow::~MainWindow()
{
    delete map;
    delete controlPointsLayer;
    delete trajectoryPointsLayer;
    delete earthLayer;
    delete oceanLayer;
    delete toolBar;
}

void MainWindow::activatePan()
{
    QgsMapToolPan* panTool = new QgsMapToolPan(map);
    map->setMapTool(panTool);
}

void MainWindow::play()
{
    if (Points.empty())
        return;

    this->setEnabled(false);

    if(vector_point_size == 0)
        vector_point_size = Points.size();

    Plane p1 = Plane(stWindow->get_id(), Points[0].x(), Points[0].y(), controller);
    for(int j = 1; j < vector_point_size; ++j)
        p1.add_waypoint({Points[j].x(), Points[j].y()});

    Launcher l0 = Launcher(centersZrk[0].x(), centersZrk[0].y(), 4, 3);
    Launcher l1 = Launcher(centersZrk[1].x(), centersZrk[1].y(), 4, 3);
    Launcher l2 = Launcher(centersZrk[2].x(), centersZrk[2].y(), 4, 3);
    Launcher l3 = Launcher(centersZrk[3].x(), centersZrk[3].y(), 4, 3);

    Loop loop({&p1}, {&l0, &l1, &l2, &l3});

    connect(&loop, &Loop::drawPoint, this, &MainWindow::addTrajectoryPoint);
    connect(&loop, &Loop::drawMissilePoint, this, &MainWindow::addMissilePoint);
    connect(&loop, &Loop::drawLine, this, &MainWindow::addPolyline);
    connect(&loop, &Loop::drawRadar, this, &MainWindow::pingRadar);

    loop.start();

    this->setEnabled(true);
}

void MainWindow::addTrajectoryPoint(std::pair<double, double> p, double angle)
{
    trajectoryPointsLayer->startEditing();
    QgsFeature f1;
    QgsFeatureIterator iter1 = trajectoryPointsLayer->getFeatures();
    while(iter1.nextFeature(f1))
        trajectoryPointsLayer->deleteFeature(f1.id());
    trajectoryPointsLayer->commitChanges();

    QgsPointXY point = {p.first, p.second};

    QgsFeature f;
    f.setFields(trajectoryPointsLayer->fields(), true);

    f.setGeometry(QgsGeometry::fromPointXY(point));

    trajectoryPointsLayer->startEditing();
    trajectoryPointsLayer->addFeature(f);
    trajectoryPointsLayer->commitChanges();

    QgsMarkerSymbol* symbol = new QgsMarkerSymbol();  // создаем символ маркера
    QgsRasterMarkerSymbolLayer* layer = new QgsRasterMarkerSymbolLayer();  // создаем слой символа маркера
    layer->setPath(planeImageLayer->dataProvider()->dataSourceUri());  // указываем источник данных изображения
    layer->setSize(8);  // указываем размер маркера
    layer->setOffset(QPointF(0, 0));  // указываем смещение маркера относительно точки
    layer->setAngle(0 - angle);
    symbol->appendSymbolLayer(layer);  // добавляем слой символа маркера в символ маркера
    trajectoryPointsLayer->setRenderer(new QgsSingleSymbolRenderer(symbol));

    //map->refresh();
}

void MainWindow::addPolyline(std::vector<std::pair<double, double>> p)
{
    QVector<QgsPointXY> points = {{p[0].first, p[0].second}, {p[1].first, p[1].second}};
    std::cout  << "Hello! " << points[0].x() << std::endl;
    QgsFeature f;
    f.setFields(polylineLayer->fields(), true);

    f.setGeometry(QgsGeometry::fromPolylineXY(points));

    polylineLayer->startEditing();
    polylineLayer->addFeature(f);
    polylineLayer->commitChanges();
}

void MainWindow::activateSelecting()
{
    QgsMapToolEmitPoint* emitPointTool = new QgsMapToolEmitPoint(map);
    map->setMapTool(emitPointTool);

    connect(emitPointTool, &QgsMapToolEmitPoint::canvasClicked, this, &MainWindow::addControlPoint);
}

void MainWindow::clearAllPoints()
{
    Points.clear();
    vector_point_size = 0;

    controlPointsLayer->startEditing();
    QgsFeature f;
    QgsFeatureIterator iter = controlPointsLayer->getFeatures();
    while(iter.nextFeature(f))
        controlPointsLayer->deleteFeature(f.id());
    controlPointsLayer->commitChanges();

    trajectoryPointsLayer->startEditing();
    QgsFeature f1;
    QgsFeatureIterator iter1 = trajectoryPointsLayer->getFeatures();
    while(iter1.nextFeature(f1))
        trajectoryPointsLayer->deleteFeature(f1.id());
    trajectoryPointsLayer->commitChanges();

    polylineLayer->startEditing();
    QgsFeature f2;
    QgsFeatureIterator iter2 = polylineLayer->getFeatures();
    while(iter2.nextFeature(f2))
        polylineLayer->deleteFeature(f2.id());
    polylineLayer->commitChanges();

    missileLayer->startEditing();
    QgsFeature f3;
    QgsFeatureIterator iter3 = missileLayer->getFeatures();
    while(iter3.nextFeature(f3))
        missileLayer->deleteFeature(f3.id());
    missileLayer->commitChanges();
}

void MainWindow::addControlPoint(const QgsPointXY &point, Qt::MouseButton button)
{
    if (vector_point_size == 0)
    {
        Points.push_back(point);

        controlPointsLayer->startEditing();

        QgsFeature feat;
        feat.setFields(controlPointsLayer->fields(), true);
        feat.setAttribute("fid", Points.size() - 1);
        feat.setGeometry(QgsGeometry::fromPointXY(point));
        controlPointsLayer->addFeature(feat);
        controlPointsLayer->commitChanges();
    }
    else
    {
        activatePan();
    }
}

void MainWindow::addZrk(const QgsPoint &p, double r1, double r2)
{
    QgsCircle Circle = QgsCircle(p, r1);
    auto CircleWkt = Circle.toPolygon()->asWkt();
    QgsFeature f;
    f.setFields(circleLayer->fields(), true);
    f.setGeometry(QgsGeometry::fromWkt(CircleWkt));
    circleLayer->startEditing();
    circleLayer->addFeature(f);
    circleLayer->commitChanges();

    Circle = QgsCircle(p, r2);
    CircleWkt = Circle.toCircularString()->asWkt();
    f.setFields(ringLayer->fields(), true);
    f.setGeometry(QgsGeometry::fromWkt(CircleWkt));
    ringLayer->startEditing();
    ringLayer->addFeature(f);
    ringLayer->commitChanges();

}

void MainWindow::pingRadar(const std::vector<Launcher*>& launchers, double radius)
{
    QVector<QgsFeature> features;
    for (int i = 0; i < launchers.size(); ++i)
    {
        QgsPoint p = {launchers[i]->getCenter().first, launchers[i]->getCenter().second};
        QgsCircle Circle = QgsCircle(p, radius);
        auto CircleWkt = Circle.toPolygon()->asWkt();
        QgsFeature f;
        f.setFields(radarLayer->fields(), true);
        f.setGeometry(QgsGeometry::fromWkt(CircleWkt));
        radarLayer->startEditing();
        radarLayer->addFeature(f);
        radarLayer->commitChanges();
    }
    QTest::qWait(100);
    radarLayer->startEditing();
    QgsFeature f1;
    QgsFeatureIterator iter1 = radarLayer->getFeatures();
    while(iter1.nextFeature(f1))
        radarLayer->deleteFeature(f1.id());
    radarLayer->commitChanges();

}

void MainWindow::showDbWindow()
{
    dbWindow->show();
}

void MainWindow::changePlane()
{
    stWindow->update_list();
    stWindow->show();
}

void MainWindow::addMissilePoint(std::pair<double, double> p, double angle)
{
    missileLayer->startEditing();
    QgsFeature f1;
    QgsFeatureIterator iter1 = missileLayer->getFeatures();
    while(iter1.nextFeature(f1))
        missileLayer->deleteFeature(f1.id());
    missileLayer->commitChanges();

    QgsPointXY point = {p.first, p.second};

    QgsFeature f;
    f.setFields(missileLayer->fields(), true);

    f.setGeometry(QgsGeometry::fromPointXY(point));

    missileLayer->startEditing();
    missileLayer->addFeature(f);
    missileLayer->commitChanges();

    QgsMarkerSymbol* symbol = new QgsMarkerSymbol();
    QgsRasterMarkerSymbolLayer* layer = new QgsRasterMarkerSymbolLayer();
    layer->setPath(missileImageLayer->dataProvider()->dataSourceUri());
    layer->setSize(4);
    layer->setOffset(QPointF(0, 0));
    layer->setAngle(90 - angle);
    symbol->appendSymbolLayer(layer);
    missileLayer->setRenderer(new QgsSingleSymbolRenderer(symbol));
}
