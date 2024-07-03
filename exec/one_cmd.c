#include "../libraries/minishell.h"

void    ft_onecmd(t_command *node, char **ev, t_pipex *p)
{
    char *buf[1025];
    ssize_t beyt_char;
    pid_t pid;
    int status;
    int flag = 0;
    while (node)
    {
        if (node->type == RED_IN)
        {
            flag = 1;
            node = node->next;
        }
        else
            break;
    }
    pipe(p->end);

    pid = fork();
    if (pid == 0)
    {
        if (p->count_here_doc > 0)
        {
            close(p->end[0]);
            p->infile_here_doc = open("file_here_doc.txt", O_RDONLY, 0644);
            dup2(p->infile_here_doc, STDIN_FILENO);
            close(p->infile_here_doc);
            dup2(p->end[1], STDOUT_FILENO);
            close(p->end[1]);
            ft_excute(node->args, ev);
            //execlp("/usr/bin/cat", "cat", NULL);
            printf("here_doc\n");

        }
        else if (flag == 1)
        {
            printf("flag == 1\n");
            close(p->end[0]);
            dup2(p->infile, STDIN_FILENO);
            close(p->infile);
            dup2(p->end[1], STDOUT_FILENO);
            close(p->end[1]);
            ft_excute(node->args, ev);
        }
        else
        {
            printf("flag == 0\n");
            close(p->end[0]);
            dup2(p->end[1], STDOUT_FILENO);
            close(p->end[1]);
            ft_excute(node->args, ev);
        }
    }
        close(p->end[1]);
        dup2(p->end[0], STDIN_FILENO);
        close(p->end[0]);
        printf("outfile\n");
        while ((beyt_char = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
            write(p->outfile, buf, beyt_char);
        dup2(p->outfile, STDOUT_FILENO);
        close(p->outfile);
        waitpid(pid, &status, 0);
}
