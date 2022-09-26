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
    commandMap["IsValidCardID"] = IS_VALID_CARD_ID_COMMAND;
    commandMap["GetCardInfo"] = GET_CARD_INFO_COMMAND;
    commandMap["GetBalance"] = GET_BALANCE_COMMAND;
    commandMap["Deposit"] = DEPOSIT_COMMAND;
    commandMap["Withdraw"] = WITHDRAW_COMMAND;
}

int requestServer(string command, void* param, void* retParam) {
    switch (commandMap[command]) {
        case IS_VALID_CARD_ID_COMMAND: {
            string curCardID = *(string*)param;
            if (g_serverData.count(curCardID) == 0) {
                cout << "This Card ID is not vaild." << endl;
                return FAIL;
            }
            break;
        }
        
        case GET_CARD_INFO_COMMAND: {
            GetCardInfoKey curCardInfoKey = *(GetCardInfoKey*)param;
            if (g_serverData[curCardInfoKey.cardID].PIN != curCardInfoKey.PIN) {
                cout << "This PIN is not vaild." << endl;
                return FAIL;
            }
            
            CardInfo* retCardInfo = (CardInfo*)retParam;
            vector<Account> accounts(g_serverData[curCardInfoKey.cardID].accountInfo.size(), Account());
            int n = g_serverData[curCardInfoKey.cardID].accountInfo.size();
            for (int i = 0; i < n; i++) {
                accounts[i].setAccountNumber(g_serverData[curCardInfoKey.cardID].accountInfo[i].accountID);
            }
            retCardInfo->setCardID(curCardInfoKey.cardID);
            retCardInfo->setAccount(accounts);
            break;
        }
        
        case GET_BALANCE_COMMAND:{
            GetBalanceKey curBalanceKey = *(GetBalanceKey*)param;
            int* balance = (int*)retParam;
            
            int n = g_serverData[curBalanceKey.cardInfo.getCardID()].accountInfo.size();
            for (int i = 0; i < n; i++) {
                if (g_serverData[curBalanceKey.cardInfo.getCardID()].accountInfo[i].accountID == curBalanceKey.account.getAccountNumber()) {
                    *balance = g_serverData[curBalanceKey.cardInfo.getCardID()].accountInfo[i].balance;
                    break;
                }
            }
            break;
        }
        
        case DEPOSIT_COMMAND: {
            TransactionKey curTransactionKey = *(TransactionKey*)param;
            
            int n = g_serverData[curTransactionKey.cardInfo.getCardID()].accountInfo.size();
            for (int i = 0; i < n; i++) {
                if (g_serverData[curTransactionKey.cardInfo.getCardID()].accountInfo[i].accountID == curTransactionKey.account.getAccountNumber()) {
                    g_serverData[curTransactionKey.cardInfo.getCardID()].accountInfo[i].balance += curTransactionKey.money;
                    break;
                }
            }
            break;
        }
        case WITHDRAW_COMMAND: {
            TransactionKey curTransactionKey = *(TransactionKey*)param;
            
            int n = g_serverData[curTransactionKey.cardInfo.getCardID()].accountInfo.size();
            for (int i = 0; i < n; i++) {
                if (g_serverData[curTransactionKey.cardInfo.getCardID()].accountInfo[i].accountID == curTransactionKey.account.getAccountNumber()) {
                    if (g_serverData[curTransactionKey.cardInfo.getCardID()].accountInfo[i].balance < curTransactionKey.money) {
                        *(bool*)retParam = 0;
                        break;
                    }
                    g_serverData[curTransactionKey.cardInfo.getCardID()].accountInfo[i].balance -= curTransactionKey.money;
                    *(bool*)retParam = 1;
                    break;
                }
            }
            break;
        }
    }
    
    return SUCCESS;
}

int getCardIdFromCardReader(string& cardID) {
    cout << "card ID를 입력하시오. : ";
    cin >> cardID;
    return SUCCESS;
}

int countMoneyFromDepositMachine(int& money) {
    cout << "입금하실 금액을 넣어주세요. : ";
    cin >> money;
    return SUCCESS;
}

int getPINFromUser(int& PIN) {
    cout << "PIN 번호를 입력하시오. : ";
    cin >> PIN;
    return SUCCESS;
}

int showAccountToScreen(string& cardID) {
    int n = g_serverData[cardID].accountInfo.size();
    for (int i = 0 ; i < n; i++) {
        cout << i << " : " << g_serverData[cardID].accountInfo[i].accountID << endl;
    }
    return SUCCESS;
}

int getAccountIndexFromUser(int& index) {
    cout << "Account Index를 입력하시오. : ";
    cin >> index;
    return SUCCESS;
}

int getNextToDoIndexFromUser(int& index) {
    cout << "0 : GET_BALANCE" << endl;
    cout << "1 : DEPOSIT" << endl;
    cout << "2 : WITHDRAW" << endl;
    cout << "3 : EXIT" << endl;
    cout << "Index를 입력하시오. : ";
    cin >> index;
    return SUCCESS;
}

int selectWithdrawMoney(int& money) {
    cout << "인출하실 금액을 입력해주세요. : ";
    cin >> money;
    return SUCCESS;
}
