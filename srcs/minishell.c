/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:42:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/06/25 19:02:10 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

t_data *data = NULL;

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
	output_color = GRN;
	reset_color = CRESET;
	write(1, output_color, ft_strlen(output_color));
	write(1, prompt, ft_strlen(prompt));
	write(1, reset_color, ft_strlen(reset_color));
}

int	exec_command(char *command)
{
	pid_t	pid;
	char	*cmd_path;
	char **parsedcmd = ft_split(command, ' ');
	if (command == NULL || command[0] == 0)
		return (0);
	cmd_path = ft_strjoin("/bin/", parsedcmd[0]);
	if (access(cmd_path, X_OK) == 0)
	{
		pid = fork();
		if (pid == -1)
			return (0);
		else if (pid == 0)
			execve(cmd_path, &parsedcmd[1], NULL);
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

	prompt = get_prompt();
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
		printf("\n%s", prompt);
	free(prompt);
}

void	print_char_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		printf("%s\n", array[i]);
}

char	*get_prompt(void)
{	
	char	*prompt1;
	char	*prompt2;
	char	*prompt3;
	char	*final_prompt;
	prompt1 = BBLU"┌──(aziz㉿aelkheta)-["COLOR_RESET;
	prompt2 = getcwd(NULL, 0);
	prompt3 = ft_strjoin(BWHT, prompt2);
	free(prompt2);
	prompt1 = ft_strjoin(prompt1, prompt3);
	free(prompt3);
	final_prompt = ft_strjoin(prompt1, BBLU"]\n└─$ "COLOR_RESET);
	free(prompt1);
	return (final_prompt);
}

void	add_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_env	*lstnew(char *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->value = content;
	new_node->next = NULL;
	return (new_node);
}


t_env *creat_env(char **env)
{
	t_env *head = NULL;
	int i = -1;
	while(env[++i] != NULL)
		add_back(&head, lstnew(env[i]));
	return (head);
}

void	init_minishell(int ac, char **av, char **env)
{
	//"┌──(aziz㉿aelkheta)-[/nfs/homes/aelkheta/Desktop/minishell]\n└─$ ";
	data->ac = ac;
	data->env = creat_env(env);
	data->av = av;
	data->syntax_error = false;
	data->prompt = get_prompt();
	data->new_command = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*command;
	
	data = (t_data *)malloc(sizeof(t_data));
	init_minishell(ac, av, env);	
	print_minishell();
	
	signal(SIGQUIT, sig_handler);
	// signal(SIGINT, sig_handler);
	
	command = readline(data->prompt);
	while (command != NULL)
	{
		add_history(command);
		parse_command(command);
		// free(command);
		command = readline(data->prompt);
	}
	clear_history();
	free(data->new_command);
	free(data->prompt);
	return (0);
}
