#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

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

void ShowFindClientScreen() {

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
 



void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
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


