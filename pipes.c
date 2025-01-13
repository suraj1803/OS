#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main() {
  int pipefds[2]; // Array to hold the file descriptors for the pipe
  pid_t pid;
  char write_msg[] = "Hello from parent!";
  char read_msg[100];

  // Create the pipe
  if (pipe(pipefds) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // Fork the process
  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    // Child process
    close(pipefds[1]); // Close unused write end of the pipe

    // Read message from the pipe
    read(pipefds[0], read_msg, sizeof(read_msg));
    printf("Child received: %s\n", read_msg);

    close(pipefds[0]); // Close the read end after use
  } else {
    // Parent process
    close(pipefds[0]); // Close unused read end of the pipe

    // Write message to the pipe
    write(pipefds[1], write_msg, strlen(write_msg) + 1);
    close(pipefds[1]); // Close the write end after use

    // Wait for the child to finish (optional)
    wait(NULL);
  }

  return 0;
}

