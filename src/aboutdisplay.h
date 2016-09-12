#ifndef ABOUTDISPLAY_H
#define ABOUTDISPLAY_H

//Qt include.
#include <QDialog>

//Qt forward declarations.
class QSvgWidget;
class QLabel;

class AboutDisplay : public QDialog{
    Q_OBJECT

public:
    explicit AboutDisplay(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    //Functions.
    void SetUpDisplay();

    void CreateImage();

    void CreateText();

    void SetText();

    //Pointers.
    QWidget *CentralWidget;

    QSvgWidget *SVGWidget;

    QLabel *AboutLabel;
    QLabel *DonationLabel;
};

#endif
