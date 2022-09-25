#ifndef ATM_h
#define ATM_h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum ERROR {
    SUCCESS = 0,
    FAIL
};

enum SELECTED_NEXT_EXECUTE {
    GET_BALANCE = 0,
    DEPOSIT,
    WITHDRAW,
    EXIT,
};

class Account {
private:
    string accountNumber;
public:
    Account() {
        accountNumber = "";
    }
    string getAccountNumber(){return accountNumber;}
    void setAccountNumber(string& accountNumber){this->accountNumber = accountNumber;}
};

class CardInfo {
private:
    string cardID;
    vector<Account> accounts;
public:
    CardInfo() {
        cardID = "";
        accounts = vector<Account>();
    }
    vector<Account> getAccount(){return accounts;}
    void setAccount(vector<Account>& accounts){this->accounts = accounts;}
};

typedef struct GetCardInfoKey {
    string cardID;
    int PIN;
    GetCardInfoKey(string& cardID, int PIN) {
        this->cardID = cardID;
        this->PIN = PIN;
    }
} GetCardInfoKey;

typedef struct GetBalanceKey {
    CardInfo cardInfo;
    Account account;
    GetBalanceKey(CardInfo& cardInfo, Account& account) {
        this->cardInfo = cardInfo;
        this->account = account;
    }
} GetBalanceKey;

typedef struct TransactionKey {
    CardInfo cardInfo;
    Account account;
    int money;
    TransactionKey(CardInfo& cardInfo, Account& account, int money) {
        this->cardInfo = cardInfo;
        this->account = account;
        this->money = money;
    }
} TransactionKey;

class ATM {
    ATM();
    ~ATM();
private:
    string curCardID;
    CardInfo curCardInfo;
    Account curAccount;
    int curMoneyCount;

    int getCardID();
    int isValidCardID(); // Request to server if currentCardID is a valid card
    int getCardInfo(); // Request to server to get card information
    int getMoneyCount(int& money);

public:
    // Check card is valid
    int cardCheck();
    
    // Show Account
    int showAccount();

    // Select Account
    int selectAccount();
    
    // Select what to do next
    int selectNext(int& nextToDo);

    // See Balance
    int getBalance(int& balance);

    // Deposit
    int deposit();

    // Withdraw
    int withdraw(bool withdrawStatus);
    
    // resetData
    int resetData();
};

#endif

