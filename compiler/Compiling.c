/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Compiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:11:45 by aziz              #+#    #+#             */
/*   Updated: 2024/05/31 09:42:52 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main()
{
    int i = 0;
    while(i < 10)
    {
        write(1, "\rC             ", 16);
        usleep(100000);
        write(1, "\rCo            ", 16);
        usleep(100000);
        write(1, "\rCom           ", 16);
        usleep(100000);
        write(1, "\rComp          ", 16);
        usleep(100000);
        write(1, "\rCompi         ", 16);
        usleep(100000);
        write(1, "\rCompil        ", 16);
        usleep(100000);
        write(1, "\rCompili       ", 16);
        usleep(100000);
        write(1, "\rCompilin      ", 16);
        usleep(100000);
        write(1, "\rCompiling     ", 16);
        usleep(100000);
        write(1, "\rCompiling  .  ", 16);
        usleep(100000);
        write(1, "\rCompiling  .. ", 16);
        usleep(100000);
        write(1, "\rCompiling  ...", 16);
        usleep(100000);
        write(1, "\r ompiling  ...", 16);
        usleep(100000);
        write(1, "\r  mpiling  ...", 16);
        usleep(100000);
        write(1, "\r   piling  ...", 16);
        usleep(100000);
        write(1, "\r    iling  ...", 16);
        usleep(100000);
        write(1, "\r     ling  ...", 16);
        usleep(100000);
        write(1, "\r      ing  ...", 16);
        usleep(100000);
        write(1, "\r       ng  ...", 16);
        usleep(100000);
        write(1, "\r        g  ...", 16);
        usleep(100000);
        write(1, "\r           ...", 16);
        usleep(100000);
        write(1, "\r            ..", 16);
        usleep(100000);
        write(1, "\r             .", 16);
        usleep(100000);
        i++;
    }
    write(1, "\rdone\n", 6);
}
