#include "ATM.h"
#include "ATMcontrol.h"

using namespace std;

ATM::ATM()
:curCardID("")
{
    curCardInfo = nullptr;
    curAccount = Account();
}

ATM::~ATM()
{
}


// int getCardIdFromCardReader(string& cardID);
int ATM::getCardID() {
    // get card ID form card reader
    if(getCardIdFromCardReader(curCardID) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

// int countMoneyFromDepositMachine(int& money);
int ATM::getMoneyCount(int& money) {
    // Count how much money is in the deposit machine
    if(countMoneyFromDepositMachine(money) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

// int requestServer(string command, void* param, void* retParam = NULL);
int ATM::isValidCardID() {
    if(requestServer("IsValidCardID", &curCardID) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

// int getPINFromUser(int& PIN)
int ATM::getCardInfo() {
    int PIN = -1;
    if (getPINFromUser(PIN) != SUCCESS) {
        return FAIL;
    }
    
    GetCardInfoKey getCardInfoKey(curCardID, PIN);
    curCardInfo = new CardInfo();
    if(requestServer("GetCardInfo", &getCardInfoKey, curCardInfo) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

int ATM::cardCheck() {
    if (getCardID() != SUCCESS) {
        resetData();
        cout << "fail read card id from your card." << endl;
        return FAIL;
    }
    
    if (isValidCardID() != SUCCESS) {
        resetData();
        cout << "it is not valid card id." << endl;
        return FAIL;
    }
    
    if (getCardInfo() != SUCCESS) {
        resetData();
        cout << "it is not valid PIN." << endl;
        return FAIL;
    }
    
    return SUCCESS;
}

// int showAccountToScreen(string& cardID);
int ATM::showAccount() {
    if(showAccountToScreen(curCardID) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

// int getAccountIndexFromUser(int& index);
int ATM::selectAccount() {
    if (showAccount() != SUCCESS) {
        return FAIL;
    }
    
    int currentIndex = -1;
    if (getAccountIndexFromUser(currentIndex) != SUCCESS) {
        return FAIL;
    }
    if (currentIndex >= curCardInfo->getAccounts().size()) {
        cout << "Out of Index." << endl;
        return FAIL;
    }
    curAccount = curCardInfo->getAccounts()[currentIndex];
    return SUCCESS;
}

// int getNextToDoIndexFromUser(int& index);
int ATM::selectNext(int& nextToDo) {
    if(getNextToDoIndexFromUser(nextToDo) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

int ATM::getBalance(int& balance) {
    GetBalanceKey getBalanceKey(*curCardInfo, curAccount);
    if(requestServer("GetBalance", &getBalanceKey, &balance) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

int ATM::deposit() {
    int curMoneyCount = -1;
    if (getMoneyCount(curMoneyCount) != SUCCESS) {
        return FAIL;
    }
    
    TransactionKey depositKey(*curCardInfo, curAccount, curMoneyCount);
    if(requestServer("Deposit", &depositKey) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

// int selectWithdrawMoney(int& money);
int ATM::withdraw(int& withdrawStatus/* 0: lack of money in account, 1: lack of money in ATM 2: success*/) {
    int curSelectMoney = -1;
    if (selectWithdrawMoney(curSelectMoney) != SUCCESS) {
        return FAIL;
    }
    
    TransactionKey withdrawKey(*curCardInfo, curAccount, curSelectMoney);
    if(requestServer("Withdraw", &withdrawKey, &withdrawStatus) != SUCCESS) {
        return FAIL;
    }
    return SUCCESS;
}

int ATM::resetData() {
    curCardID = "";
    delete curCardInfo;
    curCardInfo = nullptr;
    curAccount = Account();
    
    return SUCCESS;
}

