# 🛡️ SmartIP Fraud Detection System (C++)

A security-focused C++ project that simulates fraud detection by validating user credentials, verifying trusted IP addresses, checking transaction IDs, and logging suspicious or secure activities using file-based storage.

---

## 🚀 Overview

The SmartIP Fraud Detection System enhances transaction security by running multiple validation layers before approving access:

1. User authentication (User ID + Password)
2. Trusted IP address verification
3. Transaction ID validation
4. Geolocation reference
5. Fraud / success logging

---

## ✨ Features

| Feature | Description |
|---|---|
| **User Authentication** | Verifies User ID and Password from `users.txt` |
| **Trusted IP Validation** | Checks IP against trusted addresses in `known_ips.txt` |
| **Transaction Verification** | Validates transaction IDs using `transaction_ids.txt` |
| **Fraud Logging** | Logs suspicious activity to `fraud_log.txt` |
| **Success Logging** | Logs approved transactions to `transaction_success_log.txt` |
| **Geolocation Support** | Reads country, region, and city from `geoInfo.txt` |

---

## 📂 Project Structure

```
SmartIP-Fraud-Detection/
├── smart_ip_fraud_detection.cpp     → Main C++ source code
├── users.txt                        → Sample user credentials
├── known_ips.txt                    → Trusted IP addresses
├── transaction_ids.txt              → Valid transaction IDs
├── geoInfo.txt                      → Location information
├── transaction_success_log.txt      → Successful transaction logs
├── fraud_log.txt                    → Fraud / suspicious activity logs
└── README.md                        → Project documentation
```

---

## ▶️ How to Run

**Option 1 — Dev C++:**
- Open `smart_ip_fraud_detection.cpp` in Dev C++
- Ensure all `.txt` files are in the same project directory
- Compile and Run

**Option 2 — g++ (Terminal):**
```bash
g++ smart_ip_fraud_detection.cpp -o fraud_detection
./fraud_detection
```

---

## 🖥️ Sample Workflow

```
Enter User ID:
Enter Password:
Enter IP Address:
Enter Transaction ID:
```

The system then:
1. Validates credentials against `users.txt`
2. Checks IP against `known_ips.txt`
3. Verifies transaction ID against `transaction_ids.txt`
4. Logs result to either `fraud_log.txt` or `transaction_success_log.txt`

---

## 🧠 Skills Demonstrated

- File handling (`ifstream`, `ofstream`)
- User authentication logic
- IP validation and trust management
- String parsing and sanitization
- Rule-based fraud detection
- Logging systems design
- Real-world security workflow simulation

---

## 🌍 Real-World Applications

This project simulates concepts used in:

- Banking fraud detection systems
- Secure login monitoring
- Transaction verification pipelines
- IP trust management
- Cybersecurity prototypes

---

## 🔮 Future Improvements

- [ ] Password hashing
- [ ] MySQL / Database integration
- [ ] Multi-factor authentication
- [ ] Real-time geolocation API integration
- [ ] Admin dashboard
- [ ] GUI-based interface

---

## 🤝 Contributing

Pull requests are welcome! For suggestions, improvements, or security enhancements, feel free to open an issue.

---

## 👨‍💻 Author

**Keshav Kumar Sharma**  
B.Tech CSE | Full Stack Development | Problem Solver | Open Source Contributor
