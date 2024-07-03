#include "../libraries/minishell.h"

void    ft_count_here_doc(t_command *node, t_pipex *p)
{
    t_command *cur = node;

    p->count_here_doc = 0;
    while (cur != NULL)
    {
        if (cur->type == HER_DOC)
            p->count_here_doc++;
        cur = cur->next;
    }
}



// void	here_doc(t_command *node, t_pipex *pipex)
// {
//     int status;
//     write(1, "> ", 2);
//     pipe(pipex->end);
//     pid_t pid;
//     pid = fork();
//     if (pid == 0)
//     {
//         close(pipex->end[0]);
//         pipex->line = get_next_line(0);
//         char *str = ft_strjoin(node->args[0], "\n");
//         while (pipex->line != NULL && ft_strcmp(str, pipex->line) != 0)
//         {
//             write(pipex->end[1], pipex->line, ft_strlen(pipex->line));
//             write(1, "> ", 2);
//             pipex->line = get_next_line(0);
//         }
//     }
//     close(pipex->end[1]);
//     dup2(pipex->end[0], 0);
//     close(pipex->end[0]);
//     waitpid(pid, &status, 0);
// }

void	here_doc_error(char **av)
{
	ft_putstr_fd("\nbash: warning: here-document at line \
	1 delimited by end-of-file wanted ", 2);
	ft_putstr_fd(av[0], 2);
	write(2, "\n", 1);
	exit(0);
	unlink("file_here_doc.txt");
}

void	here_doc(t_command *node, t_pipex *pipex)
{
	char	*str;

	write(1, "> ", 2);
	pipex->line = get_next_line(0);
	pipex->infile_here_doc = open("file_here_doc.txt", O_RDWR | O_CREAT | O_TRUNC , 0644);
	str = ft_strjoin(node->args[0], "\n");
	if (pipex->line[0] == '\0')
		here_doc_error(node->args);
	while (pipex->line != NULL && ft_strcmp(pipex->line, str) != 0)
	{
		write(pipex->infile_here_doc, pipex->line, ft_strlen(pipex->line));
		write(1, "> ", 2);
		free(pipex->line);
		pipex->line = get_next_line(0);
		if (pipex->line[0] == '\0')
			here_doc_error(node->args);
	}
	free(pipex->line);
	free(str);
}
void	open_here_doc(t_command *node, t_pipex *pipex)
{
    t_command *cur = node;
    printf("count_here_doc == %d\n", pipex->count_here_doc);
    while (cur != NULL)
    {
        if (cur->type == HER_DOC)
            here_doc(cur, pipex);
        cur = cur->next;
    }
}