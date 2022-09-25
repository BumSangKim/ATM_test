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
    string setAccountNumber(string& accountNumber){this->accountNumber = accountNumber;}
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
    vector<Account> setAccount(vector<Account>& accounts){this->accounts = accounts;}
};

typedef struct GetCardInfoKey {
    string cardID;
    int PIN;
    GetCardInfoKey(stirng& cardID, int PIN) {
        this->cardID = cardID;
        this->PIN = PIN;
    }
} GetCardInfoKey;

typedef struct DepositKey {
    CardInfo cardInfo;
    Account account;
    int money;
    GetBalanceKey(CardInfo& cardInfo, Account& account, int money) {
        this->cardInfo = cardInfo;
        this->account = account;
        this->money = money;
    }
} DepositKey;

typedef struct WithdrawKey {
    CardInfo cardInfo;
    Account account;
    int money;
    GetBalanceKey(CardInfo& cardInfo, Account& account, int money) {
        this->cardInfo = cardInfo;
        this->account = account;
        this->money = money;
    }
} WithdrawKey;

class ATM {
    ATM();
    ~ATM();
private:
    string currentCardID;
    CardInfo curCardInfo;
    Account curAccount;

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
    int deposit(int money);

    // Withdraw
    int withDraw(int money);
    
    // resetData
    int resetData();
};

#endif

