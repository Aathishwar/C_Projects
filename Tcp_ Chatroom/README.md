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
###📥 Clone the Repository
```bash
git clone https://github.com/your-username/tcp-chat-room.git
cd Tcp_Charroom
```
###🧪 Compile the Code (in seperate terminals)
```bash
gcc server.c -o server
gcc client.c -o client
```
###🖥️ Usage
####1️⃣ Start the Server
```bash
./server
```
  Server will start listening on port 8080.

####2️⃣ Start One or More Clients (in new terminals)
```bash
./client
```
  Enter your username when prompted and start chatting!
