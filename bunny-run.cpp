
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>

//escape code to clear terminals
#define clear() printf("\033[H\033[J")


using namespace std;



void printBunny(unsigned int pulses){

	//unsigned int pulses = 1000000;

	string line;
	ifstream bunnyfile1("bunny1.txt");
	ifstream bunnyfile2("bunny2.txt");

	cout << endl << endl << endl;
	
	stringstream buf;
	buf << "bunnysay speed is " << pulses;
	system(buf.str().c_str());
	//system("sleep 1");
	while (getline(bunnyfile1, line))	
	{
    	istringstream iss(line);
    	cout << line << endl;
	}
    
	usleep(pulses);
    clear();

	cout << endl << endl << endl;

	system(buf.str().c_str());	

	while (getline(bunnyfile2, line))	
	{
    	istringstream iss(line);
    	cout << line << endl;
	}

	usleep(pulses); 
	clear();

}

void getPulses(unsigned int &pulses){
 	
	pulses = pulses - 10000;

 }

void *getAndPrint(void *id){
	unsigned int pulses = 1000000;
	do{
		getPulses(pulses);

		if(pulses <= 0){
			throw "you can't have negative pulses!";
		}

		printBunny(pulses);
	}while(true);

   pthread_exit(NULL);

}


void startup(string s){

	for (int i=0; i<10; i++){
    	clear();
		cout << "###################" << endl << s << endl;

		s = s + ".";
    	clear();
    	system("sleep .2");    
	}
    	system("sleep 1"); 
}

int main(){

char quit = 'q';

	system("bunnysay welcome to bunny servo simulator 2000");
	system("sleep 2");
	clear();

	system("bunnysay press enter to continue");	
	system("sleep 2");
	clear();
//cin enter to continue

	startup("initialising bunnies");

	//GetSerial();

	startup("getting connection");	

   pthread_t thread;

   pthread_create(&thread, NULL, getAndPrint, NULL);

   cin >> quit;

   pthread_cancel(thread);

   cout << "quit " << endl;
	//getSerial(pulses)
	//printBunny(pulses);

	system("bunnysay no bunnies were harmed in the making of this feature");
	system("sleep 2");
	startup("shutting down");
   pthread_exit(NULL);
	clear();

}