#ifndef ATMcontrol_h
#define ATMcontrol_h

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct AccountInfo {
    string accountID;
    int balance;
    AccountInfo(string accountID, int balance) {
        this->accountID = accountID;
        this->balance = balance;
    }
} AccountInfo;

typedef struct ServerData {
    string cardID;
    int PIN;
    vector<AccountInfo> accountInfo;
} ServerData;

class ATM;
class Account;

int loadServerData();

static bool isInit = false;
static unordered_map<string, int> commandMap;
enum SERVER_COMMAND {
    IS_VALID_CARD_ID_COMMAND = 0,
    GET_CARD_INFO_COMMAND,
    GET_BALANCE_COMMAND,
    DEPOSIT_COMMAND,
    WITHDRAW_COMMAND,
    SERVER_COMMAND_COUNT
};
void initCommand();
int requestServer(string command, void* param, void* retParam = NULL);
int getCardIdFromCardReader(string& cardID);
int countMoneyFromDepositMachine(int& money);
int getPINFromUser(int& PIN);
int showAccountToScreen(string& cardID);
int getIndexFromUser(int& index);
int selectWithdrawMoney(int& money);

#endif
