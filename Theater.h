// Engine/Backend
#ifndef THEATER_H
#define THEATER_H

#include <vector>
#include <string>
#include "SeatType.h"
#include <QString>


enum class SeatStatus { Available, Sold};
const QString UNAVAILABLE_SEAT_STYLESHEET="background-color: #555; color: #999;";
const QString AVAILABLE_SEAT_STYLESHEET="background-color: green; color: white;";
const QString SELECTED_SEAT_STYLESHEET="background-color: #3498db; color: white;";
const QString PRIMARY_STYLESHEET="background-color: darkgray; color: black;";

class Theater {
public:
    // Constructor that takes the path to a price file for the purpose of initializing the seating prices
    explicit Theater(int rows, int cols,const std::string& price_file_path);

    // public methods
    void displayMenu() const;
    bool purchaseTicket(int row, int seat);
    double getTotalValueSold() const;
    int getTotalTicketsSold() const;
    std::vector<int> getSeatsAvailablePerRow() const;
    int getTotalSeatsAvailable() const;
    double getSeatPrice(int row,SeatType type) const;
    bool isSeatAvailable(int row, int seat) const;
    void resetSeats();
    void refundTicket(int row, int seat);
private:
    // private helper methods
    void loadPrices(const std::string& file_path);
    bool isSeatValid(int row, int seat) const;
    void loadStateFromFile();
    void saveStateToFile() const;

    // private member variables
    int rows_;
    int cols_;
    std::vector<std::vector<SeatStatus>> seats_;
    std::vector<double> regular_row_prices_;
    std::vector<double> kids_row_prices_;
    std::vector<double> disabled_row_prices_;
    std::vector<double> elderly_row_prices_;

    std::string m_stateFilePath;

};



#endif //THEATER_H