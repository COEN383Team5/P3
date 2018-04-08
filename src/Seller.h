#ifndef SELLER_H
#define SELLER_H

#define TIME_TO_SELL 60

#define HIGH_TIME_MAX 2
#define HIGH_TIME_LOW 1
#define MEDIUM_TIME_MAX 4
#define MEDIUM_TIME_MIN 2
#define LOW_TIME_MAX 7
#define LOW_TIME_MIN 4

#include <queue>

enum SellerTypes {HIGH, MEDIUM, LOW};

class Seller {
    int type, nextTicket, currentSaleTime, custInHour, numSold, sellerNum;
    int minutesSpent;
    std::queue<Customer> queue;
    std::vector<int> custThisTime;
    // The seller doesn't have to worry about deleting tickets when the program
    // is over
    Ticket **tickets;
    bool stillSelling;

    /* Spend part of a  minute selling a ticket
     * If no sale is in progress right now, the seller will sell to the next 
     * customer in the queue if there is one. If there isn't one, nothing 
     * happens. If a sale is currently in progress, it will spend a minute on 
     * the sale, and complete it if the appropriate number of minutes have been
     * spent on the sale.
     */
    void sellTicket(); 

    /* Attempts to sell a ticket
     * @retval whether or not the sale went through
     */
    bool finializeSale();

    /* Randomly selects custInHour number of times during a 60 minute period to
     * have customers enter the queue
     * Initializes custThisTime
     */
    void generateTimeCustomersCome();
public:

    Seller(int sellerType, int sellerNum, int firstSeatToSell, int custInHour, Ticket **tickets);

    /* adds customers to the queue and calls sellTicket()
     */
    void spendMinute();

}

#endif
