#ifndef LANGUAGEMENU_H
#define LANGUAGEMENU_H

#include <QMenu>

class LanguageMenu : public QMenu{
    Q_OBJECT
    friend class MainCore;

public:
    explicit LanguageMenu(QWidget *parent = 0);

signals:
    void UpdateLanguage(QString NewLanguage);

private slots:
    void on_LanguageAction(bool);

private:
    //Function.
    void CreateActions(int CurrentLanguageIndex);

    //Variables.
    QStringList Languages;
    QMap<QAction *, QString> ActionsMap;
};
#endif
