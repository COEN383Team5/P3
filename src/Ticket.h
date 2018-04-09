#ifndef TICKET_H
#define TICKET_H

#define DEFAULT_LABEL "----"
#define MAX_TICKET_SALES 100

#include <string>
#include <mutex>

class Ticket {
    static std::mutex mut;
    std::string label;
    int seat;
    volatile bool sold;

public:

    Ticket(); 
    Ticket(const int &seat);
    Ticket(const Ticket &other);
    Ticket &operator=(const Ticket &other);
    ~Ticket();

    /* Sells the ticket if it is still available
     * thread-safe
     * @param sellerType
     *      the type for the requesting seller, HIGH, MEDIUM, LOW
     * @param saleCount
     *      the sale that this would be for the salesman
     *      this determines the label
     * @retval whether or not the sale could be completed     
     */
    bool sellTicket(const std::string &sellerLabel, const int &saleCount, const int &minutesSpent);

    /* returns seat
     */
    int getSeat();

    /* returns label
     */
    std::string getLabel();

    /* returns sold
     */
    bool isSold();
};

#endif 
