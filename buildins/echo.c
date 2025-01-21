
#include "../minishell.h"


int if_no_newline(t_cmd *node)
{
	int i;
	int j;
	int no_newline;
	int flag;

	i = 1;
	j = 2;
	flag = 0;
	no_newline = 0;
	while (ft_strncmp(node->args[i], "-n", 2) == 0)
	{
		while(node->args[i][j] != '\0')
		{
			no_newline = 0;
			if (node->args[i][j] != 'n')
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

int ft_echo(t_data *data, t_cmd *node)
{
	int i;

//	printf("test_echo\n");
	if (node->args[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (ft_strncmp(node->args[1], "$?", 2) == 0)
	{
		ft_putstr_fd(ft_itoa(data->err_no), 1);
		return (0);
	}
	
	i = if_no_newline(node) + 1;
	while (node->args[i] != NULL)
	{
		printf("%s", node->args[i]);
		if (node->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (if_no_newline(node) == 0)
		printf("\n");
	return (0);
}
