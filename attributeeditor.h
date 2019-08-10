#ifndef ATTRIBUTEEDITOR_H
#define ATTRIBUTEEDITOR_H


#include <QDialog>
#include <QtWidgets>

class AttributeEditor : public QDialog
{
    Q_OBJECT
public:
    AttributeEditor(QString language=QString("cpp"));
    QString getAttribute();

public slots:
    void validate();

private:
    void cppGenAttribute();

    QString m_attribute;
    QString m_language;

    QLineEdit *m_name;
    QLineEdit *m_type;
    QComboBox *m_scope;
    QCheckBox *m_const;

    QPushButton *m_validate;
    QPushButton *m_cancel;

};

#endif // ATTRIBUTEEDITOR_H
