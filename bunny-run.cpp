
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <ctype.h>
#include <math.h> 

//escape code to clear terminals
#define clear() printf("\033[H\033[J")


using namespace std;



void printBunny(unsigned int pulses){

	//unsigned int pulses = 1000000;

	string line;
	ifstream bunnyfile1("bunny1.txt");
	ifstream bunnyfile2("bunny2.txt");

	cout << endl << endl << endl;
	
	int speed = ceil(582200/(pulses-37800));

	stringstream buf;
	buf << "bunnysay speed is " << speed;
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

void processBuf(unsigned int &pulses, unsigned int &lastpulses, char buf[10]){

	int num;

	if(isdigit(buf[0])){
			num = atoi(buf);
			//cout << "num is " << num;
	}

	if (num < 50 || num > 1000){
		pulses = lastpulses;		
	}

	else{
		pulses = num*800;
		lastpulses = pulses;
	}

}

void getPulses(unsigned int &pulses, unsigned int &lastpulses, int fd){
 	
	char buf[10];

		string response;
		int n = read(fd, buf, sizeof buf);

	if(n>0){
		usleep(1000);
		processBuf(pulses, lastpulses, buf);
	}
	
    else{
    	pulses = lastpulses;
    }	


	memset(buf, 0, sizeof buf);
	//tcflush(fd, TCIOFLUSH);

 }

void *getAndPrint(void *id){
	unsigned int pulses = 616000;
	unsigned int lastpulses = 616000;

	int fd = open("/dev/cu.usbmodem1411", O_RDWR | O_NOCTTY | O_NDELAY);

	do{
		getPulses(pulses, lastpulses, fd);

		if(pulses <= 0){
			throw "you can't have negative pulses!";
		}

		printBunny(pulses);
	}while(true);

    close(fd);

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
	
	cout << endl;
	clear();
	cout << endl;
	system("bunnysay welcome to bunny resistor simulator 2000");
	system("sleep 4");
	cout << endl;
	clear();
	cout << endl;
	system("bunnysay press enter to continue");	
	system("sleep 4");
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