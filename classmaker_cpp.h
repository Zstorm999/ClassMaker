#ifndef CLASSMAKER_CPP_H
#define CLASSMAKER_CPP_H

#include <QtWidgets>
#include <QPushButton>
#include "classviewer.h"
#include "functioneditor.h"
#include "methodeditor.h"
#include "attributeeditor.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

class ClassMaker_cpp : public QWidget
{
    Q_OBJECT
public:
    ClassMaker_cpp();
    void genCode();

public slots:
    void viewCode();
    void saveCode();
    void setHeaderName(const QString & hName);

    void enableCopyC(int value);
    void enableVirtualD(int value);
    void enableHeaderName(int value);
    void enableComments(int value);

    void addMethod();
    void delMethod();

    void addAttribute();
    void delAttribute();

private:
    QString sourceCode;
    QString headerCode;
    //General

    QLineEdit *m_name;
    QLineEdit *m_inheritance;

    //Options

    QCheckBox *m_headerProt;
    QLineEdit *m_headerName;
    QCheckBox *m_constructor;
    QCheckBox *m_copyC;
    QCheckBox *m_destructor;
    QCheckBox *m_virtualD;
    //add a widget for header inclusions

    //Attributes
    //to set later

    QListWidget *m_listAtt;

    QPushButton *m_addAtt;
    QPushButton *m_editAtt;
    QPushButton *m_delAtt;

    //Methods
    //to set later

    QListWidget *m_listMethod;

    QPushButton *m_addMethod;
    QPushButton *m_editMethod;
    QPushButton *m_delMethod;

    //Comments

    QCheckBox *m_doComments;

    QFormLayout *m_flComments;
    QLineEdit *m_author;
    QDateEdit *m_date;
    QTextEdit *m_comments;

    //Validate

    QPushButton *m_view;
    QPushButton *m_save;

};

#endif // CLASSMAKER_CPP_H
