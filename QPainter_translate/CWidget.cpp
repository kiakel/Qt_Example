#include "CWidget.h"
#include <QString>
#include <QStyleOption>
#include <QDebug>
#include <QPainter>

CWidget::CWidget(QWidget *parent)
	: QWidget(parent)
{
	
}

CWidget::~CWidget()
{
}


void CWidget::paintEvent(QPaintEvent * evt)
{
	Q_UNUSED(evt);

    QPainter painter(this);
    // 用于setStyleSheet
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    // 打印文字
    QString printText("1234");
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);
    painter.setPen(QPen(QBrush(Qt::GlobalColor::red),0.25)); // 设置画笔的颜色和画出来的线条宽度
    painter.setBrush(QBrush(Qt::GlobalColor::yellow, Qt::BrushStyle::Dense4Pattern)); // 设置画刷，绘制区域图形
    painter.drawRect(this->x()+50,this->y(),60,60); // 一个黄色正方形

    QFont font = painter.font();
    QFontMetrics metrics(font);
    QRect fontRect = metrics.boundingRect(printText); // 当前字体下，输入文本的像素
    painter.drawText(0,fontRect.height(),printText); // this->x()输出的不是0
    painter.drawText(this->rect().right()-fontRect.width(),this->rect().bottom(),"1234");

    painter.save(); // 保存原来坐标系状态
    painter.translate(0+this->width()/2,0+this->height()/2); // 将窗体中心位置作为新的坐标原点
    painter.scale(3, 3); // 纵横坐标都放大3倍,放到循环里面会一直放大，painter.scale(-3, -3)并没有恢复初始状态。

    // 打造一个米字形，translate、scale、rotate、shear方法对坐标系的修改具有持久性，每次变化都是在变化后的基础上再次变化
    for(int i=0;i<8;++i)
    {
        painter.rotate(45); // 每次在原来的基础上再旋转45度
        painter.shear(0, 1); // 纵坐标扭曲系数为1
        painter.drawText(0,0,printText);
        painter.drawLine(0,0,50,50);

        painter.shear(0, -1); // 恢复扭曲前的状态

    }
    painter.restore(); // 恢复save时的状态
    painter.drawText(180,this->y(),"recover");
}

