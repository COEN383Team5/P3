#include <cstdlib>
#include "Seller.h"

void Seller::sellTicket() {
    int lowSaleTime, highSaleTime;
    currentSaleTime++;
    if(type == HIGH) {
        lowSaleTime = HIGH_TIME_MIN;
        highSaleTime = HIGH_TIME_MAX;
    } else if(type == MEDIUM) {
        lowSaleTime = MEDIUM_TIME_MIN;
        highSaleTime = MEDIUM_TIME_MAX;
    } else {
        lowSaleTime = LOW_TIME_MIN;
        highSaleTime = LOW_TIME_MAX;
    }
    if(currentSaleTime == highSaleTime || (currentSaleTime >= lowSaleTime && rand()%2 == 0)) {
        if(finializeSale() == false) {
            stillSelling = false;
        } else {
            //TODO log customer being sold to
            queue.pop();

        }
    } 
}

bool Seller::finializeSale() {
    while(!tickets[nextTicket]->sellTicket(sellerType, sellerNum, saleCount)) {
        nextTicket++;
        if(nextTicket >= MAX_TICKET_SALES) {
            return false;
        }
    }
    return true;
}

void Seller::generateTimeCustomersCome() {
    custThisTime = std::vector<int>(TIME_TO_SELL);
    for(int i = 0; i < TIME_TO_SELL; i++) {
        custThisTime[i] = 0;
    }
    int minutesWithCusts[custInHour]; 
    for(int i = 0; i < custInHour; i++) {
        minuteWithCusts[i] = rand()%TIME_TO_SELL;
    }
    for(int i = 0; i < custInHour; i++) {
        custThisTime[minuteWithCusts[i]]++;
    }
}   

Seller::Seller(int type, int sellerNum, int firstSeatToSell, int custInHour, Ticket **tickets) {
    this->type = type;
    this->sellerNum = sellerNum;
    nextTicket = firstSeatToSell;
    this->custInHour = custInHour;
    this->tickets = tickets;
    currentSaleTime = 0;
    numSold = 0;
    stillSelling = true;
    minutesSpend = 0;
    generateTimeCustomersCome();
}

void Seller::spendMinute() {
    if(stillSelling) {
        for(int i = 0; i < custThisTime[minutesSpent]; i++) {
            Customer cust = Customer();
            queue.push(cust);
        // TODO log customer entering queue
        }
        sellTicket();
    } else {
        while(!queue.empty()) {
            queue.pop();
            //TODO log customers being turned away
        }
    }
    minutesSpent++;
    if(minutesSpent == TIME_TO_SELL) {
        stillSelling = false;
    }
}
