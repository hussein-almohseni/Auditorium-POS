//
// Created by hualm on 7/22/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_seatTypeDialog.h" resolved

#include "seattypedialog.h"
#include "ui_seatTypeDialog.h"


seatTypeDialog::seatTypeDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::seatTypeDialog) {
    ui->setupUi(this);
}

SeatType seatTypeDialog::getSelectedSeatType() const{
    SeatType selected_type;
    if (ui->rdDisabled->isChecked())
        selected_type = SeatType::DISABLED;
    else if (ui->rdKids->isChecked())
        selected_type = SeatType::KIDS;
    else if (ui->rdElderly->isChecked())
        selected_type = SeatType::ELDERLY;
    else
        selected_type = SeatType::REGULAR;
    return selected_type;
}

seatTypeDialog::~seatTypeDialog() {
    delete ui;
}
