#include "cfiledialog.h"
#include <QListView>
#include <QTreeView>
#include <QDialogButtonBox>
#include <QDebug>
#include <QApplication>
CFileDialog::CFileDialog(QWidget *parent)
    : QFileDialog(parent)
{
    this->setOption(QFileDialog::DontUseNativeDialog,true);

    //支持多选
    QListView *pListView = this->findChild<QListView*>("listView");
    if (pListView)
        pListView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QTreeView *pTreeView = this->findChild<QTreeView*>();

    if (pTreeView)
        pTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    this->setDirectory(QApplication::applicationDirPath()+"/inputImage");
    this->setNameFilter(tr("Image files (*.png *.jpeg *.jpg,*.bmp)"));
    // 选中文件夹时，open按钮不打开文件夹，直接退出dialog
   // QDialogButtonBox *pButton = this->findChild<QDialogButtonBox *>("buttonBox");
   // disconnect(pButton, SIGNAL(accepted()), this, SLOT(accept()));//使链接失效
   // connect(pButton, SIGNAL(accepted()), this, SLOT(onChiose()));//改成自己的槽
}

CFileDialog::~CFileDialog()
{

}

// 响应open按钮
void CFileDialog::onChiose()
{
    QDialog::accept();
}
