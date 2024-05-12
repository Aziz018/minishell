/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:42:13 by aelkheta          #+#    #+#             */
/*   Updated: 2024/04/23 13:43:04 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt()
{
    char *prompt = "┌──(aziz㉿hostname)-[~/Desktop/minishell]\n└─$ ";

    // char *prompt = "aziz@kali ~/desktop/minishell> ";
    // printf("┌──(aziz㉿hostname)-[~/Desktop/minishell]\n");
    // printf("└─$ ");
    char *output_color = GREEN_COLOR;
    char *reset_color = RESET_COLOR;
    // printf("%s\n", prompt);
    write(1, output_color, ft_strlen(output_color));
    write(1, prompt, ft_strlen(prompt));
    write(1, reset_color, ft_strlen(reset_color));
}

int check_command(char *command)
{
    if (ft_strnstr(command, "ls", ft_strlen(command)))
    {
        system("ls");
    }
    return 0;
}

int main()
{
    print_prompt();
    char *command;
    command = get_next_line(0);
    if (command == NULL || command[0] == '\0')
        return 0;
    while(1)
    {
        if (command == NULL || command[0] == '\0')
            return 0;
        check_command(command);
        print_prompt();
        command = get_next_line(0);
    }
    return 0;
}