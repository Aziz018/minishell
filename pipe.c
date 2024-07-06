# include <stdio.h>
# include <unistd.h>

int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("error in pipe function");
        return (1);
    }

    int pid = fork();
    

    return (0);
}