#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;



const string clientFileName = "client.txt";
const string usersFileName = "users.txt";

struct stClient {
    string AccountNumber;
    string PinCode;
    string FullName;
    string Phone;
    double Balance;
    bool MarkForDelete = false;
};

struct stUser {
    string UserName;
    string Password;
    int Permissions;
    bool MarkForDelete = false;
};

stUser CurrentUser;
enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransactions = 6,
    eMangeUsers = 7, eExit= 8,
};

enum enMangeUsersMuneOption {
    eListUsers=1,
    eAddNewUser=2,
    eDeleteUser=3,
    eUpdateUser=4,
    eFindUser=5,
    eMainMune=6,
};

enum enMainMenuePermissions {
    eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient
    = 4,
    pUpdateClients = 8, pFindClient = 16, pTranactions = 32,
    pManageUsers = 64
};

enum enTransctionsMenueOptions {
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalances = 3,
    eMainMenue = 4
};


void ShowTransactionsScreen();
void ShowMainMenue();
void ShowMangeUserMenu();
void Login();
void  PerformManageUsersMenueOption(enMangeUsersMuneOption MangeUserMenu);



string ReadClientAccountNumber() {
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code       : " << Client.PinCode;
    cout << "\nName           : " << Client.FullName;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.Balance;
    cout << "\n-----------------------------------\n";
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

void GoBackToTransctiosMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsScreen();
}

void GoBackToMangeMune() 
{
    cout << "\n\nPress any key to go back to Mange Menue...";
    system("pause>0");
    ShowMangeUserMenu();
}
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

short ReadMangeUsersMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short choise = 0;
    cin >> choise;
    return choise;
}

short ReadTransctionsMenueOption() {
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.FullName + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.Balance);
    return stClientRecord;
}

string ConvertUserLinetoRecord(stUser User, string Seperator = "#//#")
{
    string userRecord = "";
    userRecord += User.UserName + Seperator;
    userRecord += User.Password + Seperator;
    userRecord += to_string(User.Permissions);

    return userRecord;
}

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    stClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.FullName = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Balance = stod(vClientData[4]);
    return Client;
}

stUser ConvertUserLinetoRecord(string Line, string Seperator = "#//#")
{
    stUser User;
    vector <string> vUserDate;

    vUserDate = SplitString(Line, Seperator);

    User.UserName = vUserDate[0];
    User.Password = vUserDate[1];
    User.Permissions = stoi(vUserDate[2]);

    return User;
}

vector <stClient> LoadCleintsDataFromFile(string fileName) {
    vector <stClient> vClient;
    fstream file;

    file.open(fileName, ios::in); // Read Mode
    if (file.is_open()) {
        string line;
        stClient Client;
        while (getline(file, line)) {
            Client = ConvertLinetoRecord(line);
            vClient.push_back(Client);
        }
        file.close();
    }
    return vClient;
}

vector <stUser> LoadUsersDataFromFile(string fileName)
{
    vector <stUser> vUser;

    fstream file;

    file.open(fileName, ios::in);

    if (file.is_open())
    {
        string Line;
        stUser User;

        while (getline(file, Line))
        {
            User = ConvertUserLinetoRecord(Line);

            vUser.push_back(User);
        }




        file.close();
    }


    return vUser;



}

void PrintClientRecordLine(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.FullName;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Balance;
}

void PrintUsersRecordLine(stUser User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(15) << left << User.Password;
    cout << "| " << setw(15) << left << User.Permissions;
}

