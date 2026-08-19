#include <iostream>

using namespace std;



void ShowMainMenue();
const string clientFileName = "client.txt";

struct stClient {
    string AccountNumber;
    string PinCode;
    string FullName;
    string Phone;
    double Balance;
    bool MarkForDelete = false;
};


enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eExit = 6
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}


short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void AddUserClient() {
    cout << "[1] add Client";
}

void DeleteUserClient() {
    cout << "[2] Delete Client";
}

void UpdateUserClient() {
    cout << "[3] Update Client";
}




void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");

        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        AddUserClient();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eDeleteClient:
        system("cls");

        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eUpdateClient:
        system("cls");

        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eFindClient:
        system("cls");

        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eExit:
        system("cls");

        break;
    }
}
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}





int main()
{
    ShowMainMenue();

}


