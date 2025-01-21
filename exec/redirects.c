
#include "../minishell.h"

int handle_heredoc(char *file)
{
	int temp_fd;
	char *line;
	
	temp_fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	line = readline("> ");

	while(1)
	{
		if (ft_strncmp(line, file, ft_strlen(file)) == 0)
			break;
		write(temp_fd, line, ft_strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	lseek(temp_fd, 0, SEEK_SET);
	return (temp_fd);
}
int handle_input_redirects(t_redir *redir)
{
	t_redir *redirects;
	int in_fd;
	int temp_fd;

	redirects = redir;
//	printf("from handle input %s\n", redirects->val);
	// while (redirects)
	// {
		if (redirects->type == IN)
		{
// 			if (access(redirects->val, F_OK) == -1)
// 			{
// //				panic("No such file or directory");
// 				return (-1);
// 			}
			in_fd = open(redirects->val, O_RDONLY);
			if (in_fd == -1)
			{
				// ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(redirects->val, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				return (-1);
			}
			if (dup2(in_fd, STDIN_FILENO) == -1)
				return(-1);
			close(in_fd);
		}
		else if (redirects->type == HEREDOC)
		{
			temp_fd = handle_heredoc(redirects->val);
			if (dup2(temp_fd, STDIN_FILENO) == -1)
				return (-1);
			close(temp_fd);
		}
//		redirects = redirects->next;
	// }
	return (0);
}

int open_and_close(t_redir *redir)
{
	int out_fd;
	out_fd = -1;

	// printf("acc %d %s\n", access(redir->val, O_WRONLY), redir->val);
	// if (access(redir->val, O_WRONLY) == -1)
	// {
	// 	panic("No such file or directory");
	// 	return (-1);
	// }
	out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (out_fd == -1)
	{
//		panic("minishell");
		ft_putstr_fd(redir->val, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	close(out_fd);

	return (0);
}

int handle_output_redirects(t_redir *redirects)
{
	int out_fd;
	out_fd = -1;
	t_redir *redir;

	redir = redirects;
	while (redir)
	{
//	printf("acc out %d %s\n", access(redir->val, O_WRONLY), redir->val);

// //		printf("from red %s\n", redir->file);
		if (redir->next)
			open_and_close(redir);
		else
		{
			if (redir->type == OUT || redir->type == APPEND)
			{
				if (redir->type == OUT)
					out_fd = open(redir->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				else
				{
					out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
				}
				if (out_fd == -1)
					return (-1);
				if (dup2(out_fd, STDOUT_FILENO) == -1)
					return (-1);
				close(out_fd);
				}
		}
		redir = redir->next;
	}
// free(redir);
	return (0);
}


int handle_redirects(t_cmd *node)
{
	t_redir *input_redirects;
	t_redir *output_redirects;
	t_redir *temp;
//	t_redir *temp2;
	t_redir *last_output;
	int err;

	err = 0;
	temp = node->redir;
	input_redirects = NULL;
	output_redirects = NULL;
	while (temp)
	{
		if (temp->type == IN || temp->type == HEREDOC)
		{
			input_redirects = temp;
			err = handle_input_redirects(input_redirects);
			if (err == -1)
				return (-1);
		}
		else if (temp->type == OUT || temp->type == APPEND)
		{
           if (output_redirects == NULL)
            {
                output_redirects = temp;
                last_output = temp; // Инициализация последнего элемента
            }
            else
            {
                last_output->next = temp; // Добавление в конец списка
                last_output = temp;      // Обновляем указатель на последний элемент
            }
		}
		temp = temp->next;
	}
	// temp2 = output_redirects;
	// while(temp2)
	// {
	// 	printf("outredir222 %d  %s\n", temp2->type, temp2->val);
	// 	temp2 = temp2->next;
	// }
//	output_redirects = temp2;
//	int in_redir_success = 0;
	if(input_redirects)
	{
		if (handle_input_redirects(input_redirects) == -1)
		{

//			write(2, "minishell: ", 11);
			ft_putstr_fd(input_redirects->val, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			err = -1;
		}

//	panic("Failed to handle input redirects");
	}
//	printf("in redir success %d\n", in_redir_success);
//				printf("from handle redir %s\n", output_redirects->val);
//		printf("input redirect success %d\n", in_redir_success); && in_redir_success == 0
	if (output_redirects)
	{
		if (handle_output_redirects(output_redirects) == -1)
		{
				// 			ft_putstr_fd("minishell: ", 2);
				// ft_putstr_fd(input_redirects->val, 2);
				// ft_putstr_fd(": No such file or directory\n", 2);

			err = -1;
		}
//			return (-1);
//			panic("Failed to handle output redirects");
	}
	return (err);
}
