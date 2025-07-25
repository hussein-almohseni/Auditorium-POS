//
// Created by hualm on 7/20/2025.
//

#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class SetupDialog; }
QT_END_NAMESPACE

class SetupDialog : public QDialog {
Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = nullptr);
    ~SetupDialog() override;
    int rows() const;
    int cols() const;

private:
    Ui::SetupDialog *ui;
};


#endif //SETUPDIALOG_H
