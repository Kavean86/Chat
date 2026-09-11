#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <mutex>
#include <csignal>
#include <fstream>
#include <random>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <string>
#include "colors.h"
#include "helpman.h"
#include "functions.h"
using namespace std;

int main(){

string server_message1=YELLOW+"Max len is 10 char\n"+RESET+"Username :"+PURPLE;
string server_message4=RED+"Maximum username length is 12 bytes or enter null."+RESET;
string server_message5=RED+"Username can not empty"+RESET;
string helpman_message=YELLOW+"For help type HELPMAN\n"+PURPLE;
char buffer[12]={0};
// Create TCP socket for accepting client connections
int main_server_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(main_server_socket<0){
perror("socket");
return 1; 
}
// Initialize server socket address
// // AF_INET: IPv4 address family
// // htons(): Convert port number to network byte order
// // INADDR_ANY: Accept connections from any local network interface
sockaddr_in server_fd;
server_fd.sin_family=AF_INET; 
server_fd.sin_port=htons(5000);
server_fd.sin_addr.s_addr=INADDR_ANY;
// Bind the socket to the server address and port
// // This allows the server to receive incoming client connections on port 5000
if(bind(main_server_socket,(sockaddr*)&server_fd,sizeof(server_fd))<0){
perror("bind");
return 1; 
}
// Put the socket into listening mode to accept incoming client connections
// // SOMAXCONN allows the system to choose the maximum pending connection queue size
if(listen(main_server_socket, SOMAXCONN)<0){
perror("listen");
return 1; 
}
// Accept incoming client connections
// // Each accepted client gets a new socket for communication with the server
sockaddr_in client_addr;
socklen_t client_size=sizeof(client_addr);
while(true){
int client_accept=accept(main_server_socket,(sockaddr*)&client_addr,&client_size);
if(client_accept<0){
perror("accept");
return 1; 
}
check(client_accept);
vector<string> users;
// Send welcome message and receive client's username
send(client_accept,server_message1.c_str(),server_message1.size(),0);
int bytes=recv(client_accept,buffer,sizeof(buffer),0);
if(bytes>0){
string username(buffer, bytes);
if (username.find_first_not_of(" \t\n\r") ==string::npos) {
send(client_accept,server_message5.c_str(),server_message5.size(),0); 
close(client_accept);
continue;
}
// Remove newline character from received username
username.erase(remove(username.begin(), username.end(), '\n'),username.cend());
if(bytes>=12){
send(client_accept,server_message4.c_str(),server_message4.size(),0);
shutdown(client_accept, SHUT_RDWR);
close(client_accept);
continue;
}

 // Handle client communication in a separate thread
thread(handle,client_accept,username).detach();
 // Send available commands/help message to the client
send(client_accept,helpman_message.c_str(),helpman_message.size(),0);
}
}
}
