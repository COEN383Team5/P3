#include <cstdio>
#include "Ticket.h"

int Ticket::lastIDUsed;
std::mutex Ticket::mut;

Ticket::Ticket() {
    label = std::string(DEFAULT_LABEL);
    seat = lastIDUsed++;
    sold = false;
} 

bool Ticket::sellTicket(int sellerType, int sellerNum, int saleCount) {
    if(sold) {
        return false;
    }
    char s[5];
    std::unique_lock<std::mutex> lock(mut);
    sold = true;
    if(sellerType == HIGH) {
        sprintf(s, "H%d%02d", sellerNum, saleCount); 
        label = std::string(s);
    } else if(sellerType == MEDIUM) {
        sprintf(s, "M%d%02d", sellerNum, saleCount); 
    } else {
        sprintf(s, "L%d%02d", sellerNum, saleCount); 
    }
    label = std::string(s);

}
