#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
  const int SIZE = 4096;
  const char *name = "SURAJ";
  int fd;
  char *ptr;

  fd = shm_open(name, O_RDONLY, 0666);
  if (fd == -1) {
    perror("shm_open");
    return 1;
  }

  ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  printf("Consumer: %s\n", ptr);

  munmap(ptr, SIZE);
  close(fd);
  shm_unlink(name);

  return 0;
}
