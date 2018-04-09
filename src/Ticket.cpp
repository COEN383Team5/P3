#include <cstdio>
#include "Log.h"
#include "Ticket.h"

std::mutex Ticket::mut;

Ticket::Ticket() {
    label = std::string(DEFAULT_LABEL);
    seat = 0;
    sold = false;
}

bool Ticket::sellTicket(const std::string &sellerLabel, const int &saleCount, const int &minutesSpent) {
    char s[5];
    std::unique_lock<std::mutex> lock(mut);
    if(sold) {
        return false;
    }
    sold = true;
    sprintf(s, "%s%02d", sellerLabel.c_str(), saleCount); 
    label = std::string(s);
    Log::logSale(seat, sellerLabel, minutesSpent);
    return true;
}

int Ticket::getSeat() {
    return seat;
}

std::string Ticket::getLabel() {
    return label;
}

bool Ticket::isSold() {
    return sold;
}
