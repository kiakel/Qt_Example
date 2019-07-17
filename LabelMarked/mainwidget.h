#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMap>
#include <QVector>
#include <QPoint>

class CLabel;
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;

protected slots:
    void scannerImage();

private:
    QVector<QPoint> m_markedPointVec = {};
    QStringList m_imagePathList = {}; //!< 需要标注的图片
    CLabel* m_imageLabel;
    Ui::MainWidget *ui;

};

#endif // MAINWIDGET_H
