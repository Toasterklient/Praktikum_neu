/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants


#include "SIMPLESOCKET.H"

using namespace std;



/*int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2023);

	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("tryPwd");
			goOn = 0;
		}else{
			msg = string("newPwd(4,6)");
		}
		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);

	}
}*/

string myResponse(string input);

int main(int argc, char * argv[]) {
    srand(time(NULL));
    int runs;
    int pwdL;
    int alphaL;
    string send;
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

    cout << "Passwortlaenge: " << pwdL << " | Alphabetlaenge: "  << alphaL << " | Versuche: " << runs << endl;

    for (int i = 0; i<runs; i ++){
    	send = string ("newPwd");
    	send =
    	cout << "client sends:" << send << endl;
    	recive = myResponse(send);
    }


}
