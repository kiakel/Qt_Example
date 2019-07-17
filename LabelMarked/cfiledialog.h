#ifndef CFILEDIALOG_H
#define CFILEDIALOG_H

#include <QFileDialog>

class CFileDialog : public QFileDialog
{
    Q_OBJECT
public:
    CFileDialog(QWidget *parent = nullptr);
    ~CFileDialog() override;

public slots:
    void onChiose();
};

#endif // CFILEDIALOG_H
