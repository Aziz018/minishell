/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkheta <aelkheta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:43:14 by aelkheta          #+#    #+#             */
/*   Updated: 2024/05/18 18:05:06 by aelkheta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int ac, char **av) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(av[1]);
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Read and print the entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return EXIT_SUCCESS;
}
