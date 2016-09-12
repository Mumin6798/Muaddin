//Muaddin includes.
#include "maindisplay.h"
#include "mainmenubar.h"
#include "prayergroup.h"
#include "athangroup.h"

//Qt includes.
#include <QLabel>
#include <QPainter>
#include <QSlider>
#include <QEvent>

MainDisplay::MainDisplay(QWidget *parent) : QMainWindow(parent){
    //Create the GUI.
    CreateMenuBar();
    CreateCentralWidget();
    CreatePrayers();
    CreateLocation();
    CreateAthan();   
}

void MainDisplay::CreateMenuBar(){
    //Creating MenuBar.
    MenuBar = new MainMenuBar(this);

    //Connecting the MenuBar signals to the slots.
    connect(MenuBar, &MainMenuBar::SetViewToDefault, this, &MainDisplay::SetViewToDefault);
    connect(MenuBar, &MainMenuBar::SetViewToMinimal, this, &MainDisplay::SetViewToMinimal);

    //Adding MenuBar to display.
    MainDisplay::setMenuBar(MenuBar);
}

void MainDisplay::SetViewToDefault(){
    //Changing the size of the display and the widgets.
    MainDisplay::setFixedSize(640, 360);
    CentralWidget->setFixedSize(MainDisplay::width(), MainDisplay::height());
    MenuBar->setFixedWidth(MainDisplay::width());
    DateLabel->setGeometry(0, 5, MainDisplay::width(), 20);
    TimeLabel->setGeometry(0, 25, MainDisplay::width(), 20);
    NextPrayerLabel->setGeometry(0, 310, MainDisplay::width(), 20);
    //Changing actions so DefaultAction is ticked and MinimalAction is not ticked.
    MenuBar->DefaultAction->setChecked(true);
    MenuBar->MinimalAction->setChecked(false);
    //Making the LocationGroup visible and repainting CentralWidget.
    LocationGroup->show();
    CentralWidget->repaint();
}

void MainDisplay::SetViewToMinimal(){
    //Changing the size of the display and the widgets.
    MainDisplay::setFixedSize(300, 360);
    CentralWidget->setFixedSize(MainDisplay::width(), MainDisplay::height());
    MenuBar->setFixedWidth(MainDisplay::width());
    DateLabel->setGeometry(0, 5, MainDisplay::width(), 20);
    TimeLabel->setGeometry(0, 25, MainDisplay::width(), 20);
    NextPrayerLabel->setGeometry(0, 310, MainDisplay::width(), 20);
    //Changing actions so MinimalAction is ticked and DefaultAction is not ticked.
    MenuBar->DefaultAction->setChecked(false);
    MenuBar->MinimalAction->setChecked(true);
    //Making the LocationGroup invisible and repainting CentralWidget.
    LocationGroup->hide();
    CentralWidget->repaint();
}

void MainDisplay::CreateCentralWidget(){
    //Creating the CentralWidget.
    CentralWidget = new QWidget(this);

    //Creating the time and date labels.
    DateLabel = new QLabel(CentralWidget);
    TimeLabel = new QLabel(CentralWidget);
    NextPrayerLabel = new QLabel(CentralWidget);
    //Setting the text to the centre of the labels.
    DateLabel->setAlignment(Qt::AlignHCenter);
    TimeLabel->setAlignment(Qt::AlignHCenter);
    NextPrayerLabel->setAlignment(Qt::AlignHCenter);

    //Adding the CentralWidget and StatusBar to the display.
    MainDisplay::setCentralWidget(CentralWidget);
}

void MainDisplay::UpdateDateLabel(QString NewDate){
    //Updating date.
    DateLabel->setText("<font size=5>"+NewDate+"</font>");
}

void MainDisplay::UpdateTimeLabel(QString NewTime){
    //Updating time.
    TimeLabel->setText("<font size=5>"+NewTime+"</font>");
}

void MainDisplay::UpdateNextPrayerLabel(QString NextPrayer){
    //Updating the next prayer label.
    NextPrayerLabel->setText("<font size=3>"+NextPrayer+"</font>");
}

void MainDisplay::UpdateCompass(int NewAngle){
    //Updating the compass.
    MainDisplay::Angle = NewAngle;
    CentralWidget->repaint();
}

void MainDisplay::CreatePrayers(){
    //Creating PrayerGroup.
    Prayergroup = new PrayerGroup(CentralWidget);

    //Setting the location of the group.
    Prayergroup->setGeometry(44, 40, 233, 180);
}

void MainDisplay::CreateLocation(){
    //Creating an empty group so the painting goes on top.
    LocationGroup = new QGroupBox(tr("Location"), CentralWidget);
    LocationGroup->setGeometry(363, 40, 233, 252);
    LocationGroup->setAlignment(Qt::AlignRight);
}

void MainDisplay::CreateAthan(){
    //Creating AthanGroup.
    Athangroup = new AthanGroup(CentralWidget);

    //Setting the location of the group.
    Athangroup->setGeometry(44, 230, 233, 60);
}

void MainDisplay::paintEvent(QPaintEvent *){
    //Checking to see if the display is in default view.
    if(LocationGroup->isVisible()){
        //Creating the compass.
        QPainter painter(this);
        painter.setRenderHints(QPainter::HighQualityAntialiasing);
        int a = 480;
        int b = 195;
        int r = 110;
        QPen pen(Qt::black);
        pen.setWidth(4);
        painter.setPen(pen);
        painter.translate(a, b);
        painter.rotate(Angle);
        painter.translate(-a, -b);
        painter.drawPoint(a, b);
        QPen pen1(Qt::black);
        pen1.setWidth(2);
        painter.setPen(pen1);
        painter.drawLine(a, b, a, b - r);
        QPolygon poly;
        poly << QPoint(a, b - r) << QPoint(a - 5, b - r + 10) << QPoint(a + 5, b - r + 10);
        QPainterPath tmpPath;
        tmpPath.addPolygon(poly);
        painter.fillPath(tmpPath, QBrush(Qt::black));
        painter.drawEllipse(QPoint(a, b), r, r);
    }
}

void MainDisplay::changeEvent(QEvent *event){
    //Checking if the language has changed and then updating text.
    if(event->type() == QEvent::LanguageChange){
        LocationGroup->setTitle(tr("Location"));
    }else{
        QWidget::changeEvent(event);
    }
}

MainDisplay::~MainDisplay(){
    //Stopping TimeThread.
    emit StopTimeThread();

    //Save the user preferences.
    emit SavePreferences();
}
