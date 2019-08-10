#include "methodeditor.h"

MethodEditor::MethodEditor(): FunctionEditor ()
{
    setFixedHeight(300);

    m_scope=new QComboBox;
    m_scope->addItem("public");
    m_scope->addItem("protected");
    m_scope->addItem("private");
    m_flLine->addRow("Scope", m_scope);

    m_const=new QCheckBox;
    m_flLine->addRow("Make constant fonction", m_const);

    m_virtual=new QRadioButton("virtual");
    m_static=new QRadioButton("static");
    m_normal=new QRadioButton("");
    m_normal->setChecked(true);

    QGridLayout *glMode=new QGridLayout;
    glMode->addWidget(m_normal, 0, 0);
    glMode->addWidget(m_virtual, 1, 0);
    glMode->addWidget(m_static, 2, 0);

    m_pureVirtual=new QCheckBox("pure virtual");
    m_pureVirtual->setEnabled(false);
    glMode->addWidget(m_pureVirtual, 1, 1);

    QGroupBox *gbMode=new QGroupBox;
    gbMode->setLayout(glMode);
    m_vlmain->insertWidget(1, gbMode);

    connect(m_virtual, SIGNAL(toggled(bool)), this, SLOT(enableVirtual(bool)));
    connect(m_validate, SIGNAL(clicked()), this, SLOT(validate()));

}

void MethodEditor::enableVirtual(bool value){
    if(value){
        m_pureVirtual->setEnabled(true);
    }
    else{
        m_pureVirtual->setEnabled(false);
    }
}

void MethodEditor::validate(){
    if(!m_function.isNull()){
        m_function="";
    }
    if(!m_name->text().isEmpty()){
        m_function+=m_scope->currentText()+" ";
        if(m_virtual->isChecked()){
            m_function+="virtual ";
        }
        else if(m_static->isChecked()){
            m_function+="static ";
        }

        genFunction();

        if(m_virtual->isChecked() && m_pureVirtual->isChecked()){
            m_function+= " =0";
        }
        if(m_const->isChecked()){
            m_function+= " const";
        }
    }

    accept();
}

