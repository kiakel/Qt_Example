#ifndef CLABEL_H
#define CLABEL_H
#include <QLabel>
#include <QPainter>
class QTimer;

class CLabel:public QLabel
{
    Q_OBJECT
public:
    explicit CLabel(QWidget* parent = nullptr);
    void setImagePathList(QStringList pathList);
    void setPointSize(int width, int height);

public slots:
        void on_prevImageBtn_clicked();
        void on_nextImageBtn_clicked();
        void on_undoBtn_clicked();
        void on_clearBtn_clicked();
        void on_saveImageBtn_clicked();
        void slotZoomIn(bool checked);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void drawCircle(int radius, int thickness);
    void drawLine(int lineType);

private:
    QVector<QPoint> m_markedPointVec = {};
    QStringList m_imagePathList = {}; //!< 需要标注的图片
    QPainter painter;
    QTimer* m_pUpdateTimer;
    QPoint m_drawPoint = {-1,-1};
    int m_markedWidht = {0};
    int m_markedHeight = {0};
    int m_curImageIndex={0}; //!< 当前处理m_imagePathList中的图片索引
    bool m_isDraw = {false};
    bool m_isZoomIn = {false};
};

#endif // CLABEL_H
