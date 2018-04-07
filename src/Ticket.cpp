#include "Ticket.h"

Ticket::Ticket() {
    label = std::string(DEFAULT_LABEL);
    seat = lastIDUsed++;
    sold = false;
} 

bool Ticket::sellTicket(int sellerType, int saleCount) {
    // TODO
}
