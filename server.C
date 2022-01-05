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
#include "TASK1.H"
#include "TASK1.C"
#include "SHA256.H"
#include "SHA256.C"

using namespace std;



class MyServer : public TCPserver {
public:
	MyServer(int portNmb, int maxDataRecv) : TCPserver (portNmb,maxDataRecv){;};	//Aufruf von constructor elternklasse


protected:
	string myResponse(string input); //deklaration


};

class MyBlackBoxSafe : public TASK1::BlackBoxSafe{
public:
	MyBlackBoxSafe(int pwdLength, int symbSetSize) : TASK1::BlackBoxSafe(pwdLength, symbSetSize){;};
	virtual string input(string strPwd){return string("undefined");};


protected:
	string randomPwd (int l);
	string pwd_;

};


int main(){

	srand(time(nullptr));
	MyServer srv(2023,25);
	srv.run();
}


string MyServer::myResponse(string input){
	int lPwd[2];
	int zPwd[2];
	char tPwd [50];
	char newPwd [50];

	if (input.compare(0,10, "getSymbols") == 0){

		return string("ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789");
	}else if(input.compare(0,6, "newPwd" )== 0){
		//newPwd(int,int), länge und anzahl der verwendeten zeichen
		//fgets()
			//printf("%i,%i", lPwd, zPwd);

			//if(res !=2) return ("ERROR");
			return string("OK");
	}else if(input.compare(0,6, "tryPwd") == 0){

		/*sscanf("tryPwd(%49s)", &tPwd[0]);
			if(tPwd ==newPwd) return ("Richtig");*/

		return string("OK");

	}else{
		return string ("ERROR");
	}

}


//BlackBoxSave
string MyBlackBoxSafe::randomPwd (int l){
	int symbolIdx;
		if(l < TASK1::MINIMAL_PWD_LENGTH){ l = TASK1::MINIMAL_PWD_LENGTH;};
		pwd_ = string("");
		for(int i=0; i < l; i++){
			symbolIdx = rand() % lengthSymbArray_;
			pwd_ +=  charSymbArray_[symbolIdx];
		}
		return sha256(pwd_);
}




