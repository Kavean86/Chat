#pragma once
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <algorithm>
#include <unistd.h>
using namespace std;

// Secret key used for generating the HMAC.
// // Both client and server must know this secret.
const string secret="$198drt5h4205#6%4@26*28$";
// Generate an HMAC-SHA256 digest for the given message
// // using the provided secret key.
string hmac_sha256(const string& secret, const string& message)
{
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_length = 0;
	 // Calculate HMAC using SHA-256.
	 //     //
	 //         // secret.c_str()  -> HMAC secret key
	 //             // secret.size()   -> length of the secret key
	 //                 // message.c_str()-> message to authenticate
	 //                     // message.size()  -> length of the message
	 //                         // hash             -> output buffer
	 //                             // hash_length      -> receives the output length
	HMAC(
			EVP_sha256(),secret.c_str(),secret.size(),reinterpret_cast<const unsigned char*>(message.c_str()),message.size(),hash,&hash_length);
	stringstream result;
	for (unsigned int i = 0; i < hash_length; i++)
	{
		result << hex<< setw(2)<< setfill('0')<< static_cast<int>(hash[i]);
	}
	return result.str();
}

// Perform the initial authentication/check between client and server.
void check(int csock){
	char buffer[64]={0};
	recv(csock,buffer,sizeof(buffer),0);
	string response = hmac_sha256(secret, buffer);
	send(csock,response.c_str(),response.size(),0);
}

// Handle SIGINT (Ctrl+C).
void signalHandler(int signal)
{
if(signal == SIGINT)
{
cerr << "\033[33m\nCtrl+C is not allowed!for exit enter EXIT\n\033[35m";
}
}
// Continuously receive messages from the server.
void autorecv(int sock){
char buffer[4024]={0};
while(true){
memset(buffer,0,sizeof(buffer));
int bytes=recv(sock,buffer,sizeof(buffer),0);
if(bytes==0){
return;
break;
}
if(bytes<=0){
perror("recv");
break;
}
cout.write(buffer,bytes);
// Immediately flush the output so the message
// appears without waiting for the stream buffer.
cout.flush();
}
}
