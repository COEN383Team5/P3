#include <cstdlib>
#include <sstream>
#include <cstdio>
#include "Log.h"
#include "Seller.h"

void Seller::setNextTicket() {
    if(type == HIGH) {
        for(int i = nextTicket+1; i < MAX_TICKET_SALES; i++) {
            if(!(*tickets)[i].isSold()) {
                nextTicket = i;
                return;
            }
        }
        nextTicket = MAX_TICKET_SALES;
        return;
    } else if(type == MEDIUM) {
        int i = nextTicket+1;
        while(true) {
            if(i%10 == 0) {
                fprintf(stderr, "i=%d\n", i);
                if(i == 70) {
                    i = 40;
                } else if(i == 50) {
                    i = 70;
                } else if(i == 80) {
                    i = 30;
                } else if(i == 40) {
                    i = 90;
                } else if(i == 100) {
                    i = 20;
                } else if(i == 30) {
                    i = 10;
                } else if(i == 20) {
                    i = 0;
                } else if(i == 10) {
                    nextTicket = MAX_TICKET_SALES+1;
                    return;
                } 
                if(!(*tickets)[i].isSold()) {
                    nextTicket = i;
                    return;
                }
            }
            i++;
        }
    } else if(type == LOW) {
        for(int i = nextTicket-1; i >= 0; i--) {
            if(!(*tickets)[i].isSold()) {
                nextTicket = i;
                return;
            }
        }
        nextTicket = MAX_TICKET_SALES;
        return;
    }
}

bool Seller::sellTicket() {
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
            queue.pop();
            return true;
        }
    } 
    return false;
}

bool Seller::finializeSale() {
    while(!(*tickets)[nextTicket].sellTicket(label, numSold, minutesSpent)) {
        numSold++;
        setNextTicket();
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
        minutesWithCusts[i] = rand()%TIME_TO_SELL;
    }
    for(int i = 0; i < custInHour; i++) {
        custThisTime[minutesWithCusts[i]]++;
    }
}   

Seller::Seller() {
    type = LOW;
    sellerNum = -1;
    label = "";
    nextTicket = MAX_TICKET_SALES;
    custInHour = 0;
    tickets = NULL;
    currentSaleTime = 0;
    numSold = 0;
    stillSelling = true;
    minutesSpent = 0;
}

Seller::Seller(int type, int sellerNum, int firstSeatToSell, int custInHour, Ticket **tickets) {
    this->type = type;
    this->sellerNum = sellerNum;
    std::stringstream label;
    if(type == HIGH) {
        label << "H";
    } else if(type == MEDIUM) {
        label << "M";
    } else {
        label << "L";
    }
    label << sellerNum;
    this->label = std::string(label.str());
    nextTicket = firstSeatToSell;
    this->custInHour = custInHour;
    this->tickets = tickets;
    currentSaleTime = 0;
    numSold = 0;
    stillSelling = true;
    minutesSpent = 0;
    generateTimeCustomersCome();
}

Seller::Seller(const Seller &other) {
    if(this == &other) {
        return;   
    }
    *this = other;
}

Seller &Seller::operator=(const Seller &other) {
    if(this == &other) {
        return *this;
    }
    type = other.type;
    nextTicket = other.nextTicket;
    currentSaleTime = other.currentSaleTime;
    custInHour = other.custInHour;
    numSold = other.numSold;
    sellerNum = other.sellerNum;
    minutesSpent = other.minutesSpent;
    queue = std::queue<Customer>(other.queue);
    custThisTime = std::vector<int>(other.custThisTime);
    label = std::string(other.label);
    tickets = other.tickets;
    stillSelling = other.stillSelling;
    return *this;
}

Seller::~Seller() {
    // tickets is clean up by whoever provided it to this function
}

bool Seller::spendMinute() {
    bool sale = false;
    if(stillSelling) {
        for(int i = 0; i < custThisTime[minutesSpent]; i++) {
            Customer cust = Customer();
            queue.push(cust);
            Log::logEntry(cust, *this);
        }
        if(queue.size() > 0) {
            sale = sellTicket();
        }
    } else {
        while(!queue.empty()) {
            Customer cust = queue.front();
            Log::logExit(cust, *this); 
            queue.pop();
        }
    }
    minutesSpent++;
    if(minutesSpent == TIME_TO_SELL) {
        stillSelling = false;
    }
    return sale;
}

std::string Seller::getLabel() const{
    return label;
}

int Seller::getMinutesSpent() const {
    return minutesSpent;
}
