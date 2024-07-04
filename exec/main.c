#include "../libraries/minishell.h"

void    ft_pipe(t_command *node1, char **ev, t_pipex *p)
{
    //pid_t pid;
    //int status;
    t_command *cur = node1;
    p->flag = 0;
    if (p->count_here_doc > 0)
        open_here_doc(node1, p);
    while (cur != NULL)
    {
        if (cur->type == PIPE || cur->type == RED_IN || cur->type == HER_DOC)
        {
            if (cur->type == RED_IN)
                p->flag = 1;
            cur = cur->next;
        }
        else if (cur->type != RED_OUT && cur->type == CMD)
        {
            if (ft_strcmp(cur->args[0], "cat") == 0 && cur->next->type == HER_DOC)
            {
                printf("flag == 2\n");
                p->flag = 2;
            }
            fork_pipe(cur, ev, p);
            //waitpid(pid, &status, 0);
            p->flag = 0;
            cur = cur->next;
        }
        else
            cur = cur->next;
    }
}

int func(t_command *list)
{
    t_pipex	pipex;

    ft_count_pipe(list, &pipex);
    // printf("count_pipe = %d\n",pipex.count_pipe);
    ft_count_read_out(list, &pipex);
    ft_count_read_in(list, &pipex);
    ft_count_here_doc(list, &pipex);
    if (pipex.count_read_in)
        open_infile(list, &pipex);
    if (pipex.count_read_out)
        open_outfile(list, &pipex);
    //open_herdoc(node1, &pipex);
    if (pipex.count_pipe == 0 && pipex.count_read_out == 0)
    {
        if (pipex.count_here_doc == 0 && pipex.count_read_in == 0)
        {
            int pp = fork();
            if (pp == 0)
                ft_excute(list->args, data->envirenment);
            else if (pp > 0)
                wait(NULL);
        }
        else if (pipex.count_here_doc == 0 && pipex.count_read_in != 0)
        {
            printf("rin\n");
            while (list)
            {
                if (list->type == RED_IN)
                    list = list->next;
                else
                    break;
            }
            int pp = fork();
            if (pp == 0)
            {
                dup2(pipex.infile, 0);
                close(pipex.infile);
                ft_excute(list->args, data->envirenment);
            }
            else
                wait(NULL);
        }
        else
        {
            printf("not\n");
            open_here_doc(list, &pipex);
            pipex.infile_here_doc = open("file_here_doc.txt", O_RDONLY, 0644);
            dup2(pipex.infile_here_doc, 0);
            close(pipex.infile_here_doc);
            ft_excute(list->args, data->envirenment);
            // unlink("file_here_doc.txt");
            //wait(NULL);
        }

    }
    else if (pipex.count_pipe == 0 && pipex.count_read_out != 0)
    {
        if (pipex.count_here_doc != 0)
        {
            open_here_doc(list, &pipex);
            ft_onecmd(list, data->envirenment, &pipex);
           // wait(NULL);
            unlink("file_here_doc.txt");
        }
        else
        {
            int pid = fork();
            if (pid == 0)
                ft_onecmd(list, data->envirenment, &pipex);
            else
                wait(NULL);
        }
    }
    else
    {
        printf("existing pipe\n");
            // int pid = fork();
            // if (pid == 0)
        ft_pipe(list, data->envirenment, &pipex);
            // else
            //     wait(NULL);
    }
    return (0);
}



    // t_command *node1 = malloc(sizeof(t_command));
    // node1->type = CMD;
    // node1->args =(char *[]){"cat", NULL};
    // node1->next = NULL;
    // t_command *node2 = malloc(sizeof(t_command));
    // node2->type = HER_DOC;
    // node2->args =(char *[]){"lop", NULL};
    // node1->next = node2;
    // t_command *node3 = malloc(sizeof(t_command));
    // node3->type = PIPE;
    // node3->args = NULL;
    // // node3->args = NULL;
    // node1->next->next = node3;
    // t_command *node4 = malloc(sizeof(t_command));
    // node4->type = CMD;
    // node4->args = (char *[]){"grep", "l", NULL};
    // node1->next->next->next = node4;

//  ls | grep f | wc -l
// int main(int ac, char **av, char **ev)
// {
//     (void)ac;
//     (void)av;
    
    // t_command *node6 = malloc(sizeof(t_command));
    // node6->type = PIPE;
    // node6->args = NULL;
    // list->next->next->next->next->next = node6;
    // t_command *node7 = malloc(sizeof(t_command));
    // node7->type = CMD;
    // node7->args =  (char *[]) {"wc", "-l", NULL};
    // node1->next->next->next->next->next->next = node7;
    // t_command *node8 = malloc(sizeof(t_command));
    // node8->type = CMD;
    // node8->args = (char *[]){"wc", NULL};
    // node1->next->next->next->next->next->next->next = node8;
    // t_command *node9 = malloc(sizeof(t_command));
    // node9->type = RED_OUT;
    // node9->args = (char *[]){"y.txt", NULL};
    // node1->next->next->next->next->next->next->next->next = node9;
    // t_command *node10 = malloc(sizeof(t_command));
    // node10->type = RED_OUT;
    // node10->args = (char *[]){"x.txt", NULL};
    // node1->next->next->next->next->next->next->next->next->next = node10;


    

// }