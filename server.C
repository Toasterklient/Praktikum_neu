/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"

class MyServer : public TCPserver {
public:
	MyServer(int portNmb, int maxDataRecv) : TCPserver (portNmb,maxDataRecv){;};	//Aufruf von constructor elternklasse

protected:
	string myResponse(string input); //deklaration

};




int main(){

	srand(time(nullptr));
	MyServer srv(2021,25);
	srv.run();
}


string MyServer::myResponse(string input){
	int lPwd;
	int zPwd;
	char tPwd [50];
	char newPwd [50];

	if (input.compare(0,10, "getSymbols") == 0){
		return string("ABCDEFGHIJKLMNOPQRSTUVW");
	}else if(input.compare(0,6, "newPwd") == 0){
		//newPwd(int,int), länge und anzahl der verwendeten zeichen
		int res = sscanf(input.c_str() , "newPwd(%i,%i)", &lPwd, &zPwd);

			if(res !=2) return ("ERROR");
		return string("OK");
	}else if(input.compare(0,6, "tryPwd") == 0){

		/*sscanf("tryPwd(%49s)", &tPwd[0]);
			if(tPwd ==newPwd) return ("Richtig");*/

		return string("Falsch");

	}else{
		return string ("ERROR");
	};

};


