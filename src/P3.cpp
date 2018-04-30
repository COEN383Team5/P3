#include <iostream>
#include <thread>
#include <mutex>
#include "Log.h"
#include "Ticket.h"
#include "Seller.h"
#include "Barrier.h"

#define HIGH_SELLERS 1
#define MEDIUM_SELLERS 3
#define LOW_SELLERS 6
#define NUM_SELLERS 10

Ticket *makeTickets() {
    Ticket *retval = new Ticket[MAX_TICKET_SALES];
    for(int i = 0; i < MAX_TICKET_SALES; i++) {
        retval[i] = Ticket(i+1);
    }
    return retval;
}

Seller *makeSellers(const int &custInHour, Ticket **tickets) {
    Seller *retval = new Seller[NUM_SELLERS];
    int i;
    for(i = 0; i < HIGH_SELLERS; i++) {
        retval[i] = Seller(HIGH, i, 0, custInHour, tickets);
    }
    for(; i < MEDIUM_SELLERS+HIGH_SELLERS; i++) {
        int medSellNum = (i+1)-HIGH_SELLERS;
        retval[i] = Seller(MEDIUM, medSellNum, 50, custInHour, tickets); 
    }
    for(; i < LOW_SELLERS+MEDIUM_SELLERS+HIGH_SELLERS; i++) {
        int lowSellNum = (i+1)-(MEDIUM_SELLERS+HIGH_SELLERS);
        retval[i] = Seller(LOW, lowSellNum, 99, custInHour, tickets);
    }
    return retval;
}

int parseArguments(const int &argc, char *argv[]) {
    int retval;
    if(argc != 2 || (retval = atoi(argv[1])) == 0) {
        std::cerr << "Improper args. Usage:\n\t" << argv[0] << " numCustInHour" 
            << "\nWhere numCustInHour is the number of customers that will enter"
            << " each seller's queue in 60 minutes.\n";
        exit(-1);
    }
    return retval;
}

void sellerThread(Seller *seller, Ticket **tickets, Barrier *barrier) {
    for(int i = 0; i < TIME_TO_SELL; i++) {
        if(seller->spendMinute()) {
            Log::printTickets(tickets);
        }   
        barrier->lockOrNotify();
    }
    seller->closeUpShop();
}

int main(int argc, char *argv[]) {
    int custInHour = parseArguments(argc, argv);
    Ticket *tickets = makeTickets();
    Seller *sellers = makeSellers(custInHour, &tickets);   
    Barrier barrier(NUM_SELLERS);
    std::thread sThreads[NUM_SELLERS];
    for(int i = 0; i < NUM_SELLERS; i++) {
        sThreads[i] = std::thread(sellerThread, &sellers[i], &tickets, &barrier);
    }
    for(int i = 0; i < NUM_SELLERS; i++) {
        sThreads[i].join();
    }
    delete[] tickets;
    delete[] sellers;
}
