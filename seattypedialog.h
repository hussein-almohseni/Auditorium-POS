//
// Created by hualm on 7/22/2025.
//

#ifndef SEATTYPEDIALOG_H
#define SEATTYPEDIALOG_H

#include <QDialog>

#include "mainwindow.h"
#include "SeatType.h"


QT_BEGIN_NAMESPACE
namespace Ui { class seatTypeDialog; }
QT_END_NAMESPACE

class seatTypeDialog : public QDialog {
Q_OBJECT

public:
    explicit seatTypeDialog(QWidget *parent = nullptr);
    ~seatTypeDialog() override;
    SeatType getSelectedSeatType() const;

private:
    Ui::seatTypeDialog *ui;
};


#endif //SEATTYPEDIALOG_H
