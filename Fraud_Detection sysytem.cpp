#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;

// Trim function to remove leading and trailing spaces
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// Split function
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(str);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

// Authenticate user
bool authenticateUser(const string& userID, const string& password) {
    ifstream file("C:\\Users\\kesha\\OneDrive\\Desktop\\users.txt");
    if (!file.is_open()) {
        cout << "Error opening users.txt\n";
        return false;
    }

    string user, pass;
    while (file >> user >> pass) {
        if (user == userID && pass == password)
            return true;
    }
    return false;
}

// Load trusted IPs
vector<string> loadTrustedIPs(const string& userID) {
    ifstream file("C:\\Users\\kesha\\OneDrive\\Desktop\\know_ips.txt");
    vector<string> ips;
    if (!file.is_open()) {
        cout << "Error opening known_ips.txt\n";
        return ips;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        if (id == userID) {
            string ipList;
            getline(iss, ipList);
            if (!ipList.empty() && ipList[0] == ' ')
                ipList = ipList.substr(1);
            ips = split(ipList, ',');
            break;
        }
    }

    // Debug: Print all trusted IPs
    /*
    for (const auto& ip : ips) {
        cout << "Trusted IP: [" << ip << "]" << endl;
    }
    */

    return ips;
}

// Validate transaction ID
bool isValidTxnID(const string& txnID) {
    ifstream file("C:\\Users\\kesha\\OneDrive\\Documents\\trans.txt");
    if (!file.is_open()) {
        cout << "Error opening trans.txt\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line == txnID)
            return true;
    }
    return false;
}

// Check for suspicious IP

bool isSuspiciousIP(const string& inputIP, const vector<string>& trustedIPs) {
    for (int i = 0; i < trustedIPs.size(); i++) {
        if (trustedIPs[i] == inputIP)
            return false;
    }
    return true;
}


// Log fraud
void logFraud(const string& userID, const string& reason, const string& inputIP = "", const string& txnID = "") {
    ofstream file("C:\\Users\\kesha\\OneDrive\\Desktop\\fraud_log.txt", ios::app);
    time_t now = time(0);
    string dt = ctime(&now);

    if (!dt.empty() && dt[dt.length() - 1] == '\n') {
        dt.erase(dt.length() - 1);
    }

    file << "[" << dt << "] User: " << userID << " | FRAUD: " << reason;
    if (!inputIP.empty()) file << " | IP: " << inputIP;
    if (!txnID.empty()) file << " | TxnID: " << txnID;
    file << "\n";
}

// Log success
void logSuccess(const string& userID, const string& inputIP, const string& txnID) {
    ofstream file("C:\\Users\\kesha\\OneDrive\\Desktop\\success_log.txt", ios::app);
    time_t now = time(0);
    string dt = ctime(&now);

    if (!dt.empty() && dt[dt.length() - 1] == '\n') {
        dt.erase(dt.length() - 1);
    }

    file << "[" << dt << "] User: " << userID << " | SUCCESS | IP: " << inputIP << " | TxnID: " << txnID << "\n";
}
string getGeoLocationFromIP(const string& ip) {
    string cmd = "curl -s http://ip-api.com/line/" + ip + " > geoinfo.txt";
    system(cmd.c_str());

    ifstream infile("geoinfo.txt");
    string country, region, city;
    getline(infile, country); // country
    getline(infile, region);  // region
    getline(infile, city);    // city
    infile.close();

    stringstream ss;
    ss << "Country: " << country << ", Region: " << region << ", City: " << city;
    return ss.str();
}
bool isValidIP(const string& ip) {
    int dots = 0;
    size_t start = 0, end;
    while ((end = ip.find('.', start)) != string::npos) {
        string part = ip.substr(start, end - start);
        if (part.empty() || part.size() > 3) return false;
        for (size_t j = 0; j < part.size(); j++)
            if (!isdigit(part[j])) return false;

        int num;
        stringstream ss(part); ss >> num;

        if (num < 0 || num > 255) return false;
        start = end + 1;
        dots++;
    }
    // Last part
    string part = ip.substr(start);
    if (part.empty() || part.size() > 3) return false;
    for (size_t j = 0; j < part.size(); j++)
        if (!isdigit(part[j])) return false;

    int num;
    stringstream ss(part); ss >> num;
    if (num < 0 || num > 255) return false;
    return dots == 3;
}

int main() {
    string userID, password, inputIP, txnID;

    cout << "Enter User ID: ";
    cin >> userID;
    cout << "Enter Password: ";
    cin >> password;

    if (!authenticateUser(userID, password)) {
        cout << "Invalid user credentials!\n";
        logFraud(userID, "Invalid Credentials");
        return 1;
    }

    vector<string> trustedIPs = loadTrustedIPs(userID);
    if (trustedIPs.empty()) {
        cout << "No trusted IPs found. Transaction blocked.\n";
        logFraud(userID, "No Trusted IPs Configured");
        return 1;
    }

    cout << "Enter IP Address: ";
    cin >> inputIP;
    inputIP = trim(inputIP);  // Trim the input IP before comparing

    if (isSuspiciousIP(inputIP, trustedIPs)) {
        cout << "Suspicious IP detected! Transaction blocked.\n";
        logFraud(userID, "Suspicious IP", inputIP);
        return 1;
    } else {
        cout << "? IP is trusted.\n";
    }

    cout << "Enter Transaction ID: ";
    cin >> txnID;

    if (!isValidTxnID(txnID)) {
        cout << "Invalid Transaction ID! Transaction blocked.\n";
        logFraud(userID, "Invalid Transaction ID", inputIP, txnID);
        return 1;
    }

    cout << "Transaction successful and secure.\n";
    logSuccess(userID, inputIP, txnID);

    return 0;
}
