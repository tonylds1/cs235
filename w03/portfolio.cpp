/***********************************************************************
 * Program:
 *    Portfolio
 * Summary:
 *    This class contains the data about a customers portfolio.
 * Authors:
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 ************************************************************************/
#include "portfolio.h"  // for the class definition
#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
using namespace std;

/***********************************************************************
 * PORTFOLIO :: CONSTRUCTOR
 * Creates a new Queue to keep track of the buy/sell transactions
 ************************************************************************/
Portfolio :: Portfolio()
      : m_proceeds(0)
{
}

/***********************************************************************
 * PORTFOLIO :: DESTRUCTOR
 * Destructs the portfolio.
 ************************************************************************/
Portfolio :: ~Portfolio()
{
}

/***********************************************************************
 * PORTFOLIO :: BUY
 * Buys stock and puts it in the portfolio.
 ************************************************************************/
void Portfolio :: buy(int number, Dollars price)
{
   Transaction t = Transaction(number, price);
   m_holdings.push(t);
}

/***********************************************************************
 * PORTFOLIO :: SELL
 * Sells stocks and updates the portfolio accordingly.
 ************************************************************************/
void Portfolio :: sell(int number, Dollars price)
{
   while (number > 0 && !m_holdings.empty())
   {
      Transaction sale = m_holdings.front().sellShares(number, price);
      number -= sale.getShareCount();
      m_proceeds += sale.getProfit();
      m_saleHistory.push(sale);

      if (m_holdings.front().getShareCount() == 0)
         m_holdings.pop();
   }
}

/***********************************************************************
 * PORTFOLIO :: DISPLAY
 * Displays the portfolio
 ************************************************************************/
void Portfolio :: display(ostream & out) const
{
   if (!m_holdings.empty())
   {
      out << "Currently held:\n";
      Queue <Transaction> q = m_holdings;

      while (!q.empty())
      {
         out << q.front();
         q.pop();
      }
   }

   if (!m_saleHistory.empty())
   {
      out << "Sell History:\n";
      Queue<Transaction> s = m_saleHistory;

      while (!s.empty())
      {
         out << s.front();
         s.pop();
      }

   }
   out << "Proceeds: " << m_proceeds << endl;
}

/***********************************************************************
 * PORTFOLIO INSERTION OPERATOR
 * Allows data to be outputted to the screen without the std library.
 ************************************************************************/
ostream & operator << (ostream & out, const Portfolio & rhs)
{
   rhs.display(out);
   return out;
}
