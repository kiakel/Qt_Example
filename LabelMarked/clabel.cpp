#include "clabel.h"
#include "cfiledialog.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QWheelEvent>
#include <QTimer>

CLabel::CLabel(QWidget* parent)
    : QLabel (parent)
{
    // setWindowFlags(Qt::FramelessWindowHint);//无边框
     //setAttribute(Qt::WA_TranslucentBackground);//背景透明
    this->setMouseTracking(true);
}

void CLabel::setImagePathList(QStringList pathList)
{
    m_imagePathList = pathList;
    if (m_imagePathList.empty())
        return;

    m_curImageIndex = 0;
    m_markedPointVec.clear();
    m_isDraw =false;
    this->setPixmap(QPixmap::fromImage(QImage(m_imagePathList.at(m_curImageIndex))));
}

void CLabel::setPointSize(int width, int height)
{
    m_markedWidht = width;
    m_markedHeight = height;
}

void CLabel::on_prevImageBtn_clicked()
{
    if (m_curImageIndex>0)
    {
        qDebug()<<__FUNCTION__;
        m_markedPointVec.clear();
        m_isDraw = false;
        qDebug()<<m_imagePathList.at(--m_curImageIndex);
        this->setPixmap(QPixmap::fromImage(QImage(m_imagePathList.at(m_curImageIndex))));
        update();
    }
}

void CLabel::on_nextImageBtn_clicked()
{

    if (m_curImageIndex<m_imagePathList.size()-1)
    {
        qDebug()<<__FUNCTION__;
        m_markedPointVec.clear();
        qDebug()<<m_imagePathList.at(++m_curImageIndex);
        m_isDraw =false;
        this->setPixmap(QPixmap::fromImage(QImage(m_imagePathList.at(m_curImageIndex))));
        update();
    }
}

void CLabel::on_undoBtn_clicked()
{
    qDebug()<<__FUNCTION__;
    m_markedPointVec.takeLast();
    update();
}

void CLabel::on_clearBtn_clicked()
{
    qDebug()<<__FUNCTION__;
    m_markedPointVec.clear();
    m_isDraw = false;
    update();
}

void CLabel::on_saveImageBtn_clicked()
{
    qDebug()<<__FUNCTION__;
    QString filePath = m_imagePathList.at(m_curImageIndex);
    int lastIndex = filePath.lastIndexOf('/');
    QString outputName =  filePath.mid(lastIndex+1,filePath.lastIndexOf('.')-lastIndex-1);
    QFile fileHandler(QApplication::applicationDirPath()+"/outputImage/"+outputName+".txt");
    fileHandler.open(QIODevice::WriteOnly|QIODevice::Truncate);
    if (!fileHandler.isOpen())
    {
        qDebug()<<"open filed failed:"<<fileHandler.fileName();
        return;
    }
    int count = 0;
    for (auto var:m_markedPointVec)
    {
        if (++count%m_markedHeight==0 )
        {
            fileHandler.write(QString("(%1,%2)").arg(var.x()).arg(var.y()).toStdString().c_str());
            fileHandler.write(QLatin1String("\r\n").data());
        }
        else {
            fileHandler.write(QString("(%1,%2),").arg(var.x()).arg(var.y()).toStdString().c_str());
        }
    }

    fileHandler.waitForBytesWritten(1000);
    fileHandler.close();

    QPixmap savePix = QPixmap::grabWidget ( this, this->rect() );
    savePix.save(QApplication::applicationDirPath()+"/outputImage/"+outputName+".png");
    // 保存QPainter的第二种方式
    //void QWidget::render(QPaintDevice *target, const QPoint &targetOffset = QPoint(), const QRegion &sourceRegion = QRegion(), QWidget::RenderFlags renderFlags = ...)
    //void QWidget::render(QPainter *painter, const QPoint &targetOffset = QPoint(), const QRegion &sourceRegion = QRegion(), QWidget::RenderFlags renderFlags = ...)
    /*
     * QPixmap savePixmap(this->rect());
     * this->render(&savePixmap);
     * savePix.save(QApplication::applicationDirPath()+"/outputImage/"+outputName+".png");
     */
}

void CLabel::slotZoomIn(bool checked)
{
    m_isZoomIn = checked;
    update();
}

void CLabel::paintEvent(QPaintEvent *event)
{
QLabel::paintEvent(event); // 调用父类paintEvent，绘制pixmap
    if(m_isDraw)
    {
        drawCircle(5,5);
        if (m_markedPointVec.size()>=2)
        {
            drawLine(1);
        }
    }


    if (this->pixmap() && m_isZoomIn)
    {
        QPoint cursorPos = mapFromGlobal(QCursor::pos());

        if (cursorPos.x()<0 || cursorPos.y()<0 || cursorPos.x() > this->width() || cursorPos.y()>this->height())
            return;

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);//设置反走样

        int x = cursorPos.x();
        int y = cursorPos.y();

        int radiusZoomIn = 60; // 放大半径
        qreal zoomIn = 1.2; // 放大倍数
        QTransform tr;
        tr.translate(x - zoomIn*radiusZoomIn, y - zoomIn*radiusZoomIn);
        tr.scale(zoomIn, zoomIn);
        QPixmap* _pixmap = const_cast<QPixmap*>(this->pixmap());
        QPixmap pix = _pixmap->copy(x - radiusZoomIn, y - radiusZoomIn, radiusZoomIn*2, radiusZoomIn*2);//截取以鼠标位置为中心的矩形
        QBrush brush(pix);//设置画刷
        brush.setTransform(tr);//画刷的矩阵转化会和painter叠加混合在一起，这个要也别注意
        painter.setBrush(brush);
        painter.drawEllipse(QRectF(tr.dx(), tr.dy(), pix.width()*zoomIn, pix.width()*zoomIn));//画出我们想要的放大部分
    }
}

void CLabel::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    update();
}

void CLabel::mouseReleaseEvent(QMouseEvent *event)
{

    if (m_imagePathList.empty())
        return;
qDebug()<<__FUNCTION__;
        m_drawPoint.setX(event->x());
        m_drawPoint.setY(event->y());
        m_markedPointVec.append(m_drawPoint);
        m_isDraw = true;
        qDebug()<<"drawpoint:"<<m_drawPoint;
        update();

}

void CLabel::drawCircle(int radius, int thickness)
{
    //const_cast<QPixmap*>(this->pixmap())
    painter.begin(this);
    painter.setPen(QPen(Qt::red, thickness, Qt::SolidLine, Qt::RoundCap));

    for (auto tmpPoint : m_markedPointVec)
    {
        painter.drawEllipse(tmpPoint.x()-radius,tmpPoint.y()-radius,radius*2,radius*2);
    }
    painter.end();
}

void CLabel::drawLine(int lineType)
{
    painter.begin(this);
    painter.setPen(QPen(Qt::red, lineType, Qt::SolidLine, Qt::RoundCap));
    for (int pointIndex=1; pointIndex<m_markedPointVec.size();++pointIndex)
    {
        QPoint curPoint = m_markedPointVec.at(pointIndex);
        QPoint prevPoint = m_markedPointVec.at(pointIndex-1);
        painter.drawLine(prevPoint.x(),prevPoint.y(),curPoint.x(),curPoint.y());
    }
    painter.end();
}
