#include "../libraries/minishell.h"

void    ft_count_pipe(t_command *list, t_pipex *p)
{
    t_command *cur = list;
    p->count_pipe = 0;
    while (cur)
    {
        if (cur->type == PIPE)
            p->count_pipe++;
        cur = cur->next;
    }
}

void    ft_count_read_out(t_command *node, t_pipex *p)
{
    t_command *cur = node;
    p->count_read_out = 0;

    while (cur)
    {
        if (cur->type == RED_OUT)
            p->count_read_out++;
        cur = cur->next;
    }
}
void    ft_count_read_in(t_command *node, t_pipex *p)
{
    t_command *cur = node;
    p->count_read_in = 0;

    while (cur)
    {
        if (cur->type == RED_IN)
            p->count_read_in++;
        cur = cur->next;
    }
}

void    open_infile(t_command *node, t_pipex *p)
{
    
    int *fd  = malloc(sizeof(int) * p->count_read_in);
    int i = 0;
    t_command *cur = node;
    printf("count_read_in = %d\n", p->count_read_in);
    while (cur && i < p->count_read_in)
    {
        if (cur->type == RED_IN)
        {
            fd[i] = open(cur->args[0], O_RDONLY, 0644);
            i++;
        }
        cur = cur->next;
    }
    // p->infile = fd[i];
    p->infile = fd[i - 1];
}
void    open_outfile(t_command *node, t_pipex *p)
{
    
    int *fd  = malloc(sizeof(int) * p->count_read_out);
    int i = 0;
    t_command *cur = node;
    printf("count_read_out = %d\n", p->count_read_out);
    while (cur && i < p->count_read_out)
    {
        if (cur->type == RED_OUT)
        {
            fd[i] = open(cur->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            i++;
        }
        cur = cur->next;
    }
    p->outfile = fd[i - 1];
}