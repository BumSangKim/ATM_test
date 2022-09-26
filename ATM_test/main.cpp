#include <iostream>
#include "ATM.h"
#include "ATMcontrol.h"

using namespace std;

#define INT0_vect // interrupt service routine for card insert check
#define TEST

ATM g_atm;

void interruptServiceRoutine(INT0_vect) {
    cout << "cardCheck" << endl;
    if (g_atm.cardCheck() != SUCCESS) {
        return;
    }
    
    cout << "selectAccount" << endl;
    if (g_atm.selectAccount() != SUCCESS) {
        return;
    }
    
    cout << "selectNext" << endl;
    int index = -1;
    if (g_atm.selectNext(index) != SUCCESS) {
        return;
    }
    SELECTED_NEXT_EXECUTE nextToDo = static_cast<SELECTED_NEXT_EXECUTE>(index);
    
    switch (nextToDo) {
        case GET_BALANCE: {
            int balace = -1;
            g_atm.getBalance(balace);
            cout << "cur balance is $" << balace << endl;
            break;
        }
            
        case DEPOSIT:
            g_atm.deposit();
            break;
            
        case WITHDRAW:
            bool withdrawStatus;
            g_atm.withdraw(withdrawStatus);
            if (withdrawStatus == 0) {
                cout << "The deposit is less than the withdrawal you wish to make." << endl;
            }
            break;
            
        case EXIT:
            cout << "exit" << endl;
            break;
        default:
            break;
    }
    
    g_atm.resetData();
}

int main() {
    cout << "start ATM." << endl;
    initCommand();
#if defined(TEST)
    loadServerData();
#endif
    
    while(true){
#if defined(TEST)
        interruptServiceRoutine();
#endif
    }
    cout << "end ATM." << endl;
    return 0;
}
