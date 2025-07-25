#include "Theater.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#include "mainwindow.h"


// Constructor to initialize the Theater object
Theater::Theater(int rows, int cols,const std::string &price_file_path) : rows_(rows), cols_(cols), m_stateFilePath("auditorium_state.dat") {
    // Initialize the seats to be available
    seats_.resize(rows_, std::vector<SeatStatus>(cols_, SeatStatus::Available));
    loadStateFromFile();
    // Load the pricing information from the file
    loadPrices(price_file_path);
}

void Theater::displayMenu() const {
}

bool Theater::purchaseTicket(int row, int seat) {
    // check if the seat number is within boundaries
    if (!isSeatValid(row, seat))
        return false;

    // check if seat is sold
    if (seats_[row-1][seat-1] == SeatStatus::Sold)
        return false;

    // mark the seat as sold
    seats_[row-1][seat-1] = SeatStatus::Sold;
    saveStateToFile();
    return true; // Indicate purchasing seats requested
}

// Calculates and displays the total value of all sold tickets
double Theater::getTotalValueSold() const {
    double total_value = 0.0;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (seats_[i][j] == SeatStatus::Sold) {

            }
        }
    }
    return total_value;
}

// Counts and displays the total number of sold tickets
int Theater::getTotalTicketsSold() const {
    int sold_count = 0;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (seats_[i][j] == SeatStatus::Sold) {
                sold_count++;
            }
        }
    }
    return sold_count;
}

// returns a vector of how many seats are still available in each row
std::vector<int> Theater::getSeatsAvailablePerRow() const {
    std::vector<int> row_seats_available;
    for (int i = 0; i < rows_; ++i) {
        int available_count = 0;
        for (int j = 0; j < cols_; ++j) {
            if (seats_[i][j] == SeatStatus::Available) {
                available_count++;
            }
        }
        row_seats_available.push_back(available_count);
        std::cout << "Row " << i + 1 << ": " << available_count << " seats available." << std::endl;
    }
    return row_seats_available;
}

// returns the total number of available seats in the entire theater
int Theater::getTotalSeatsAvailable() const {
    int available_count = 0;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (seats_[i][j] == SeatStatus::Available) {
                available_count++;
            }
        }
    }
    return available_count;
}

void Theater::loadPrices(const std::string &file_path) {
    std::ifstream price_file(file_path);
    if (!price_file) {
        throw std::runtime_error("Error: Could not open price file: " + file_path);
    }

    double price;
    int helper_counter=0;
    while (price_file >> price) {
        helper_counter++;
        if (helper_counter==1)
            regular_row_prices_.push_back(price);
        else if (helper_counter==2)
            kids_row_prices_.push_back(price);
        else if (helper_counter==3)
            elderly_row_prices_.push_back(price);
        else{
            disabled_row_prices_.push_back(price);
            helper_counter=0;
        }
    }

    // Ensure we have a price for every row
    if (regular_row_prices_.size() < rows_) {
        std::cerr << "Error: Price file does not contain the correct number of row prices."<< std::endl;
        exit(1);
    }
}

bool Theater::isSeatValid(int row, int seat) const {
    return row>=1 && row<=rows_ && seat>=1 && seat<=cols_;
}

bool Theater::isSeatAvailable(int row, int seat) const {
    if (!isSeatValid(row, seat)) {
        return false;
    }
    return seats_[row-1][seat-1] == SeatStatus::Available;
}

double Theater::getSeatPrice(int row, SeatType type) const {
   if (type == SeatType::DISABLED)
       return disabled_row_prices_[row-1];
   if (type == SeatType::KIDS)
       return kids_row_prices_[row-1];
    if (type == SeatType::ELDERLY)
       return elderly_row_prices_[row-1];
    // Default value
    return regular_row_prices_[row-1];
}

void Theater::loadStateFromFile() {
    std::ifstream stateFile(m_stateFilePath);
    if (!stateFile) {
        // File doesn't exist, so do nothing
        return;
    }

    int status;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (stateFile >> status) {
                seats_[i][j] = (status == 1) ? SeatStatus::Sold : SeatStatus::Available;
            }
        }
    }
}

void Theater::saveStateToFile() const {
    std::ofstream stateFile(m_stateFilePath);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            stateFile << (seats_[i][j] == SeatStatus::Sold ? 1 : 0) << " ";
        }
        stateFile << "\n";
    }
}

void Theater::refundTicket(int row, int seat)
{
    seats_[row-1][seat-1] = SeatStatus::Available;
}


void Theater::resetSeats() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            seats_[i][j] = SeatStatus::Available;
        }
    }
    saveStateToFile();
}