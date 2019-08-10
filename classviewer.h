#ifndef CLASSVIEWER_H
#define CLASSVIEWER_H

#include <QtWidgets>
#include <QDialog>

class ClassViewer : public QDialog
{
    Q_OBJECT
public:
    ClassViewer(QString code,QString header=QString(), QString language=QString("cpp"));

private:
    QTextEdit *m_code;
    QTextEdit *m_header;
    QPushButton *m_save;

};

#endif // CLASSVIEWER_H
