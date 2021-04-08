#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0)
    {
        execvp("./sequential_min_max", argv);
    }
    return 0;
}