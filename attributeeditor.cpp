#include "attributeeditor.h"

AttributeEditor::AttributeEditor(QString language): QDialog (), m_language(language)
{
    if(m_language=="cpp"){
        setFixedSize(400, 200);
        QFormLayout *flMain=new QFormLayout;

        m_name=new QLineEdit;
        m_type=new QLineEdit;

        m_scope=new QComboBox;
        m_scope->addItem("protected");
        m_scope->addItem("private");

        m_const=new QCheckBox;

        flMain->addRow("Name", m_name);
        flMain->addRow("Type", m_type);
        flMain->addRow("Scope", m_scope);
        flMain->addRow("Make attribute constant", m_const);

        QHBoxLayout *hbButtons=new QHBoxLayout;
        m_validate=new QPushButton("Validate");
        m_cancel= new QPushButton("Cancel");
        hbButtons->addWidget(m_validate);
        hbButtons->addWidget(m_cancel);

        QVBoxLayout *vlMain=new QVBoxLayout;
        vlMain->addLayout(flMain);
        vlMain->addLayout(hbButtons);

        setLayout(vlMain);
    }

    connect(m_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_validate, SIGNAL(clicked()), this, SLOT(validate()));
}

QString AttributeEditor::getAttribute(){
    return m_attribute;
}

void AttributeEditor::cppGenAttribute(){
    m_attribute+=m_scope->currentText()+" ";
    m_attribute+=m_type->text() +" ";
    m_attribute+=m_name->text();

    if(m_const->isChecked()){
        m_attribute+=" const";
    }
}

void AttributeEditor::validate(){
    if(m_language=="cpp" && !m_name->text().isEmpty() && !m_type->text().isEmpty()){
        if(!m_attribute.isEmpty()){
            m_attribute="";
        }
        cppGenAttribute();
        accept();
    }
}
