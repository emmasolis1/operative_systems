// Author: Emmanuel.
// Code adapted and learned from https://www.geeksforgeeks.org/pipe-system-call/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // Required by MacOS system to use wait().
#define MSGSIZE 20
char* msg1 = "hello, world, Pipe1";
char* msg2 = "hello, world, Pipe2";
char* msg3 = "hello, world, Pipe3";
  
int simple_pipe();
int pipe_with_fork();

int main() {
  int status;
  status = simple_pipe();
  status = pipe_with_fork();

  return status;
}

int simple_pipe() {
  int error;
  printf("Simple pipe of sending message working...\n");

  char inbuf[MSGSIZE];
  int pipe_space[2];

  if (pipe(pipe_space) == -1) {
    error = 1;
  } else {
    // Write into the pipe p[1].

    write(pipe_space[1], msg1, MSGSIZE);
    write(pipe_space[1], msg2, MSGSIZE);
    write(pipe_space[1], msg3, MSGSIZE);

    for (int i = 0; i < 3; i++) {
      // Read from the pipe p[0].
      read(pipe_space[0], inbuf, MSGSIZE);
      printf("% s\n", inbuf);
    }
    error = 0;
  }
  return error;
}

int pipe_with_fork() {
  int error;
  printf("Pipe with fork() implementation working...\n");

  char inbuf[MSGSIZE]; // Where the child process will put the red data.
  int p[2];  // Pipe tunnel
  int pid;  // Process ID
  int red_bytes; // Number of bytes readed for the read() func if successfull

  if(pipe(p) == -1) {
    error = 1;
  } else {
    // Means that was successful and it is the parent.
    if ((pid = fork()) > 0) {
      printf("Parent writing to the child process.\n");
      write(p[1], msg1, MSGSIZE);
      write(p[1], msg2, MSGSIZE);
      write(p[1], msg3, MSGSIZE);

      // If want the program to wait for a change in the status of child process comment next line.
      close(p[1]);
      wait(NULL);
    } else {  // Means that it is the child.
      // If want the program to keep waiting for reading comment next line.
      close(p[1]);
      while ((red_bytes = read(p[0], inbuf, MSGSIZE)) > 0) { // If success the number of red bytes is returned, otherwise will stop.
        printf("% s\n", inbuf);
      }
      if (red_bytes != 0) { // Means it was unsuccessful.
        _exit(2); 
      }
      printf("Child proccess finished reading.\n");
    }
    error = 0;
  }

  return error;
}