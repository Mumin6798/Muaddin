//Muaddin include.
#include "languagemenu.h"

LanguageMenu::LanguageMenu(QWidget *parent) : QMenu(parent){
    //Setting up supported languages.
    Languages = (QStringList() << "English (en)" << "العربية (ar)");

    //Create Language Actions.
    CreateActions(Languages.indexOf(QRegExp(tr("English")+" *", Qt::CaseSensitive, QRegExp::Wildcard)));
}

void LanguageMenu::CreateActions(int CurrentLanguageIndex){
    //Creating actions and it's properties then adds it to the menu.
    for(int i = 0; i < Languages.size(); i++){
        QString Language = Languages.at(i);
        QAction *Action = new QAction(QString(Language).remove(QRegExp(" (*", Qt::CaseSensitive, QRegExp::Wildcard)));
        Action->setCheckable(true);
        if(CurrentLanguageIndex == i){Action->setChecked(true);}
        connect(Action, &QAction::triggered, this, &LanguageMenu::on_LanguageAction);
        ActionsMap.insert(Action, Language.remove(QRegExp("*(", Qt::CaseSensitive, QRegExp::Wildcard)).remove(')'));
        LanguageMenu::addAction(Action);
    }
}

void LanguageMenu::on_LanguageAction(bool){
    //Getting the sender and checking if the language is already set.
    QAction *Action = qobject_cast<QAction *>(LanguageMenu::sender());
    if(Action->isChecked()){
        //Getting all actions that are not Action and making them all unchecked and then updating the translation.
        QList<QAction *> TempActionsList = ActionsMap.keys();
        TempActionsList.removeAll(Action);
        for(int i = 0; i < TempActionsList.size(); i++){
            TempActionsList.at(i)->setChecked(false);
        }
        emit UpdateLanguage(ActionsMap.value(Action));
    }else{
        //Making the action checked agian.
        Action->setChecked(true);
    }
}
