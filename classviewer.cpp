#include "classviewer.h"

ClassViewer::ClassViewer(QString code, QString header, QString language) : QDialog()
{
    if(language=="cpp"){
        //layout
        setFixedSize(500, 900);
        QVBoxLayout *vlMain=new QVBoxLayout();

        QTabWidget *tab=new QTabWidget;

        m_code=new QTextEdit;
        m_code->setReadOnly(true);
        m_code->setText(code);
        m_header=new QTextEdit;
        m_header->setText(header);
        m_header->setReadOnly(true);

        m_code->setFont(QFont("Source Code Pro", 10));
        m_header->setFont(QFont("Source Code Pro", 10));


        tab->addTab(m_header, "Header");
        tab->addTab(m_code, "C++ Code");

        m_save=new QPushButton("Save");

        vlMain->addWidget(tab);
        vlMain->addWidget(m_save);
        setLayout(vlMain);
    }
}


