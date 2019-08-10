#ifndef FUNCTIONEDITOR_H
#define FUNCTIONEDITOR_H

#include <QDialog>
#include <QtWidgets>

class FunctionEditor : public QDialog
{
    Q_OBJECT
public:
    FunctionEditor();
    QString getFunction();

public slots:
    void validate();

protected:
    void genFunction();

    QString m_function;

    QPushButton *m_validate;
    QPushButton *m_cancel;

    QLineEdit *m_name;
    QLineEdit *m_type;
    QLineEdit *m_arguments;

    QFormLayout *m_flLine;
    QHBoxLayout *m_hlButtons;
    QVBoxLayout *m_vlmain;
};

#endif // FUNCTIONEDITOR_H
