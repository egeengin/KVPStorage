#include <iostream>
#include <fstream>
#include <iomanip>
#include <json.hpp>
#include <DaoInMemory.h>

using namespace std;
using json = nlohmann::json;

DaoInMemory &DaoInMemory::GetInstance() {
    static DaoInMemory instance;
    return instance;
}

bool DaoInMemory::ReadSettingsFromFile(nlohmann::json &jsonfile, std::string filename = SettingsFile) {
    ifstream inputfile(filename);
    if (!inputfile.is_open()) {
        return EXIT_FAILURE;
    } else {
        inputfile >> jsonfile;
        inputfile.close();
        return EXIT_SUCCESS;
    }
}

bool DaoInMemory::WriteSettingsToFile(nlohmann::json &jsonfile, std::string filename = SettingsFile) {
    ofstream outputfile(filename);
    outputfile << setw(4) << jsonfile << endl;
    outputfile.close();
    return EXIT_SUCCESS;
}

bool DaoInMemory::SetKVP(std::string &key, std::string &value) {
    json j;

    ReadSettingsFromFile(j);
    j[key] = value;
    WriteSettingsToFile(j);

    cout << "OK" << endl;
    return EXIT_SUCCESS;
}

bool DaoInMemory::GetKVP(std::string &key) {
    json j;

    if (ReadSettingsFromFile(j)) {
        // cout << "No settings file" << endl;
        cout << endl;
        return EXIT_FAILURE;
    }

    if (j[key].is_null())
        cout << endl;
    else {
        string j_key = to_string(j[key]);
        string str_out = j_key.substr(1, j_key.size() - 2); // Remove quotes
        cout << str_out << endl;
    }

    return EXIT_SUCCESS;
}

bool DaoInMemory::DeleteKVP(std::string &key) {
    json j;

    ReadSettingsFromFile(j);
    j[key] = "";
    WriteSettingsToFile(j);
    cout << "OK" << endl;
    return EXIT_SUCCESS;
}

DaoInMemory::~DaoInMemory() {

}
