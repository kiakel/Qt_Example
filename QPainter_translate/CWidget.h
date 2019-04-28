#pragma once

#include <QLineEdit>

class CWidget : public QWidget
{
	Q_OBJECT

public:
    CWidget(QWidget *parent=nullptr);
    CWidget(const QString& text, QWidget* parent = nullptr);
    ~CWidget() override;

protected:
	void paintEvent(QPaintEvent *) override;

};
