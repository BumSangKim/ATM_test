#ifndef ATMcontrol_h
#define ATMcontrol_h

#include <iostream>
#include <string>
#include <vector>

int requestServer(string command, void* param, void* retParam = NULL);
int getCardIdFromCardReader(string& cardID);
int countMoneyFromDepositMachine(int& money);
int getPINFromUser(int& PIN);
int showAccountToScreen(vector<Account>& accounts);
int getIndexFromUser(int& index);
int getIndexFromUser(int& index);
int selectWithdrawMoney(int& money);

#endif
