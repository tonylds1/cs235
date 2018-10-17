/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell().
 * Author
 *    Maximiliano Correa, Esteban Cabrera and Tony Moraes.
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for DOLLARS defined in StockTransaction
#include "queue.h"     // for QUEUE
#include "portfolio.h" // for PORTFOLIO
#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT


// the interactive stock buy/sell function
void stocksBuySell();

#endif // STOCK_H
