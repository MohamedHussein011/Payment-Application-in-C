# Payment-Application-in-C
Project Introduction


Payment systems are now available everywhere and everyone interacts with these systems every day.

There are different types of transactions you can make, SALE, REFUND, Pre-Authorization, and VOID.

    SALE: means to buy something and its price will be deducted from your bank account.
    REFUND: this means that you will return something and wants your money back to your bank account.
    Pre-Authorization: means holding an amount of money from your account, e.g Hotel reservation.
    VOID: this means canceling the transaction, e.g if the seller entered the wrong amount.


You are required to implement the SALE transaction only by simulating the card, terminal(ATM), and the server.

Project Requirements


    Development environment preparation
    Implement the card module
    Implement the terminal module
    Implement the server module
    Implement the application
    Testing the application

The project can be distributed over 6 main tasks:


Development environment preparation

    Create modules folders
    Create .c and .h file for each module
    Add header file guard
    Create the main.c file

Implement the card module

    Fill in card.h file with functions' prototypes and typedefs
    Implement getCardHolderName function
    Implement getCardExpiryDate function
    Implement getCardPAN function

Implement the terminal module

    Fill in terminal.h file with functions' prototypes and typedefs
    Implement getTransactionDate function
    Implement isCardExpried function
    Implement gatTransactionAmount function
    Implement isBelowMaxAmount function
    Implement setMaxAmount function

Implement the server module

    Fill in server.h file with functions' prototypes and typedefs
    Implement server-side accounts' database
    Implement server-side transactions' database
    Implement recieveTransactionData function
    Implement isValidAccount function
    Implement isAmountAvailable function
    Implement saveTransaction function

Implement the application

    Fill in application.h file with functions' prototypes
    Implement appStart function

Testing the application

    Transaction approved user story
    Exceed the maximum amount user story
    Insufficient fund user story
    Expired card user story
    Invalid card user story

