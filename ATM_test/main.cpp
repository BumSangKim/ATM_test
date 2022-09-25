#include <iostream>
#include "ATM.h"

using namespace std;

#define INT0_vect // interrupt service routine for card insert check

ATM g_atm;

void ISR(INT0_vect) {
    if (g_atm.cardCheck() != SUCCESS) {
        return;
    }
    
    if (g_atm.showAccount() != SUCCESS) {
        return;
    }
    
    if (g_atm.selectAccount() != SUCCESS) {
        return;
    }
    
    int index = -1;
    if (g_atm.selectNext(index) != SUCCESS) {
        return;
    }
    SELECTED_NEXT_EXECUTE nextToDo = static_cast<SELECTED_NEXT_EXECUTE>(index);
    
    switch (nextToDo) {
        case GET_BALANCE:
            int balace = -1;
            g_atm.getBalance(balace);
            cout << "cur balance is $" << balace << endl;
            break;
            
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
            break;
    }
    
    g_atm.resetData();
}

int main() {
    cout << "start ATM." << endl;
    while(true){
#if defined(TEST)
        ISR();
#endif
    }
    cout << "end ATM." << endl;
    return 0;
}
