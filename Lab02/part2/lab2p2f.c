#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {

    printf("Be patient, the program will take around 7 seconds to run.\n");
    printf("At the end you can do \"cat results.out\" to see the result.\n");

    //
    // Add code here to pipe from ./slow 5 to ./talk and redirect
    // output of ./talk to results.out
    // I.e. your program should do the equivalent of ./slow 5 | talk > results.out
    // WITHOUT using | and > from the shell.
    //
    int p[2];
    char slowout[128]

    if(pipe(p) < 0)
      perror("lab2p2f:");

    //send output from slow 
    if (fork() == 0) {
      dup2(p[0], STDOUT_FILENO);
      close(p[0]);
      close(p[1]);
      execlp("./slow","5", NULL);
    } else {
      char buffer[128];
      int fp_in = open("./slow.out", O_RDONLY);
      int fp_out = open("./talk.out", O_CREAT | O_WRONLY);

      if(fork() == 0){

    }

}

