#ifndef METHODEDITOR_H
#define METHODEDITOR_H

#include "functioneditor.h"

class MethodEditor : public FunctionEditor
{
    Q_OBJECT
public:
    MethodEditor();

public slots:
    void enableVirtual(bool value);
    void validate();


private:
    QComboBox *m_scope;

    QCheckBox *m_const;

    QRadioButton *m_normal;
    QRadioButton *m_virtual;
    QRadioButton *m_static;
    QCheckBox *m_pureVirtual;
};

#endif // METHODEDITOR_H
