#include "../headers/minishell.h"

int	fopen_read(t_var *var, t_files *files)
{
	var->fd[0] = open(files->file_name, O_RDONLY);
	if (*files->file_name == TOKEN_DOLLAR)
	{
		*files->file_name = 36;
		ft_putstr_error("minishell: ", files->file_name, \
		": ambiguous redirect\n");
		var->error = 1;
		return (0);
	}
	if (var->fd[0] < 0)
	{
		no_file(var, var->prs->cmd, "", ": No such file or directory\n");
		var->error = 1;
		return (0);
	}
	else
		dup2(var->fd[0], STDIN_FILENO);
	close(var->fd[0]);
	return (1);
}

int	redir_append(t_var *var, t_files *files)
{
	if (files->type == '>' && *files->file_name != TOKEN_DOLLAR)
	{
		var->fd[1] = open(files->file_name, O_WRONLY \
		| O_CREAT | O_TRUNC, 0666);
	}
	else if (files->type == 'a' && *files->file_name != TOKEN_DOLLAR)
		var->fd[1] = open(files->file_name, O_WRONLY \
		| O_CREAT | O_APPEND, 0666);
	else if (*files->file_name == TOKEN_DOLLAR)
	{
		*files->file_name = 36;
		no_file(var, files->file_name, "", ": ambiguous redirect\n");
		var->error = 1;
		return (0);
	}
	if (var->fd[1] < 0)
	{
		error_open_file(var, files);
		return (0);
	}
	return (1);
}

void	open_file(t_var *var)
{
	t_files		*files;

	files = var->prs->file_head;
	while (files)
	{
		if (files->type == '>' || files->type == 'a')
		{
			if (!redir_append(var, files))
				break ;
			error_red_app(var, files);
			dup2(var->fd[1], STDOUT_FILENO);
			close(var->fd[1]);
		}
		else
			if (!fopen_read(var, files))
				break ;
		files = files->next;
	}
}
