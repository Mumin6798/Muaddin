#ifndef SYSTEMTRAYMENU_H
#define SYSTEMTRAYMENU_H

#include <QMenu>

class SystemTrayMenu : public QMenu{
    Q_OBJECT
    friend class MainCore;

public:
    explicit SystemTrayMenu(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    //Functions.
    void CreateHelp();
    void CreateView();
    void CreateExit();

    void SetText();

    //Pointers.
    QAction *GithubAction;
    QAction *AboutAction;

    QAction *DefaultAction;
    QAction *MinimalAction;

    QAction *ExitAction;
};

#endif
