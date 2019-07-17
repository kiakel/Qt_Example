#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "clabel.h"
#include "cfiledialog.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    connect(ui->saveImageBtn,&QPushButton::clicked,ui->imageLabel,&CLabel::on_saveImageBtn_clicked);
    connect(ui->prevImageBtn, &QPushButton::clicked,ui->imageLabel, &CLabel::on_prevImageBtn_clicked);
    connect(ui->nextImageBtn,&QPushButton::clicked,ui->imageLabel,&CLabel::on_nextImageBtn_clicked);
    connect(ui->undoBtn,&QPushButton::clicked,ui->imageLabel,&CLabel::on_undoBtn_clicked);
    connect(ui->clearBtn,&QPushButton::clicked,ui->imageLabel,&CLabel::on_clearBtn_clicked);
    connect(ui->loadImageBtn, &QPushButton::clicked,this, &MainWidget::scannerImage);
    connect(ui->zoomInRdo,&QRadioButton::clicked,ui->imageLabel,&CLabel::slotZoomIn);
    ui->undoBtn->setShortcut(tr("ctrl+z"));
    ui->saveImageBtn->setShortcut(tr("ctrl+s"));
}

MainWidget::~MainWidget()
{
    delete ui; ui = nullptr;
}

void MainWidget::scannerImage()
{
    CFileDialog fileDialog;
    if ( fileDialog.exec() == CFileDialog::Accepted)
    {
         QStringList pathList =  fileDialog.selectedFiles();
         if (pathList.empty())
             return;

         ui->imageLabel->setImagePathList(pathList);
         QStringList pointSize = ui->lineEdit->text().split("*");
         ui->imageLabel->setPointSize(pointSize.at(0).toInt(),pointSize.at(1).toInt());
    }
}
