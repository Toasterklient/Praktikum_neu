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

class MyBlackBoxSafe : public TASK1::BlackBoxSafe{
public:
	MyBlackBoxSafe(int pwdLength, int symbSetSize) : TASK1::BlackBoxSafe(pwdLength, symbSetSize){;};
	virtual string input(string strPwd);//{return string("undefined");};


protected:
	string randomPwd (int l);
	string pwd_;

};

class MyServer : public TCPserver {
public:
	MyServer(int portNmb, int maxDataRecv) : TCPserver (portNmb,maxDataRecv){;};	//Aufruf von constructor elternklasse


protected:
	string myResponse(string input); //deklaration
	MyBlackBoxSafe *bb_ = nullptr;


};




int main(){

	srand(time(nullptr));
	MyServer srv(2023,25);
	srv.run();
}


string MyServer::myResponse(string input){
	if(input.compare(0,6, "newPwd" )== 0){
			int pwdLeng = 3;
			int alphabetLeng = 5;
			int res;

			res = sscanf(input.c_str(), "newPwd(%i,%i)", &pwdLeng, &alphabetLeng);
			if (res !=2)return string ("ERROR");
			if (pwdLeng < 3) return string ("Passwortlaenge zu gering.");
			if (alphabetLeng < 2) return string ("Alphabetlaenge zu gering.");

			if (bb_ == nullptr){
				bb_ = new MyBlackBoxSafe(pwdLeng, alphabetLeng);
			}else{
				delete bb_;
				bb_ = new MyBlackBoxSafe(pwdLeng, alphabetLeng);
			}
			return string("OK");
	};

	if(input.compare(0,6, "tryPwd") == 0){
		if (bb_ == nullptr) return string ("Bitte erst  neues Passwort generieren.");


		const char *tmpPwdChr = input.c_str();  // Umwandlung string input in ein "array of char"
		        char pwdChr[input.size()];                         // Anlegen eines weiteren "array of char" mit
		                                                                               // der Laenge des String input
		        for(int idx = 0; idx < input.size(); idx++){
		            pwdChr[idx] = '\0';                                     // Initialisierung des arrays mit NULL-Zeichen
		        }                                                                        // Dieses NULL-Zeichen ist das Terminierungszeichen
		                                                                                  // fuer Zeichenketten (arrays of char) in C und C++

		        for(int idx = 7; idx < input.size(); idx++){
		            if(tmpPwdChr[idx] == ')') { break;};         // Kopiere alle Zeichen des arrays tmpPwdChr ab
		            pwdChr[idx-7] = tmpPwdChr[idx];         // Index 7 in das Array pwdChr ab Index 0.
		        }                                                                       // Falls das im Feld tmpPwdChr das Zeichen
		                                                                                 // ')' gelesen wird, wird der Kopiervorgang durch
		                                                                                 // Verlassen der Schleife abgebrochen

		        string pwd =  string(pwdChr);


		cout <<"#"<< pwd <<"#\n";

		return  (bb_-> input(pwd));

	};

	return string ("ERROR");

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


string MyBlackBoxSafe::input(string strPwd){
	if(sha256(strPwd).compare(pwd_) == 0){
		return string("ACCESS ACCEPTED");
	}
	return string("ACCESS DENIED");
}

