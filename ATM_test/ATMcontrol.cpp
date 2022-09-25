#include "ATMcontrol.h"
#include "ATM.h"

using namespace std;

unordered_map<string, ServerData> g_serverData;
int loadServerData() {
    string cardID0 = "1234123412341234";
    AccountInfo account00("10", 100);
    AccountInfo account01("11", 200);
    vector<AccountInfo> accountInfo0;
    accountInfo0.push_back(account00);
    accountInfo0.push_back(account01);
    ServerData d0;
    d0.cardID = cardID0;
    d0.PIN = 1234;
    d0.accountInfo = accountInfo0;
    g_serverData[cardID0] = d0;
    
    string cardID1 = "2345234523452345";
    AccountInfo account10("20", 300);
    AccountInfo account11("21", 20);
    vector<AccountInfo> accountInfo1;
    accountInfo1.push_back(account10);
    accountInfo1.push_back(account11);
    ServerData d1;
    d1.cardID = cardID1;
    d1.PIN = 2345;
    d1.accountInfo = accountInfo1;
    g_serverData[cardID1] = d1;
    
    return SUCCESS;
}

void initCommand() {
    isInit = true;
    commandMap["IsValidCardID"] = IS_VALID_CARD_ID_COMMAND;
    commandMap["GetCardInfo"] = GET_CARD_INFO_COMMAND;
    commandMap["GetBalance"] = GET_BALANCE_COMMAND;
    commandMap["Deposit"] = DEPOSIT_COMMAND;
    commandMap["Withdraw"] = WITHDRAW_COMMAND;
}

int requestServer(string command, void* param, void* retParam) {
    if (!isInit) initCommand();
    switch (commandMap[command]) {
        case IS_VALID_CARD_ID_COMMAND:
            
            break;
        case GET_CARD_INFO_COMMAND:
            
            break;
        case GET_BALANCE_COMMAND:
            
            break;
        case DEPOSIT_COMMAND:
            
            break;
        case WITHDRAW_COMMAND:
            
            break;
    }
    
    return SUCCESS;
}

int getCardIdFromCardReader(string& cardID) {
    cout << "card ID를 입력하시오.";
    cin >> cardID;
    return SUCCESS;
}

int countMoneyFromDepositMachine(int& money) {
    
    return SUCCESS;
}

int getPINFromUser(int& PIN) {
    
    return SUCCESS;
}

int showAccountToScreen(string& cardID) {
    
    return SUCCESS;
}

int getIndexFromUser(int& index) {
    
    cin >> index;
    return SUCCESS;
}

int selectWithdrawMoney(int& money) {
    
    return SUCCESS;
}
