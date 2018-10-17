/***********************************************************************
 * Header:
 *    Transaction
 * Summary:
 *    This class contains the implementation of transactions.
 * Authors:
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 ************************************************************************/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "dollars.h"       // for DOLLARS defined in StockTransaction
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT

class Transaction
{
  public:
   Transaction(int in_shareCount = 1, Dollars in_sharePrice = 1.0,
               Dollars in_soldPrice = 0.0);

   // Gets the count of remaining shares bought in this transaction;
   // this can't be added to, but shares can be sold
   int getShareCount() const { return m_shareCount; }

   // Get share price (share price can't be changed once set at creation time)
   // only read
   Dollars getSharePrice() const { return m_buyPrice; }

   // Get sold price (sold price can't be changed once set)
   // only read
   Dollars getSoldPrice() const { return m_soldPrice; }

   // Gets the profit for this transaction
   Dollars getProfit() const;

   // Sells a subset of the shares, reducing the share count by the
   // amount sold; returns the number of shares sold - in case
   // a caller tries to sell more shares than available
   Transaction sellShares(int in_sellCount, Dollars in_salePrice);

   // Displays the transaction
   void display(std::ostream & out) const;

  private:
   int m_shareCount;       // number of shares
   bool m_sold;            // returns true of shares have been sold
   Dollars m_buyPrice;     // price shares were purchased at
   Dollars m_soldPrice;    // price shares were sold at
};

std::ostream & operator << (std::ostream & out, const Transaction & rhs);

#endif // !TRANSACTION_H
