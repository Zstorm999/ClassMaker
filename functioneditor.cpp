#include "functioneditor.h"

FunctionEditor::FunctionEditor(): QDialog ()
{
    m_vlmain=new QVBoxLayout;
    m_hlButtons=new QHBoxLayout;
    m_flLine=new QFormLayout;

    m_validate=new QPushButton("Validate");
    m_cancel= new QPushButton(("Cancel"));
    m_hlButtons->addWidget(m_validate);
    m_hlButtons->addWidget(m_cancel);

    m_name=new QLineEdit;
    m_type=new QLineEdit;
    m_arguments=new QLineEdit;
    m_arguments->setToolTip("Use a \",\" to separate arguments");

    m_flLine->addRow("Name", m_name);
    m_flLine->addRow("Return type", m_type);
    m_flLine->addRow("Arguments", m_arguments);

    QFormLayout *flButton=new QFormLayout;
    flButton->addRow("", m_hlButtons);

    m_vlmain->addLayout(m_flLine);
    m_vlmain->addLayout(flButton);

    setLayout(m_vlmain);

    setFixedSize(400, 200);
    connect(m_validate, SIGNAL(clicked()), this, SLOT(validate()));
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    m_function="";
}

void FunctionEditor::validate(){
    if(!m_function.isNull()){
        m_function="";
    }
    genFunction();
    accept();
}

QString FunctionEditor::getFunction(){
    return m_function;

}

void FunctionEditor::genFunction(){
    if(!m_name->text().isEmpty()){

        if(m_type->text().isEmpty()){
            m_function+="void ";
        }

        else{
            m_function+=m_type->text()+" ";
        }

        m_function+=m_name->text();
        m_function+="("+m_arguments->text()+")";
    }
}
