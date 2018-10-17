/***********************************************************************
 * Header:
 *    Portfolio
 * Summary:
 *    This class contains the data about a customers portfolio.
 * Authors:
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 ************************************************************************/
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "queue.h"         // for QUEUE
#include "transaction.h"   // for TRANSACTIONS
#include "dollars.h"       // for DOLLARS defined in StockTransaction
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT

class Portfolio
{
  public:
   Portfolio();
   ~Portfolio();
   void buy(int number, Dollars price);
   void sell(int number, Dollars price);
   void display(std::ostream & out) const;

  private:
   Queue<Transaction> m_holdings;
   Queue<Transaction> m_saleHistory;
   Dollars m_proceeds;
};

std::ostream & operator << (std::ostream & out, const Portfolio & rhs);
#endif
