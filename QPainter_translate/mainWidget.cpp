#include "mainWidget.h"
#include "CWidget.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

mainWidget::mainWidget(QWidget *parent)
    : QWidget (parent)
{
    this->initialize();
}

mainWidget::~mainWidget()
{
    release();
}


QSize mainWidget::sizeHint() const
{
    return QSize(300,400);
}

void mainWidget::paintEvent(QPaintEvent *evt)
{
    qDebug()<<"x:"<<this->x()<<",y:"<<this->y()<<endl;// 屏幕系统坐标
    QPainter painter(this);
    QFontMetrics fontRect(painter.font());

    painter.drawText(evt->rect().x(),evt->rect().y()+fontRect.height(), "mainWidget");
}


void mainWidget::initialize()
{
    m_label = new CWidget();
    m_label->setStyleSheet("background-color:white;padding-left:0;padding-right:0;padding-top:0;");
    m_lay = new QVBoxLayout();
    m_lay->setSpacing(0);
    m_lay->addWidget(m_label);
    this->setLayout(m_lay);
    m_label->setMinimumSize(100,100);
    m_label->installEventFilter(this);
}


void mainWidget::release()
{
    delete m_label; m_label = nullptr;
    delete m_lay; m_lay = nullptr;

}

