#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


void ShowTransactionsScreen();
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
    eFindClient = 5, eTransactions = 6, 
    eExit = 7
};

enum enTransctionsMenueOptions {
    eDeposit=1,
    eWithdraw=2,
    eTotalBalances=3,
    eMainMenue=4
};


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
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.FullName;
    cout << "\nPhone : " << Client.Phone;
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
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowTransactionsScreen();
}


short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
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
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length()); /* erase() until
        positon and move to next word. */
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}





string ConvertRecordToLine(stClient Client, string Seperator =
    "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.FullName + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.Balance);


    return stClientRecord;
}


stClient ConvertLinetoRecord(string Line, string Seperator =
    "#//#")
{
    stClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.FullName = vClientData[2];
    Client.Phone = vClientData[3];
    Client.Balance = stod(vClientData[4]);
    return Client;
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



void PrintClientRecordLine(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.FullName;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Balance;
}

void ShowAllClientsScreen() {

    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
        cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
 

// seve file

vector <stClient> SaveCleintsDataToFile(string FileName, vector
    <stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.
                    DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}


// Add 

bool ClientExistsByAccountNumber(string AccountNumber, string
    FileName)
{
    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
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
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return false;
}




stClient ReadNewClient()
{
    stClient Client;
    cout << "Enter Account Number? ";
    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExistsByAccountNumber(Client.AccountNumber,
        clientFileName))
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
    stClient Client;
    Client = ReadNewClient();

    AddDataLineToFile(clientFileName, ConvertRecordToLine(Client));
}



void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
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

//Find

bool FindClientByAccountNumber(string AccountNumber, vector
    <stClient> vClients, stClient& Client)
{
    for (stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}





// Delete


bool MarkClientForDeleteByAccountNumber(string AccountNumber,
    vector <stClient>& vClients)
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

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient> &vClients) {

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";

        cin >> Answer;

        MarkClientForDeleteByAccountNumber(AccountNumber, vClients);


        SaveCleintsDataToFile(clientFileName, vClients);


        //Refresh Clients

        vClients = LoadCleintsDataFromFile(clientFileName);

        cout << "\n\nClient Deleted Successfully.";
        return true;

    }

    else {
        cout << "\nClient with Account Number (" << AccountNumber
            << ") is Not Found!";
        return false;
    }

}


void ShowDeleteClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);
    string accountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(accountNumber, vClients);
}

//Update 

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


bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient> &vClients) {

    stClient client;

    char answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, client)) {

        PrintClientCard(client);

        cout << "\n\nAre you sure you want update this client? y/n? ";

        cin >> answer;
        if (tolower(answer) == 'y') {
            for (stClient &cUpdate : vClients) {

                if (cUpdate.AccountNumber == AccountNumber) {
                    cUpdate = ChangeClientRecord(AccountNumber);
                    break;

                }
            }

            SaveCleintsDataToFile(clientFileName, vClients);


            cout << "\n\nClient Updated Successfully.";
            return true;
        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber
                << ") is Not Found!";
            return false;
        }
    }

}

void ShowUpdateClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadCleintsDataFromFile(clientFileName);

    string accountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(accountNumber, vClients);
}




// Find
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
        cout << "\nClient with Account Number[" << AccountNumber
        << "] is not found!";
}



// Transctios


double ChengeDeposit(string AcccountNumber) {
    double depoist = 0;
    cout << "How much do you want to deposit?" ;
    cin >> ws >> depoist;
    return depoist;
}


void Deposit(string AccountNumber, vector<stClient> &vClients, stClient Client) {

    char answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want update this client? y/n? ";
        cin >> answer;
        if (tolower(answer) == 'y') {


            for (stClient &cl : vClients) {

                if (cl.AccountNumber == AccountNumber) {
                    cl.Balance += ChengeDeposit(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(clientFileName, vClients);

            vClients = LoadCleintsDataFromFile(clientFileName);

            cout << "\n\nClient Updated Successfully.";


        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber
                << ") is Not Found!";
        }





    }
}


void ShowDepositScreen() {
    
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Client Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClient = LoadCleintsDataFromFile(clientFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();

    Deposit(AccountNumber, vClient, Client);

}




void PerfromTransctionsMenueOption(enTransctionsMenueOptions TransctiosMainMenu) {

    switch (TransctiosMainMenu) {

    case enTransctionsMenueOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransctiosMenue();
        break;
    case enTransctionsMenueOptions::eWithdraw:
        system("cls");
        GoBackToTransctiosMenue();
        break;
    case enTransctionsMenueOptions::eTotalBalances:
        system("cls");
        GoBackToTransctiosMenue();
        break;
    case enTransctionsMenueOptions::eMainMenue:
        ShowMainMenue();
        //GoBackToMainMenue();
        break;
    }
}


void ShowTransactionsScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\tTransctions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit\n";
    cout << "\t[2] Withdraw\n";
    cout << "\t[3] Total Balances\n";
    cout << "\t[4] Main Menue\n";
    cout << "===========================================\n";


    PerfromTransctionsMenueOption((enTransctionsMenueOptions)ReadTransctionsMenueOption());
}



//Exit

void ShowEndScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}


void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
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
        GoBackToMainMenue();
        break;
    
    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
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
    cout << "\t[6] Transctions. \n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}





int main()
{
    ShowMainMenue();

}


