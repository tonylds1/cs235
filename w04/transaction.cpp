/***********************************************************************
 * Program:
 *    Transaction
 * Summary:
 *    This class contains the implementation of transactions.
 * Authors:
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes
 ************************************************************************/
#include "transaction.h"   // for the class definition
#include <cassert>         // for ASSERT
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT
using namespace std;

/***********************************************************************
 * TRANSACTION :: CONSTRUCTOR
 * "Buys" a number of shares at a given price by creating a new Transaction
 * to represent the purchase
 ************************************************************************/
Transaction :: Transaction(int in_shareCount, Dollars in_sharePrice,
                           Dollars in_soldPrice)
      : m_shareCount(in_shareCount), m_buyPrice(in_sharePrice),
        m_soldPrice(in_soldPrice), m_sold(false)
{
   if (in_soldPrice > 0)
      m_sold = true;
}

/***********************************************************************
 * TRANSACTION :: SELLSHARES
 * Sells a number of shares, reducing the transaction by that amount
 ************************************************************************/
Transaction Transaction :: sellShares(int in_sellCount, Dollars in_salePrice)
{
   assert(in_sellCount >= 0);
   if (in_sellCount < 0)
      in_sellCount = 0;

   if (in_sellCount > m_shareCount)
      in_sellCount = m_shareCount;

   assert(in_salePrice >= 0);
   if (in_salePrice < 0)
      in_salePrice = 0;

   m_shareCount -= in_sellCount;

   Transaction salesTransaction(in_sellCount, m_buyPrice, in_salePrice);

   assert(m_shareCount >= 0);
   assert(m_buyPrice >= 0);
   assert(m_soldPrice >= 0);

   return salesTransaction;
}

/***********************************************************************
 * TRANSACTION :: GETPROFIT
 * If this was a sale, gets the profit, else gets 0
 ************************************************************************/
Dollars Transaction :: getProfit() const
{
   if (m_sold)
      return (m_soldPrice - m_buyPrice) * m_shareCount;
   else
      return Dollars(0);
}

/***********************************************************************
 * TRANSACTION :: DISPLAY
 * Displays the transaction as appropriate depending on whether it is
 * a sale or not
 ************************************************************************/
void Transaction :: display(ostream & out) const
{
   if (m_sold)
   {
      out << "\tSold " << m_shareCount
          << " shares at " << m_soldPrice
          << " for a profit of " << getProfit()
          << endl;
   }
   else
   {
      out << "\tBought " << m_shareCount
          << " shares at " << m_buyPrice
          << endl;
   }
}

/***********************************************************************
 * OPERATOR << Transaction
 * Displays the transaction as appropriate depending on whether it is
* a sale or not
************************************************************************/
ostream & operator << (ostream & out, const Transaction & rhs)
{
   rhs.display(out);
   return out;
}
