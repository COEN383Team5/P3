#include <cstdlib>
#include "Seller.h"

Seller::Seller(int type, int firstSeatToSell, int custInHour) {
    this->type = type;
    nextTicket = firstSeatToSell;
    this->custInHour = custInHour;
    currentSaleTime = 0;
    numSold = 0;
}

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
    if(currentSaleTime > highSaleTime || (currentSaleTime > lowSaleTime && rand()%2 == 0)) {
        bool sold = finializeSale();
    } 
}

void Seller::finializeSale() {
    
}

void Seller::spendMinute() {
    if(type == HIGH) {

    } else if(type == MEDIUM) {

    } else {
        
    }
}
