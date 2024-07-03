#ifndef MAIN_H
#define MAIN_H

// typedef struct s_pipex
// {
// 	int		end[2];
// 	int		status;
// 	int		status_1;
// 	int		i;
// 	int		indixe;
// 	int		outfile;
// 	int		infile;
// 	int		infile_here_doc;
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	pid_t	a[2];
// 	char	*line;
// 	pid_t	pid;
// 	int		fd;
// 	int		save1;
// 	pid_t	r;
// 	int		count_read_out;
// 	int		count_read_in;
// 	int		count_pipe;
// 	int		count_here_doc;
// 	int		flag;
// }			t_pipex;


// typedef struct s_path
// {
// 	char	*path_from_envp;
// 	char	**mypaths;
// 	char	*part_path;
// 	char	*path;
// 	int		i;
// }			t_path;
// link_list



// int	ft_lstsize(t_command *lst);
// t_command	*ft_lstlast(t_command *lst);




//excut

// void	ft_excute(char **av, char **env);
// char	*search_path(char *mycmdargs, char **env);
// char	*without_slash(char **env, char *mycmdargs);
// char	*slash(char *mycmdargs);
// char	*function(char **env);


// error
// void	ft_putstr_fd(char *s, int fd);
// void	ft_error_2(void);
// void	ft_error(char *av);
// char	*ft_strchr(const char *s, int c);
// int	ft_strcmp(char *s1, char *s2);

// open_file

// void    ft_count_pipe(t_command *list, t_pipex *p);
// void    ft_count_read_out(t_command *node, t_pipex *p);
// void    ft_count_read_in(t_command *node, t_pipex *p);
// void    open_infile(t_command *node, t_pipex *p);
// void    open_outfile(t_command *node, t_pipex *p);

// allcmd

// void	fork_pipe(t_command *node1, char **env, t_pipex *p);

// one_cmd

// void    ft_onecmd(t_command *node, char **ev, t_pipex *p);
// void    ft_onecmd_her(t_command *node, char **ev, t_pipex *p);


// here_doc

// void	open_here_doc(t_command *node, t_pipex *pipex);
// void	here_doc(t_command *node, t_pipex *pipex);
// void    ft_count_here_doc(t_command *node, t_pipex *p);

// void    	ft_pipe(t_command *node1, char **ev, t_pipex *p);
// int 		func(t_command *list);

#endif
