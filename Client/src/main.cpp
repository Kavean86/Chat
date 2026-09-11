#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <csignal>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>
#include <string>
#include "functions.h"
using namespace std;

int main(){
	  // Register the signal handler for SIGINT (Ctrl+C)
signal(SIGINT, signalHandler);
int main_client_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(main_client_socket<0){
perror("socket");
}
sockaddr_in client_fd;
client_fd.sin_family=AF_INET;
client_fd.sin_port=htons(5000);
inet_pton(AF_INET,"127.0.0.1",&client_fd.sin_addr);
if(connect(main_client_socket,(sockaddr*)&client_fd,sizeof(client_fd))<0){
perror("connect");
}
 // Perform additional client-side checks/setup
check(main_client_socket);
  // Start a separate thread to continuously receive messages
  //     // from the server without blocking the main input loop
thread(autorecv,main_client_socket).detach();
while(true){
string send_message;  
getline(cin,send_message);
send_message+="\n";
if(send_message.size()>1024){
cout<<"\033[33mMaximum message length is 1024 bytes.\n\033[35m";
continue;
}
   // Send the message to the server through the TCP socket
send(main_client_socket,send_message.c_str(),send_message.size(),0);
}
}
