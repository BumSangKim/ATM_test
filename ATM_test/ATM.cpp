#include <ATM.h>

using namespace std;

ATM::ATM()
:currentCardID("")
{
    curCardInfo = CardInfo();
    curAccount = Account();
}

// int getCardIdFromCardReader(string& cardID);
int ATM::getCardID() {
    // get card ID form card reader
    if(getCardIdFromCardReader(currentCardID) != SUCCESS) {
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

// int requestServer(string Command, void* param, void* retParam = NULL);
int ATM::isValidCardID(string& cardID) {
    if(requestServer("IsValidCardID", &cardID) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

int ATM::getCardInfo(stirng cardID, int PIN) {
    GetCardInfoKey getCardInfoKey(cardID, PIN);
    if(requestServer("GetCardInfo", &getCardInfoKey, &curCardInfo) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

// int showAccountToScreen(vector<Account>& accounts);
int ATM::showAccount() {
    if(showAccountToScreen(curCardInfo.getAccount()) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

// int getIndexFromUser(int& index);
int ATM::selectAccount() {
    if(showAccount() != SUCCESS) {
        return FAIL;
    }
    
    int currentIndex = -1;
    if (getIndexFromUser(&currentIndex) != SUCCESS) {
        return FAIL;
    }
    
    curAccount = curCardInfo.getAccount()[currentIndex];
        
    return SUCCESS;
}

int ATM::getBalance(int& balance) {
    GetBalanceKey getBalanceKey(cardInfo, account);
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
    
    DepositKey depositKey(cardInfo, account, curMoneyCount);
    if(requestServer("Deposit", &depositKey) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

int ATM::withdraw(int money, bool withdrawStatus/* 0: lack of money, 1: success*/) {
    WithdrawKey withdrawKey(cardInfo, account, money);
    if(requestServer("Withdraw", &withdrawKey, &withdrawStatus) != SUCCESS) {
        return FAIL;
    }
    
    return SUCCESS;
}

int ATM::resetData() {
    currentCardID = "";
    curCardInfo = CardInfo();
    curAccount = Account();
}

