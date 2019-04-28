#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
class QVBoxLayout;
class QPushButton;
class QLabel;
class QGridLayout;
class QSlider;
class CWidget;

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget() override;

protected:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent* evt) override;
    void initialize(); // 分配资源
    void release(); // 释放内存



private:
    CWidget* m_label;
    QVBoxLayout* m_lay;
};

#endif // MAINWIDGET_H
