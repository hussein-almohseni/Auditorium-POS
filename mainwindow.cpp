/*
 * Created by Hussein Almohseni
 * Incomplete Auditorium point of sale (pos) app
 */
#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QMessageBox>

#include "seattypedialog.h"

MainWindow::MainWindow(int rowsGiven, int colsGiven,QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),my_theater(rowsGiven, colsGiven,"seats.txt") {
    ui->setupUi(this);
    const int rows = rowsGiven;
    const int cols = colsGiven;
    m_seatButtons.resize(rows);
    ui->infoDisplay->setHtml("<div style='text-align: center'>Select a seat</dev>");

    for (int i = 0; i < rows; ++i) {
        m_seatButtons[i].resize(cols);
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QPushButton *button = new QPushButton(this);
            button->setFixedSize(40, 20);
            button->setText(QString("%1-%2").arg(i+1).arg(j+1));

            m_seatButtons[i][j] = button;

            ui->seatsGridLayout->addWidget(button, i, j);

            // Connect the button's click signal to our single slot
            connect(button, &QPushButton::clicked, [=]() {
                onSeatClicked(i, j, button);
            });
        }
    }
    updateSeatColors();
    this->setStyleSheet(PRIMARY_STYLESHEET);
}
void MainWindow::onSeatClicked(int row, int col, QPushButton* button) {
    // Add a dialog to ask for the type of seat
    // if the button is already selected, remove it from the selectedSeats
    if (button->styleSheet() == SELECTED_SEAT_STYLESHEET){
        for (auto& seat : selectedSeats){
            if (seat.row == row && seat.col == col){
                selectedSeats.remove(selectedSeats.indexOf(seat));
            }
        }
    } else if (button->styleSheet()==UNAVAILABLE_SEAT_STYLESHEET) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Refund", QString("Seat %1-%2 is unavailable. Would you like to refund it?").arg(row+1).arg(col+1), QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            button->setStyleSheet(AVAILABLE_SEAT_STYLESHEET); // Why isn't this actually applying
            std::cout << "Refunding seat " << row + 1 << "-" << col + 1 << std::endl;
            my_theater.refundTicket(row+1,col+1);
            updateSeatColors();
        }
            return;

    } else {
        seatTypeDialog dialog;
        if (dialog.exec() == QDialog::Accepted){
            // add to selectedSeats
            Seat seat(row, col,dialog.getSelectedSeatType());
            selectedSeats.push_back(seat);
        } else {
            // if the user cancels the selection process by closing the popup
            return;
        }
    }
    // get seat price and availability
    double price;

    // format the information string
    QString message="<div style='text-align: center;'>";
    double total_cost=0;
    for (auto& seat : selectedSeats) {
        price = my_theater.getSeatPrice(seat.row+1, seat.type);
        total_cost += price;
        message.append(QString("Seat: %1-%2 | Price: $%3<"
                               "br>")
                          .arg(seat.row+1)
                          .arg(seat.col + 1)
                          .arg(price, 0, 'f', 2));
    }
    if (!selectedSeats.empty())
        message.append(QString("Total Cost: $%1").arg(total_cost));
    message.append("</div>");
    // Update the infoDisplay using HTML to center align the text
    ui->infoDisplay->setHtml(message);
    // auto scroll
    QTextCursor cursor = ui->infoDisplay->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->infoDisplay->setTextCursor(cursor);
    // update the seat colors
    updateSeatColors();
}
void MainWindow::on_purchaseButton_clicked() {
    if (selectedSeats.isEmpty()) {
        ui->infoDisplay->setHtml("<div style='text-align=center;'>Please select a seat first.<div>");
        return;
    }

    for (auto& seat : selectedSeats) {
        my_theater.purchaseTicket(seat.row+1, seat.col+1);
    }

    ui->infoDisplay->setHtml("<div style='text-align: center;'>Processed seats successfully</div>");


    // Reset seat selection
    selectedSeats.clear();

    // update the seat colors to reflect availability
    updateSeatColors();
}

void MainWindow::updateSeatColors() {
    for (int i=0; i<m_seatButtons.size(); ++i) {
        for (int j=0; j<m_seatButtons[i].size(); ++j) {
            QPushButton *button = m_seatButtons[i][j];
            bool isSelected = false;
            for (auto& seat : selectedSeats){
                if (seat.row==i && seat.col==j)
                    isSelected = true;
            }
            if (isSelected) {
                // Selected Seat
                button->setStyleSheet(SELECTED_SEAT_STYLESHEET); // Blue
            } else if (my_theater.isSeatAvailable(i+1, j+1)) {
                // Available Seat
                button->setStyleSheet(AVAILABLE_SEAT_STYLESHEET); // Reverts to default stylesheet
            } else {
                // unavailable seat
                button->setStyleSheet(UNAVAILABLE_SEAT_STYLESHEET);
            }
        }
    }
}

void MainWindow::on_resetButton_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Reset", "Are you sure you want to reset all seats? This cannot be undone.",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        my_theater.resetSeats(); // Call the reset logic
        updateSeatColors();      // Update the UI to reflect the changes
        ui->infoDisplay->setHtml("<div style='text-align: center;'>All seats have been reset.</div>");
        // make all buttons available
        for (auto& rowOfButtons : m_seatButtons) {
            for (auto* button : rowOfButtons) {
                button->setEnabled(true);
            }
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
