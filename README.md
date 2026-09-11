# Chat_V1.0

A simple multi-client chat application written in **C++** using **TCP socket programming**.

The project is designed to demonstrate the fundamentals of network programming, client-server communication, socket programming, and concurrent connections.

## 🚀 Features

* TCP-based client-server communication
* Multi-client support
* Real-time message broadcasting
* Username support
* Concurrent client handling using threads
* Connection and disconnection handling
* Server-side command/help system
* Message timestamps
* Basic error handling
* Linux-compatible socket implementation

## 📁 Project Structure

Chat_V1.0

Chat_V1.0:
Client
LICENSE
README.md
Server

Chat_V1.0/Client:
bin
src

Chat_V1.0/Client/bin:
client

Chat_V1.0/Client/src:
functions.h
main.cpp

Chat_V1.0/Server:
bin
src

Chat_V1.0/Server/bin:
server

Chat_V1.0/Server/src:
colors.h
functions.h
helpman.h
main.cpp

## 🛠️ Technologies

* **C++**
* **TCP/IP**
* **BSD Sockets**
* **POSIX Threads / std::thread**
* **Linux**
* **GCC / G++**

## ⚙️ How It Works

The application follows a basic client-server architecture:

             ┌──────────────┐
             │ Chat Server  │
             │              │
             │ TCP Socket   │
             └──────┬───────┘
                    │
          ┌─────────┼─────────┐
          │         │         │
          ▼         ▼         ▼
      ┌───────┐ ┌───────┐ ┌───────┐
      │Client1│ │Client2│ │Client3│
      └───────┘ └───────┘ └───────┘

The server creates a TCP socket, binds it to an IP address and port, and starts listening for incoming connections.

When a client connects, the server accepts the connection and creates a separate thread to handle that client.

Messages received from one client can then be broadcast to the other connected clients.

## 🔧 Compilation

On Linux, compile the server with:

g++ main.cpp -o server -lcrypto

Then run:

./server

Compile the client similarly:


g++ main.cpp -o client -lcrypto

Then run:

./client

> Make sure the client connects to the correct server IP address and port.

## 🌐 Network Configuration

The server requires:

* Server IP address
* Listening port
* Client IP address
* A reachable network connection between the client and server

For local testing, you can use:

127.0.0.1

For testing between two machines on the same LAN, use the server's local network IP, for example:

192.168.1.100

## 💻 Example

A client can then connect and send messages:

[12:30:15] USERNAME: Hello everyone!

Other connected clients receive the broadcast message.

## 🧠 What I Learned

This project was built as a practical exercise in network programming and helped me understand:

* Socket creation
* `bind()`
* `listen()`
* `accept()`
* `connect()`
* `send()`
* `recv()`
* TCP connections
* Client-server architecture
* Concurrent connections
* Thread synchronization
* Mutexes
* Broadcasting data between clients
* Basic network error handling

## 🔐 Security Notes

This project is intended for **educational purposes**.

The current implementation does not provide strong security features such as:

* TLS/HTTPS encryption
* End-to-end encryption
* Strong authentication
* Password hashing
* Input sanitization
* Rate limiting

Therefore, it should **not be considered production-ready**.

## 🔮 Future Improvements

Planned improvements include:

* [ ] Complete client implementation
* [ ] Better authentication
* [ ] Password hashing
* [ ] Encrypted communication using TLS
* [ ] Private messaging
* [ ] Improved file transfer
* [ ] Better command handling
* [ ] Logging system
* [ ] Improved error handling
* [ ] Graceful server shutdown
* [ ] `select()` / `poll()` / `epoll()` support
* [ ] Improved protocol design
* [ ] Configuration file support

## 📜 License

This project is licensed under the MIT License.

See the `LICENSE` file for more information.

## 👤 Author

**Kaveh Nazem**

This project was created as a practical learning project for **C++ network programming and cybersecurity**.
