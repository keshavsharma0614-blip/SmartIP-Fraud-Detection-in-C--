*SmartIP Fraud Detection System in C++


A simple fraud detection system written in C++ that validates user credentials, checks IP addresses, and logs secure or suspicious transactions using file-based storage.

*Features


User authentication (ID & password verified from file)

IP address validation and trusted IPs management

Transaction ID validation

Logs for both valid and suspicious transactions

Geolocation reading from geoInfo.txt

Simple command-line interface

*Files Included


Fraud_Detection_system.cpp – Main C++ source file

users.txt – Sample user credentials

known_ips.txt – Trusted IP addresses

trans.txt – Valid transaction IDs

geoInfo.txt – Location info (country, region, city)

success_log.txt – Logs of valid (secure) transactions

fraud_log.txt – Logs of suspicious/fraud attempts

*How to Run


Open the project in Dev C++ or any standard C++ IDE.

Ensure all .txt files are placed in the same directory as the .cpp file.

Compile and run the program.

Follow command-line prompts to enter User ID, Password, IP address, and Transaction ID.

*How It Works


The system checks the entered User ID and Password (users.txt).

Validates that the given IP exists in the user’s trusted IP list (known_ips.txt).

Transaction ID is checked in trans.txt.

Location info is fetched from geoInfo.txt.

All successful and suspicious activities are logged separately.

*Contribution


Pull requests are welcome! For suggestions or issues, please open an issue on this repo.
