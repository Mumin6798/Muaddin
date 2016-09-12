#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

//Qt includes.
#include <QMenuBar>

//Muaddin forward declaration.
class LanguageMenu;

class MainMenuBar : public QMenuBar{
    Q_OBJECT
    friend class MainCore;
    friend class MainDisplay;

public:
    explicit MainMenuBar(QWidget *parent = 0);

signals:
    void SetViewToDefault();
    void SetViewToMinimal();

protected:
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_DefaultAction(bool);
    void on_MinimalAction(bool);
    void on_GithubAction(bool);

private:
    //Functions.
    void CreateViewMenu();

    void CreateOptionsMenu();

    void CreateHelpMenu();

    void SetText();

    //Pointers.
    QWidget *Parent;

    QMenu *ViewMenu;
    QAction *DefaultAction;
    QAction *MinimalAction;

    QMenu *OptionsMenu;
    QAction *SettingsAction;
    LanguageMenu *Languagemenu;
    QAction *StartupAction;
    QAction *NoAthanAction;
    QAction *DefaultAthanAction;
    QAction *CustomAthanAction;

    QMenu *HelpMenu;
    QAction *GithubAction;
    QAction *AboutAction;

};

#endif
