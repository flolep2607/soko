#include <termios.h>
#include <unistd.h> 
#include <stdbool.h>
#include <stdio.h>

#define MAXSIZE 10 

int resetTerminal()
{
	struct termios new;
	if (tcgetattr(0,&new)==-1) {
      		perror("tcgetattr");
		return -1;
    	}
	new.c_lflag |= ICANON; // Met le terminal en mode canonique.
	new.c_lflag |= ECHO;   // les touches tapées ne s'inscriront plus dans le terminal
	new.c_cc[VMIN]=1;
	new.c_cc[VTIME]=0;
	if (tcsetattr(0,TCSANOW,&new)==-1) {
      		perror("tcsetattr");
		return false;
    	}
	return true;
}

int configureTerminal()
{
	struct termios new;
	if (tcgetattr(0,&new)==-1) {
      		perror("tcgetattr");
		return -1;
    	}
	new.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	new.c_lflag &= ~(ECHO);   // les touches tapées ne s'inscriront plus dans le terminal
	new.c_cc[VMIN]=1;
	new.c_cc[VTIME]=0;
	if (tcsetattr(0,TCSANOW,&new)==-1) {
      		perror("tcsetattr");
		return false;
    	}
	return true;
}

int litClavier() 
{
	char r[MAXSIZE];
	int c;  

	if ((c=read(0,r,3)) == - 1 ) return false; 

	switch (r[0]) {
		case 27 :  if ((c==3) && (r[1]==91)) return (r[2]-64); else return false; break; 
		default: return r[0]; break; 
	}
}

