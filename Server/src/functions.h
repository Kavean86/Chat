#pragma once
using namespace std;


const string SECRET = "$198drt5h4205#6%4@26*28$";

string hmac_sha256(const string& secret, const string& message)
{
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_length = 0;
	HMAC(
			EVP_sha256(),secret.c_str(),secret.size(),reinterpret_cast<const unsigned char*>(message.c_str()),message.size(),hash,&hash_length);
	stringstream result;
	for (unsigned int i = 0; i < hash_length; i++)
	{
		result << hex<< setw(2)<< setfill('0')<< static_cast<int>(hash[i]);
	}
	return result.str();
}
string generate_challenge()
{
	random_device rd;
	uint64_t challenge =(static_cast<uint64_t>(rd()) << 32) |rd();
	return to_string(challenge);
}
void check(int csock)
{
// Generate random challenge
string challenge = generate_challenge();
//Send challenge to client
send(csock,challenge.c_str(),challenge.size(),0);
//Receive client's HMAC response
char buffer[65] = {0};
int bytes = recv(csock,buffer,64,0);
if (bytes <= 0)
{
cout << "Client disconnected during authentication.\n";
return;
}
string response(buffer, bytes);
//Server calculates the expected response
string expected =
hmac_sha256(SECRET, challenge);
//Compare
if (response == expected)
{
cout << "Authentication successful!\n";
}else{
cout << "Authentication failed!\n";
string error_message="Your connection is not valid";
send(csock,error_message.c_str(),error_message.size(),0);
close(csock);
}
}
 
/*
 * Chat Server Function Declarations
 * Contains declarations of functions used by the chat server.
 */

// Sends a message to all connected clients except the sender
// // Used for broadcasting chat messages and notifications
void broadcast(int main_socket,vector<int>&vectorsocket,string message){
for (int client : vectorsocket)
{
if (client != main_socket)
{
send(client, message.c_str(), message.size(), 0);
}
}
}

// Returns the current local time as a formatted string
// // Used to add timestamps to chat messages
string getTime()
{
time_t now = time(0);
tm *local = localtime(&now);
char buffer_time[80];
strftime(buffer_time, sizeof(buffer_time), "%H:%M:%S", local);
return string(buffer_time);
}
// Store connected users and their socket descriptors
vector<string> vectoruser;
vector<int> userssocket;
// Protect shared user data when accessed by multiple threads
mutex user_mutex;
/*
 * Handles communication with a connected client. 
 *   Responsibilities:
 * - Check username availability
 * - Add client to active users list
 * - Receive and process client messages
 * - Handle chat commands
 * - Remove disconnected users
 */
int handle(int main_socket,string name){
string server_message2=YELLOW+"you exited.."+RESET;
string server_message3=RED+"User already exists"+PURPLE;
{
// Check if username already exists before adding the client
lock_guard<mutex> lock(user_mutex);
if(find(vectoruser.begin(), vectoruser.end(), name) != vectoruser.end())
{
send(main_socket, server_message3.c_str(), server_message3.size(), 0);
close(main_socket);
return 1;
}
else
{
string join_message=YELLOW+name+" joined...\n"+PURPLE;
cout<<join_message;
vectoruser.push_back(name);
userssocket.push_back(main_socket);
broadcast(main_socket,userssocket,join_message);
}
}
char buffer[1024]={0};
while(true){
memset(buffer,0,sizeof(buffer));
int bytes=recv(main_socket,buffer,sizeof(buffer),0);
if(bytes<=0){
if(bytes == 0){
cout << "Client disconnected: " << name << endl;
}
else{
perror("recv");
}
{
lock_guard<mutex> lock(user_mutex);
vectoruser.erase(remove(vectoruser.begin(), vectoruser.end(), name),vectoruser.end());
userssocket.erase(remove(userssocket.begin(), userssocket.end(), main_socket),userssocket.end());
}
close(main_socket);
return 0;
}

string message(buffer,bytes);
message.erase(remove(message.begin(), message.end(), '\n'), message.cend());
string time="["+getTime()+"]";

if (message.find_first_not_of(" \t\n\r") ==string::npos) {
continue;
}
// Handle client exit request and remove user from active lists
if(message=="EXIT"){ 
string leave_message=YELLOW+"Leave: "+name+"\n"+PURPLE;
cout<<leave_message;
broadcast(main_socket,userssocket,leave_message);
send(main_socket,server_message2.c_str(),server_message2.size(),0);
{
lock_guard<mutex> lock(user_mutex);
vectoruser.erase(remove(vectoruser.begin(), vectoruser.end(), name),vectoruser.end());
userssocket.erase(remove(userssocket.begin(), userssocket.end(), main_socket),userssocket.end());
}
close(main_socket);
return 0;
}
// Process built-in chat commands
if(message=="HELPMAN"){
send(main_socket,helpman.c_str(),helpman.size(),0);
 continue;
}
if(message=="TIME"){
string TIME=GRAY+time+"\n"+PURPLE;
send(main_socket,TIME.c_str(),TIME.size(),0); 
continue;
}
if(message=="ONLINE"){
for(int i=0;i<vectoruser.size();i++){
string online_users=GRAY+vectoruser[i]+"\n"+PURPLE;
send(main_socket,online_users.c_str(),online_users.size(),0); 
}
 continue;
}
if(message=="CLEAR"){
string clear="\033[2J\033[H";
send(main_socket,clear.c_str(),clear.size(),0);
 continue;
}
// Format and broadcast normal chat messages to other clients
string mes=WHITE+time+name+":"+BLUE+buffer+PURPLE;
cout<<mes;
broadcast(main_socket,userssocket,mes);
}
return 0;
}


