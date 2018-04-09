#include <iostream>
#include "Log.h"

std::mutex Log::stdoutMut;

void Log::printTickets(Ticket **tickets) {
    std::unique_lock<std::mutex> lock(stdoutMut);
    for(int j = 0; j< 10; j++) {
        for(int i = 0; i < 10; i++) {
            std::cout << (*tickets)[i+j].getLabel() << " ";
        }   
        std::cout << std::endl;
    }   
    std::cout << std::endl;
}

void Log::logEntry(const Customer &cust, const Seller &seller) {
    std::unique_lock<std::mutex> lock(stdoutMut);
    std::cout << "Minute " << seller.getMinutesSpent() << ": "
        << "A customer entered seller " << seller.getLabel() << "'s queue\n";
}

void Log::logExit(const Customer &cust, const Seller &seller) {
    std::unique_lock<std::mutex> lock(stdoutMut);
    std::cout << "Minute " << seller.getMinutesSpent() << ": "
        << "A customer was turned away by seller " << seller.getLabel() << "'s queue\n";

}

void Log::logSale(const int &seat, const std::string &sellerLabel, const int &minutesSpent) {
    std::unique_lock<std::mutex> lock(stdoutMut);
    std::cout << "Minute " << minutesSpent << ": "
        << "A customer was sold seat " << seat << " by seller " << sellerLabel << "\n";
}
