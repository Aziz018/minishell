/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:42:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/24 16:18:31 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_minishell(void)
{
	printf("\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███");
	printf("████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══");
	printf("════╝\n");
	printf("\n");
}
void	print_prompt(void)
{
	char	*prompt;
	char	*output_color;
	char	*reset_color;

	prompt = "┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
	output_color = N_GREEN_COLOR;
	reset_color = RESET_COLOR;
	write(1, output_color, ft_strlen(output_color));
	write(1, prompt, ft_strlen(prompt));
	write(1, reset_color, ft_strlen(reset_color));
}

int	exec_command(char *command, t_data *data)
{
	pid_t	pid;
	char	*cmd_path;
	(void) data;
	char **parsedcmd = ft_split(command, ' ');
	if (command == NULL || command[0] == 0)
		return (0);
	cmd_path = ft_strjoin("/bin/", parsedcmd[0]);
	printf("command: %s <||> args: %s\n", parsedcmd[0], parsedcmd[1]);
	if (access(cmd_path, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
			execve(cmd_path, &parsedcmd[1], data->env);
		else
			wait(NULL);
	}
	else
		printf("%s: command not found\n", command);
	free_array(parsedcmd);
	free(cmd_path);
	return (0);
}

void	sig_handler(int signal)
{
	char	*prompt;

	prompt = "\n┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		printf("\n%s", prompt);
}

void	print_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("%s\n", array[i]);
}

int	built_in_cmd(char **parsedcmd, t_data *data)
{
	if (parsedcmd == NULL || parsedcmd[0] == 0)
		return (0);
	else if (!ft_strncmp("exit", parsedcmd[0], ft_strlen(parsedcmd[0])))
		exit(0);
	else if (!ft_strncmp("echo", parsedcmd[0], ft_strlen(parsedcmd[0])))
		echo(parsedcmd);
	else if (!ft_strncmp("pwd", parsedcmd[0], ft_strlen(parsedcmd[0])))
		pwd();
	else if (!ft_strncmp("cd", parsedcmd[0], ft_strlen(parsedcmd[0])))
		cd(parsedcmd[1], data);
	else if (!ft_strncmp("env", parsedcmd[0], ft_strlen(parsedcmd[0])))
		env(data->env);
	else if (!ft_strncmp("export", parsedcmd[0], ft_strlen(parsedcmd[0])))
		export(data, parsedcmd);
	else
		return (0);
	free_array(parsedcmd);
	return (1);
}

int	parse_command(char *command, t_data *data)
{
	char	**parsedcmd;

	(void) data;

	int i = -1;
	int j = -1;
	
	parsedcmd = ft_split(command, ' ');
	
	while(parsedcmd[++i] != NULL)
	{
		j = -1;
		if (i == 0 || ft_strchr("|&;", parsedcmd[i - 1][0]))
			printf("command: ------ %s\n", parsedcmd[i]);
		else if (ft_strchr("<>", parsedcmd[i - 1][0]))
			printf("file: ------ %s\n", parsedcmd[i]);
		else if (ft_strchr("<|&>", parsedcmd[i][0]))
		{
			// parsedcmd[i][0] == '|' || (parsedcmd[i][0] == '&' && parsedcmd[i][1] == '&') || parsedcmd[i][0] == '&' || parsedcmd[i][0] == '<' || parsedcmd[i][0] == '>'
			if (parsedcmd[i][0] == '|')
				printf("pipe: --------- %s\n", parsedcmd[i]);
			else if (parsedcmd[i][0] == '&' && parsedcmd[i][1] == '&')
				printf("and oprt: ----- %s\n", parsedcmd[i]);
			else if (parsedcmd[i][0] == '<')
				printf("red-in: ------- %s\n", parsedcmd[i]);
			else if (parsedcmd[i][0] == '>')
				printf("red-out: ------ %s\n", parsedcmd[i]);
		}
		else
			printf("arg: ---------- %s\n", parsedcmd[i]);

			
		// while(parsedcmd[i][++j])
		// {
		// }
	}
	free_array(parsedcmd);

	
			// cd .. && cat file | grep hello

	// printf("%s\n", command);
	// print_char_array(parsedcmd);

	

	// parsedcmd = ft_split(command, ' ');


	// if (built_in_cmd(parsedcmd, data))
	// 	return (0);
	// free_array(parsedcmd);
	// exec_command(command, data);
	return (0);
}
char	*get_prompt(void)
{
	char	*prompt1;
	char	*prompt2;
	char	*final_prompt;

	prompt1 = "┌──(aziz㉿aelkheta)-["RESET_COLOR;
	prompt2 = getcwd(NULL, 0);
	prompt1 = ft_strjoin(prompt1, prompt2);
	free(prompt2);
	final_prompt = ft_strjoin(prompt1, "]\n└─$ "RESET_COLOR);
	free(prompt1);
	return (final_prompt);
}

void	init_minishell(t_data *data, int ac, char **av, char **env)
{
	data->ac = ac;
	data->env = env;
	data->av = av;
	data->prompt = get_prompt();
	//"┌──(aziz㉿aelkheta)-[/nfs/homes/aelkheta/Desktop/minishell]\n└─$ ";
}

int	main(int ac, char **av, char **env)
{
	char	*command;
	t_data	data;

	// char	*prompt;
	// (void)ac;
	init_minishell(&data, ac, av, env);
	// prompt = "┌──(aziz㉿aelkheta)-[~/Desktop/minishell]\n└─$ ";
	// prompt = get_prompt();
	print_minishell();
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	command = readline(data.prompt);
	while (command != NULL)
	{
		parse_command(command, &data);
		free(command);
		command = readline(data.prompt);
	}
	free(data.prompt);
	return (0);
}
