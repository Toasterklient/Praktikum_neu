//============================================================================
// Name        : INF3_Prak.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

//Token: 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

#include <string>
#include <iostream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <unistd.h>

#include "SHA256.H"
#include "TASK1.H"

using namespace std;
using namespace TASK1;


int main(){

	//demoTASK1_00();
	srand(time(nullptr));
	//demoTASK1_01();


	/*ConcreteObserver o1;
	ConcreteObserver o2;
	ConcreteObserver o3;

	ConcreteSubject subject;


	//dem Subject dem Observer uebergeben
	subject.attach(&o1);						//o ist jetzt abonent von Subject
	subject.attach(&o2);
	subject.attach(&o3);


	//dem Observer das Subject übergeben
	o1.setSubject(&subject);					//Ausgabe vom Observer
	o2.setSubject(&subject);
	o3.setSubject(&subject);

		//erste Datenaenderung des Subjects
		subject.setState("Hello World!");

		//Zweite Datenaenderung des Subjects
		subject.setState("New Data");*/


    return 0;
}





