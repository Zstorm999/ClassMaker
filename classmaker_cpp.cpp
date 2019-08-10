#include "classmaker_cpp.h"

ClassMaker_cpp::ClassMaker_cpp() : QWidget()
{
    //layout
    QGridLayout *glMain=new QGridLayout;

    QGroupBox *gbGeneral= new QGroupBox("General");
    QGroupBox *gbOptions= new QGroupBox("Options");
    QGroupBox *gbMethods=new QGroupBox("Methods");
    QGroupBox *gbAttributes=new QGroupBox("Attributes");
    QGroupBox *gbComments= new QGroupBox("Comments");

    QVBoxLayout *vlOptions=new QVBoxLayout;
    QVBoxLayout *vlMethods=new QVBoxLayout;
    QVBoxLayout *vlAttributes=new QVBoxLayout;
    QVBoxLayout *vlComments=new QVBoxLayout;

    QHBoxLayout *hlMembers=new QHBoxLayout;
    QHBoxLayout *hlValidate=new QHBoxLayout;
    QHBoxLayout *hlMethods=new QHBoxLayout;
    QHBoxLayout *hlAttributes= new QHBoxLayout;

    //General
    m_name= new QLineEdit;
    m_inheritance= new QLineEdit;

    QFormLayout *flGeneral=new QFormLayout;
    flGeneral->addRow("Class name", m_name);
    flGeneral->addRow("Inheritance", m_inheritance);

    gbGeneral->setLayout(flGeneral);

    //Options

    m_headerProt= new QCheckBox("Protect against multiple inclusion");
    m_headerProt->setChecked(true);
    m_headerName= new QLineEdit;
    QHBoxLayout *hbHeaderProt=new QHBoxLayout;
    hbHeaderProt->addWidget(m_headerProt);
    hbHeaderProt->addWidget(m_headerName);

    m_constructor=new QCheckBox("Generate constructor");
    m_constructor->setChecked(true);
    m_copyC=new QCheckBox("Generate copy constructor");
    m_destructor=new QCheckBox("Generate destructor");
    m_virtualD= new QCheckBox("Destructor is virtual");
    m_virtualD->setEnabled(false);

    vlOptions->addLayout(hbHeaderProt);
    vlOptions->addWidget(m_constructor);
    vlOptions->addWidget(m_copyC);
    vlOptions->addWidget(m_destructor);
    vlOptions->addWidget(m_virtualD);

    gbOptions->setLayout(vlOptions);

    //Methods
    m_addMethod= new QPushButton("Add");
    m_editMethod= new QPushButton("Edit");
    m_editMethod->setEnabled(false);
    m_delMethod= new QPushButton("Delete");
    hlMethods->addWidget(m_addMethod);
    hlMethods->addWidget(m_editMethod);
    hlMethods->addWidget(m_delMethod);

    m_listMethod=new QListWidget;
    m_listMethod->setSortingEnabled(true);
    vlMethods->addWidget(m_listMethod);
    vlMethods->addLayout(hlMethods);

    gbMethods->setLayout(vlMethods);


    //Attributes
    m_addAtt= new QPushButton("Add");
    m_editAtt= new QPushButton("Edit");
    m_editAtt->setEnabled(false);
    m_delAtt= new QPushButton("Delete");
    hlAttributes->addWidget(m_addAtt);
    hlAttributes->addWidget(m_editAtt);
    hlAttributes->addWidget(m_delAtt);

    m_listAtt=new QListWidget;
    m_listAtt->setSortingEnabled(true);
    vlAttributes->addWidget(m_listAtt);
    vlAttributes->addLayout(hlAttributes);

    gbAttributes->setLayout(vlAttributes);

    hlMembers->addWidget(gbMethods);
    hlMembers->addWidget(gbAttributes);

    //Comments
    m_author= new QLineEdit();
    m_date= new QDateEdit();
    m_comments= new QTextEdit();

    m_flComments=new QFormLayout();
    m_flComments->addRow("Author", m_author);
    m_flComments->addRow("Date of creation", m_date);
    m_flComments->addRow("External comments", m_comments);

    m_doComments=new QCheckBox("Activate comments");
    m_author->setEnabled(false);
    m_date->setEnabled(false);
    m_comments->setEnabled(false);

    vlComments->addWidget(m_doComments);
    vlComments->addLayout(m_flComments);
    gbComments->setLayout(vlComments);

    //Validate
    m_save=new QPushButton("Save");
    m_view=new QPushButton("View");

    hlValidate->addWidget(m_view);
    hlValidate->addWidget(m_save);

    //Main

    glMain->addWidget(gbGeneral, 0,0, 1,2);
    glMain->addWidget(gbOptions, 1, 0, 3,2);
    glMain->addLayout(hlMembers, 0, 2, 2, 2);
    glMain->addWidget(gbComments, 2, 2, 2, 2);
    glMain->addLayout(hlValidate, 4, 3);

    setLayout(glMain);

    connect(m_view, SIGNAL(clicked()), this, SLOT(viewCode()));
    connect(m_save, SIGNAL(clicked()), this, SLOT(saveCode()));
    connect(m_name, SIGNAL(textEdited(QString)), this, SLOT(setHeaderName(QString)));
    connect(m_constructor, SIGNAL(stateChanged(int)), this, SLOT(enableCopyC(int)));
    connect(m_destructor, SIGNAL(stateChanged(int)), this, SLOT(enableVirtualD(int)));
    connect(m_headerProt, SIGNAL(stateChanged(int)), this, SLOT(enableHeaderName(int)));
    connect(m_doComments, SIGNAL(stateChanged(int)), this, SLOT(enableComments(int)));

    connect(m_addMethod, SIGNAL(clicked()), this, SLOT(addMethod()));
    connect(m_delMethod, SIGNAL(clicked()), this, SLOT(delMethod()));

    connect(m_addAtt, SIGNAL(clicked()), this, SLOT(addAttribute()));
    connect(m_delAtt, SIGNAL(clicked()), this, SLOT(delAttribute()));


}

