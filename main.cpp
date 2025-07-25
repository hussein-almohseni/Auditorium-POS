#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include "mainwindow.h" // Include your new main window header
#include "setupdialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    try{
        QSettings settings("University Detroit Mercy", "Auditorium");
        int rows, cols;
        if (!settings.contains("theater/rows")) {
            SetupDialog dialog;
            if (dialog.exec() == QDialog::Accepted) {
                rows = dialog.rows();
                cols = dialog.cols();
                settings.setValue("theater/rows", rows);
                settings.setValue("theater/cols", cols);
            } else
                return 0;
        } else {
            rows = settings.value("theater/rows").toInt();
            cols = settings.value("theater/cols").toInt();
        }


        MainWindow w(rows, cols); // Create an instance of your main window
        w.show(); // Show the main window
        return QApplication::exec();
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(nullptr, "Fatal Error", e.what());
        return 1;
    }
}