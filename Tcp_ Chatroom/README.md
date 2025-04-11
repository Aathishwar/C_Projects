# 🗨️ Encrypted Multi-Client TCP Chat Room with Color-Coded Usernames

A Linux-based terminal chat application written in C using TCP sockets. It supports multiple clients, real-time messaging, XOR-based encryption, and beautiful color-coded usernames for improved readability.

---

## 🚀 Features

- ✅ Multi-client support using `select()` system call (no threads on server)
- ✅ Real-time messaging with non-blocking input (client-side threading)
- 🎨 Unique color-coded usernames for easy identification
- 🔐 Lightweight XOR encryption to obfuscate messages
- 🖥️ Clean terminal interface with colored messages
- ⚙️ Works on any Unix/Linux system (tested on Kali Linux)

---

## 🧠 Concepts Covered

- TCP socket programming
- Concurrency with `select()` and `pthread`
- Basic encryption techniques (XOR cipher)
- ANSI escape sequences for terminal colors
- Client-server architecture

---

## 🛠️ Setup Instructions

### 🔧 Install GCC & Git (Linux)

```bash
sudo apt update
sudo apt install build-essential git
```
### 📥 Clone the Repository
```bash
git clone https://github.com/your-username/tcp-chat-room.git
cd Tcp_Charroom
```
### 🧪 Compile the Code (in seperate terminals)
```bash
gcc server.c -o server
gcc client.c -o client
```
### 🖥️ Usage
- 1️⃣ Start the Server
```bash
./server
```
  Server will start listening on port 8080.

- 2️⃣ Start One or More Clients (in new terminals)
```bash
./client
```
Enter your username when prompted and start chatting!

---
## 🔐 About the Encryption
This project uses a simple XOR cipher with a shared key (0x5A) to encrypt and decrypt all messages transmitted between clients and server.
This is not secure encryption, but it demonstrates:
- How to obfuscate messages in transit
- Shared-key symmetric encryption flow
---

## 🎨 Terminal Colors
Each user is assigned a unique color from a predefined set using ANSI escape codes.

- Color	Meaning
- 🔴 Red	    User 1
- 🟢 Green	  User 2
- 🔵 Blue   	User 3
- 🟡 Yellow	  User 4
- 🟣 Magenta	User 5
- 🟦 Cyan	    User 6
- Colors wrap around once all are used.

---
## 📸 Preview
```rust
[🟢 Alice] Hey there!
[🔵 Bob] Hi Alice!
[🟡 Carol] What's up everyone?
```
---
## 🧩 Future Enhancements
- 🔒 Upgrade to AES encryption using OpenSSL
- 📬 Private messaging (/msg command)
- 📝 Chat history logging
- 🖼️ GUI interface using ncurses or GTK
- 🔗 File sharing (via TCP stream)
---
