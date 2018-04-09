#ifndef LOG_H
#define LOG_H

#include <mutex>
#include "Ticket.h"
#include "Customer.h"
#include "Seller.h"

class Log {
    static std::mutex stdoutMut;

public:

    static void printTickets(Ticket **tickets);

    static void logEntry(const Customer &cust, const Seller &seller);

    static void logExit(const Customer &cust, const Seller &seller);

    static void logSale(const int &seat, const std::string &sellerLabel, const int &minutesSpent);
};

#endif
