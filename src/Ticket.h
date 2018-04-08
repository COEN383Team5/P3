#ifndef TICKET_H
#define TICKET_H

#define DEFAULT_LABEL "----"
#define MAX_TICKET_SALES 100

#include <string>
#include <mustex>

class Ticket {
    static int lastIDUsed;
    static std::mutex mut;
    std::string label;
    int seat;
    volatile bool sold;

public:

    Ticket(); 

    /* Sells the ticket if it is still available
     * thread-safe
     * @param sellerType
     *      the type for the requesting seller, HIGH, MEDIUM, LOW
     * @param saleCount
     *      the sale that this would be for the salesman
     *      this determines the label
     * @retval whether or not the sale could be completed     
     */
    bool sellTicket(int sellerType, int sellerNum, int saleCount);
};

#endif 
