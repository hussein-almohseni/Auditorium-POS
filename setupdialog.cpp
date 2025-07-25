#include "setupdialog.h"
#include "ui_SetupDialog.h"
#include <QSpinBox>

int SetupDialog::rows() const {
    return ui->rowsSpinBox->value();
}

int SetupDialog::cols() const {
    return ui->colsSpinBox->value();
}

SetupDialog::SetupDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SetupDialog) {
    ui->setupUi(this);
}

SetupDialog::~SetupDialog() {
    delete ui;
}
