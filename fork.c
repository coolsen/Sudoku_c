#include <stdio.h>
long a=0,b,c,i;  //if long 5sec in i loop, if int 8sec
		//maybe the step on eatch others toes 
		//if loop is to small? 
int main(int argc, char*argv[]){
    int pid;
    pid = fork();

    if(pid == 0){       /*child*/

	printf("I am a Child: %d\n", pid);
    }else if(pid > 0){  /*parent*/

	printf("I am  Parent: %d\n", pid);
    }
    for (i=0; i<20000000000;i++) b = a;b = a;b = a;  //do alot of work
}
