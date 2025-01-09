
#include "../minishell.h"


int if_no_newline(t_cmd_node *node)
{
	int i;
	int j;
	int no_newline;
	int flag;

	i = 1;
	j = 2;
	flag = 0;
	no_newline = 0;
	while (ft_strncmp(node->cmd_args[i], "-n", 2) == 0)
	{
		while(node->cmd_args[i][j] != '\0')
		{
			no_newline = 0;
			if (node->cmd_args[i][j] != 'n')
				break;
			j++;
			no_newline = 1;
		}
		if (no_newline == 0)
			break;
		flag++;
		i++;
	}
	return (flag);
}

int ft_echo(t_cmd_node *node)
{
	int i;

	i = if_no_newline(node) + 1;
	while (node->cmd_args[i] != NULL)
	{
		printf("%s", node->cmd_args[i]);
		if (node->cmd_args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (if_no_newline(node) == 0)
		printf("\n");
	return (0);
}