void ClassMaker_cpp::genCode(){
    headerCode="";
    sourceCode="";
    if(m_name->text()!=""){
        int nMethods=m_listMethod->count();
        int mRow=0;
        int nAttributes=m_listAtt->count();
        int aRow=0;
        QString scope="";

        //C++ source code
            sourceCode+="#include \""+m_name->text().toLower()+"\"\n\n";
            if(m_constructor->isChecked()){
                sourceCode+=m_name->text()+"::"+m_name->text()+"()";
                if(!m_inheritance->text().isEmpty()){
                    sourceCode+=" : "+m_inheritance->text()+"()";
                }
                sourceCode+="\n{\n\n}\n\n";

                if(m_copyC->isChecked()){
                    sourceCode+=m_name->text()+"::"+m_name->text()+"("+m_name->text()+" copy)\n";
                    sourceCode+="{\n\n}\n\n";
                }
            }
            if(m_destructor->isChecked()){
                sourceCode+=m_name->text()+"::~"+m_name->text()+"()\n";
                sourceCode+="{\n\n}\n\n";
            }


        //Comments section
        if(m_doComments->isChecked()){
            headerCode+= "/*\nCreator : " + m_author->text();
            headerCode+= "\nDate : " + m_date->text();
            headerCode+= "\n" + m_comments->toPlainText();
            headerCode+= "\n*/\n\n";
        }

        //header protection
        if(m_headerProt->isChecked()){
            headerCode+="#ifndef "+m_headerName->text();
            headerCode+="\n#define "+m_headerName->text()+"\n\n";
        }

        //main code
        headerCode+="Class "+m_name->text();
        if(!m_inheritance->text().isEmpty()){
            headerCode+=" : public "+ m_inheritance->text();
        }
        headerCode+="\n{\n\n";

        //public
        scope="public";
        headerCode+="public:\n\t";
        if(m_constructor->isChecked()){
            headerCode+=m_name->text() + "(); //Constructor\n\t";

            if(m_copyC->isChecked()){
                headerCode+=m_name->text() + "(const& " + m_name->text() + "copy); //Copy constuctor\n\t";
            }
        }

        if(m_destructor->isChecked()){
            if(m_virtualD->isChecked()){
                headerCode+="virtual ";
            }
            headerCode+="~"+m_name->text()+"(); //Destructor\n\t";
        }
        if(m_destructor->isChecked()||m_constructor->isChecked()){
            headerCode+="\n\t";
        }

        while(mRow<nMethods && m_listMethod->item(mRow)->text().startsWith(scope)){
            QString method=m_listMethod->item(mRow)->text();
            method.remove(0, 7);
            headerCode+=method + ";\n\t";
            mRow++;
        }


        //protected
        scope="protected";
        headerCode+="\nprotected:\n\t";
        while(mRow<nMethods && m_listMethod->item(mRow)->text().startsWith(scope)){
            QString method=m_listMethod->item(mRow)->text();
            method.remove(0, 10);
            headerCode+=method + ";\n\t";
            mRow++;
        }

        while(aRow<nAttributes &&m_listAtt->item(aRow)->text().startsWith(scope)){
            QString attribute=m_listAtt->item(aRow)->text();
            attribute.remove(0, 10);
            headerCode+=attribute + ";\n\t";
            aRow++;
        }

        //private
        scope="private";
        headerCode+="\nprivate:\n\t";
        while(mRow<nMethods && m_listMethod->item(mRow)->text().startsWith(scope)){
            QString method=m_listMethod->item(mRow)->text();
            method.remove(0, 8);
            headerCode+=method + ";\n\t";
            mRow++;
        }
        headerCode+="\n\t";

        while(aRow<nAttributes &&m_listAtt->item(aRow)->text().startsWith(scope)){
            QString attribute=m_listAtt->item(aRow)->text();
            attribute.remove(0, 8);
            headerCode+=attribute + ";\n\t";
            aRow++;
        }


        headerCode+="\n}\n";

        if(m_headerProt->isChecked()){
            headerCode+="\n#endif //"+m_headerName->text()+"\n";
        }

    }
}

