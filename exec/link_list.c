#include "../libraries/minishell.h"

int	lstsize(t_command *lst)
{
	int		size;
	t_command	*current;

	if (lst == NULL)
		return (0);
	size = 0;
	current = lst;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

t_command	*lstlast(t_command *lst)
{
	t_command	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}