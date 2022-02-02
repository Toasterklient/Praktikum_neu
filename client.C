/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream>

#include "TASK1.H"
#include "SIMPLESOCKET.H"

using namespace std;

string randomPwd(int pwdL, int alphaL);

string myResponse(string input);

int main(int argc, char * argv[]) {

    srand(time(NULL));
    TCPclient c;

    string host = "localhost";
    string msg1;
    string msg2;

    //connect to host
    c.conn(host , 2023);

    int runs;
    int pwdL;
    int alphaL;
    string recive;



    if(argc != 4) {   // Pruefung, ob nur 2 Kommandozeilenparameter gegeben sind
        cout << "Fehlende oder zu viel Kommandozeilenparameter." << endl;
        return 0;
    }



    // Passwordlaenge
    sscanf(argv[1],"%i",&pwdL);
    //Alphabetlaenge
    sscanf(argv[2], "%i", &alphaL);
    // read anzahl laeufe
    sscanf(argv[3],"%i",&runs);


    //überprüfung der Passwortparameter
    if (pwdL < 3){   //Passwortlaenge
    	cout << "Passwortlaenge ist zu gering mind. 3 erforderlich" << endl;
        return 0;
    }

    if (alphaL < 2){   //Alphabetlaenge
        cout << "Alphabetlaenge zu gering, mind. 2 erforderlich" << endl;
        return 0;
    }

    //Ausgabe der Passwort-,Alphabetlaenge und der Anzahl der Versuche
    cout << "Passwortlaenge: " << pwdL << " | Alphabetlaenge: "  << alphaL << " | Versuche: " << runs << endl;



    stringstream ss1;
    ss1<< "newPwd(" << pwdL << "," << alphaL << ")" << "\n";
    msg1 = ss1.str();


    for (int i = 0; i<runs; i ++){

    	//cout << "client msg:" << msg << "\n";

    	c.sendData(msg1);
    	recive = c.receive(32);
    	cout << "server: " << msg1 << endl;

    	int counter = 0;
    	while(1){
    		stringstream ss2;
    		counter ++;

    		//Rate Pwd
    		string randPwd = randomPwd(pwdL, alphaL);

    		ss2 << "tryPwd(" << randPwd << ")";
    		msg2 = ss2.str();
    		c.sendData(msg2);
    		msg2 = c.receive(32);

    		if(msg2.compare(0,15, string("ACCESS ACCEPTED")) == 0){
    			//cout << "client msg: " <<msg2 << "\n";
    			break;
    		}
    	}
    	cout << counter <<"\n";

    }


}


string randomPwd(int pwdL, int alphaL){
	int symbolIdx;
	string pwd;
	if(pwdL < TASK1::MINIMAL_PWD_LENGTH){ pwdL = TASK1::MINIMAL_PWD_LENGTH;};
	pwd= string("");
	for(int i=0; i < pwdL; i++){
		symbolIdx = rand() % alphaL;
		pwd += TASK1::SYMBOLS[symbolIdx];
	}
	return pwd;
}
