#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Theater.h"
#include <QVector>
#include "SeatType.h"

class QPushButton;
struct Seat {
    int row;
    int col;
    SeatType type;

    Seat(int r, int c, SeatType t) : row(r), col(c), type(t) {}

    bool operator==(const Seat& other) const {
        return row == other.row && col == other.col;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(int rows, int cols,QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    Ui::MainWindow *ui;
    Theater my_theater;
    // -1 means no seat is selected
    // int selectedRow = -1;
    // int selectedCol = -1;
    QVector<Seat> selectedSeats;
    QVector<QVector<QPushButton*>> m_seatButtons;
    void updateSeatColors();
    void printHello() const;
private slots:
    void onSeatClicked(int row, int col, QPushButton* button);
    void on_purchaseButton_clicked();
    void on_resetButton_clicked();
};


#endif //MAINWINDOW_H
