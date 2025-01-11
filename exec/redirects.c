
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
	while (redirects)
	{
		if (redir->type == IN)
		{
			in_fd = open(redir->val, O_RDONLY);
			if (in_fd == -1)
				return (-1);
			if (dup2(in_fd, STDIN_FILENO) == -1)
				return(-1);
			close(in_fd);
		}
		else if (redir->type == HEREDOC)
		{
			temp_fd = handle_heredoc(redir->val);
			if (dup2(temp_fd, STDIN_FILENO) == -1)
				return (-1);
		}
		close(temp_fd);
		redir = redir->next;
	}
	return (0);
}

int handle_output_redirects(t_redir *redir)
{
	int out_fd;
	out_fd = -1;
//	t_redirects *redir;

// 	redir = redirects;
// 	while (redir)
// 	{
// //		printf("from red %s\n", redir->file);
		if (redir->type == OUT || redir->type == APPEND)
		{
			if (redir->type == OUT)
				out_fd = open(redir->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				out_fd = open(redir->val, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (out_fd == -1)
				return (-1);
			if (dup2(out_fd, STDOUT_FILENO) == -1)
				return (-1);
			close(out_fd);
		}
		redir = redir->next;
//	}
// free(redir);
	return (0);
}

int open_and_close(t_redir *redir)
{
	int out_fd;
	out_fd = -1;

	out_fd = open(redir->val, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (out_fd == -1)
	{
		panic("No such file or directory");
	}
	close(out_fd);

	return (0);
}

void handle_redirects(t_cmd *node)
{
	t_redir *input_redirects;
	t_redir *output_redirects;
	t_redir *temp;

	temp = node->redir;
	while (temp)
	{
		printf("redir %d  %s\n", temp->type, temp->val);
		temp = temp->next;
	}
	temp = node->redir;
	input_redirects = NULL;
	output_redirects = NULL;
	while (temp)
	{
		if (temp->type == IN || temp->type == HEREDOC)
			input_redirects = temp;
		else if (temp->type == OUT || temp->type == APPEND)
		{
			open_and_close(temp);
			output_redirects = temp;
		}
		temp = temp->next;
	}
	if (handle_input_redirects(input_redirects) == -1)
		panic("Failed to handle input redirects");
	if (handle_output_redirects(output_redirects) == -1)
		panic("Failed to handle output redirects");
}