void ClassMaker_cpp::viewCode(){
    genCode();
    if(sourceCode!="" || headerCode!=""){
        ClassViewer viewer(sourceCode, headerCode);
        viewer.exec();
    }
}

void ClassMaker_cpp::saveCode(){
    genCode();
    if(sourceCode!="" || headerCode!=""){
        QString folder=QFileDialog::getExistingDirectory(this);

        QFile cppFile(folder+"/"+m_name->text().toLower()+".cpp");
        if(!cppFile.open(QIODevice::WriteOnly| QIODevice::Text))
            return;
        QTextStream cppOut(&cppFile);
        cppOut<<sourceCode;

        QFile hFile(folder+"/"+m_name->text().toLower()+".h");
        if(!hFile.open((QIODevice::WriteOnly| QIODevice::Text)))
            return;
        QTextStream hOut(&hFile);
        hOut<<headerCode;

        QMessageBox::information(this, "", "Your files have been succesfully saved");
    }
}

void ClassMaker_cpp::setHeaderName(const QString & hName){
    if(!m_headerName->isModified()){
        m_headerName->setText(hName.toUpper()+"_H");
    }
}

void ClassMaker_cpp::enableCopyC(int value){
    if(value==Qt::Checked){
        m_copyC->setEnabled(true);
    }
    else{
        m_copyC->setEnabled(false);
    }
}

void ClassMaker_cpp::enableVirtualD(int value){
    if(value==Qt::Checked){
        m_virtualD->setEnabled(true);
    }
    else{
        m_virtualD->setEnabled(false);
    }
}

void ClassMaker_cpp::enableHeaderName(int value){
    if(value==Qt::Checked){
        m_headerName->setEnabled(true);
    }
    else{
        m_headerName->setEnabled(false);
    }
}

void ClassMaker_cpp::enableComments(int value){
    if(value==Qt::Checked){
        m_author->setEnabled(true);
        m_date->setEnabled(true);
        m_comments->setEnabled(true);
    }
    else{
        m_author->setEnabled(false);
        m_date->setEnabled(false);
        m_comments->setEnabled(false);
    }

}

void ClassMaker_cpp::addMethod(){
    MethodEditor window;
    int ret=window.exec();

    if(ret==QDialog::Accepted && !window.getFunction().isEmpty()){
        m_listMethod->addItem(window.getFunction());
        m_listMethod->sortItems(Qt::DescendingOrder);
    }

}

void ClassMaker_cpp::delMethod(){
    int ret=QMessageBox::warning(this, "Delete Method", "Do you want to remove the selected method ?", QMessageBox::Yes|QMessageBox::No);
    if(ret==QMessageBox::Yes)
        m_listMethod->takeItem(m_listMethod->currentRow());

}

void ClassMaker_cpp::addAttribute(){
    AttributeEditor window;
    int ret=window.exec();

    if(ret==QDialog::Accepted &&!window.getAttribute().isEmpty()){
        m_listAtt->addItem(window.getAttribute());
        m_listAtt->sortItems(Qt::DescendingOrder);
    }
}

void ClassMaker_cpp::delAttribute(){
    int ret=QMessageBox::warning(this, "Delete Attribute", "Do you want to remove the selected attribute ?", QMessageBox::Yes|QMessageBox::No);
    if(ret==QMessageBox::Yes)
        m_listAtt->takeItem(m_listAtt->currentRow());
}
