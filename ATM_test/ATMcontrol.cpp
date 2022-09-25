#include "ATM.h"
#include "ATMcontrol.h"

using namespace std;

int requestServer(string command, void* param, void* retParam) {
    switch (command) {
        case "IsValidCardID":
            break;
        case "GetCardInfo":
            break;
        case "GetBalance":
            break;
        case "Deposit":
            break;
        case "Withdraw":
            break;
    }
    
    return SUCCESS;
}

int getCardIdFromCardReader(string& cardID) {
    
    return SUCCESS;
}

int countMoneyFromDepositMachine(int& money) {
    
    return SUCCESS;
}

int getPINFromUser(int& PIN) {
    
    return SUCCESS;
}

int showAccountToScreen(vector<Account>& accounts) {
    
    return SUCCESS;
}

int getIndexFromUser(int& index) {
    
    return SUCCESS;
}

int getIndexFromUser(int& index) {
    
    return SUCCESS;
}

int selectWithdrawMoney(int& money) {
    
    return SUCCESS;
}