void ShowAllClientsScreen() {
    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // Overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (!C.MarkForDelete)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

stClient ReadNewClient()
{
    stClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExistsByAccountNumber(Client.AccountNumber, clientFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.FullName);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.Balance;
    return Client;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void AddNewClient() {
    stClient Client = ReadNewClient();
    AddDataLineToFile(clientFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void ShowAddNewClientsScreen() {
    cout << "\n_________________________________________\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n_________________________________________\n";
    AddNewClients();
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient> vClients, stClient& Client)
{
    for (stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber && !C.MarkForDelete)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClients) {
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (tolower(Answer) == 'y') {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(clientFileName, vClients);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
    return false;
}

void ShowDeleteClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);
    string accountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(accountNumber, vClients);
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.FullName);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.Balance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClients) {
    stClient client;
    char answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, client)) {
        PrintClientCard(client);
        cout << "\n\nAre you sure you want update this client? y/n? ";
        cin >> answer;

        if (tolower(answer) == 'y') {
            for (stClient& cUpdate : vClients) {
                if (cUpdate.AccountNumber == AccountNumber) {
                    cUpdate = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(clientFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
    return false;
}

void ShowUpdateClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);
    string accountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(accountNumber, vClients);
}

void ShowFindClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

// Transactions Logic

bool DepositBalanceByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients) {
    char Answer = 'n';
    cout << "\n\nAre you sure you want to perform this transaction? y/n? ";
    cin >> Answer;

    if (tolower(Answer) == 'y') {
        for (stClient& C : vClients) {
            if (C.AccountNumber == AccountNumber) {
                C.Balance += Amount;
                SaveCleintsDataToFile(clientFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.Balance << endl;
                return true;
            }
        }
    }
    return false;
}

void ShowDepositScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);
    string AccountNumber = ReadClientAccountNumber();
    stClient Client;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);
    string AccountNumber = ReadClientAccountNumber();
    stClient Client;

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    // Validate balance sufficiency
    while (Amount > Client.Balance) {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Balance;
        cout << "\nPlease enter another amount? ";
        cin >> Amount;
    }

    // Multiply by -1 for subtraction
    DepositBalanceByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void PrintClientRecordBalanceLine(stClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.FullName;
    cout << "| " << setw(12) << left << Client.Balance;
}

void ShowTotalBalancesScreen() {
    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else {
        for (stClient Client : vClients) {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.Balance;
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalances << endl;
}

void PerfromTransctionsMenueOption(enTransctionsMenueOptions TransctionsMainMenu) {
    switch (TransctionsMainMenu) {
    case enTransctionsMenueOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransctiosMenue();
        break;
    case enTransctionsMenueOptions::eWithdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransctiosMenue();
        break;
    case enTransctionsMenueOptions::eTotalBalances:
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransctiosMenue();
        break;
    case enTransctionsMenueOptions::eMainMenue:
        ShowMainMenue();
        break;
    }
}

void ShowTransactionsScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit\n";
    cout << "\t[2] Withdraw\n";
    cout << "\t[3] Total Balances\n";
    cout << "\t[4] Main Menue\n";
    cout << "===========================================\n";

    PerfromTransctionsMenueOption((enTransctionsMenueOptions)ReadTransctionsMenueOption());
}

void ShowEndScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}


void ShowAllUsersScreen()
{
    vector<stUser> vUser = LoadUsersDataFromFile(usersFileName);

    cout << "\n\t\t\t\t\tClient List (" << vUser.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUser.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stUser User : vUser)
        {
            PrintUsersRecordLine(User);
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void ShowListUsersScreen()
{
    ShowAllUsersScreen();


}

int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';


    cout << "\nDo you want to give full access? Y/N? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give access to: ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pListClients;
    }

    cout << "\nDo you want to give access to: ";


    cout << "\nShow Client List? Y/N? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuePermissions::pListClients;
    }


    cout << "\nAdd New Clients? Y/N?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenueOptions::eAddNewClient;
    }


    cout << "\nDelete Client? Y/N? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pDeleteClient;
    }

    cout << "\nUpdate Client? Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nUpdate Client? Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pUpdateClients;
    }

    cout << "\nTranactions? Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pTranactions;
    }

    cout << "\nMange User? Y/N?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enMainMenuePermissions::pManageUsers;
    }



    return Permissions;
   
}


stUser ReadNewUser()
{
    stUser User;
    cout << "Enter Username? ";
    getline(cin >> ws, User.UserName);
    while (ClientExistsByAccountNumber(User.UserName, clientFileName))
    {
        cout << "\User with [" << User.UserName << "] already exists, Enter another Username ? ";
        getline(cin >> ws, User.UserName);
    }
    cout << "Enter Password? ";
    getline(cin, User.Password);

    User.Permissions = ReadPermissionsToSet();
    return User;
}

void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(usersFileName, ConvertUserLinetoRecord(User));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do {
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users Y/N? ";


        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}


void ShowAddNewUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();
}




void ShowMangeUserMenu()
{


    system("cls");
    cout << "===========================================\n";
    cout << "\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update Usre.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";


    PerformManageUsersMenueOption((enMangeUsersMuneOption)ReadMangeUsersMenueOption());


}


void  PerformManageUsersMenueOption(enMangeUsersMuneOption MangeUserMenu)
{
    switch(MangeUserMenu)
    {
    case enMangeUsersMuneOption::eListUsers: 
    {
        system("cls");
        ShowListUsersScreen();
        GoBackToMangeMune();
    }
    case enMangeUsersMuneOption::eAddNewUser: 
    {
        system("cls");
        ShowAddNewUserScreen();
    }
    
    
    }
}



void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eTransactions:
        system("cls");
        ShowTransactionsScreen();
        break;
    case enMainMenueOptions::eMangeUsers:
        system("cls");
        ShowMangeUserMenu();
        break;

    case enMainMenueOptions::eExit:
        system("cls");
        //ShowEndScreen();
        Login();
        break;
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Mange Users.\n";
    cout << "\t[7] Logout.\n";
    cout << "===========================================\n";

    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool FindUserByUserNameAndPassword(string UserName, string Password, stUser &User)
{
    vector <stUser> vUsers = LoadUsersDataFromFile(usersFileName);


    for (stUser U : vUsers)
    {
        if (U.UserName == UserName && U.Password == Password)
        {
            User = U;
            return true;
        }
    }

    return false;
}



bool LoadUserInfo(string UserName, string Password)
{
    return FindUserByUserNameAndPassword(UserName, Password, CurrentUser);
}


void Login()
{
    bool LoginFaild = false;

    string UserName, Passwoed;

    do {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n-----------------------------------\n";



        if (LoginFaild)
        {
            cout << "Invlaid Username/Password!\n";

        }

        cout << "Enter UserName? ";
        cin >> UserName;

        cout << "Enter Password? ";
        cin >> Passwoed;

        LoginFaild = !LoadUserInfo(UserName, Passwoed);


    } while (LoginFaild);


    ShowMainMenue();

}

int main()
{
    Login();
    return 0;
}