#include "../headers/minishell.h"

void	correct_flag_neg(t_var *var, int i)
{
	t_files	*fil;
	int		j;
	int		k;

	fil = var->prsTail->file_head;
	while (fil)
	{
		j = -1;
		while (fil->file_name[++j])
		{
			if (fil->file_name[j] < 0 && fil->file_name[j] != -90)
				fil->file_name[j] = -fil->file_name[j];
		}
		fil = fil->next;
	}
	while (var->prsTail->args[++i])
	{
		k = -1;
		while (var->prsTail->args[i][++k])
		{
			if (var->prsTail->args[i][k] < 0)
				var->prsTail->args[i][k] = -var->prsTail->args[i][k];
		}
	}
}

void	search_cmd_args(t_var *var, int *j)
{
	t_parser	*node;
	char		*tmp;
	int			i;

	i = -1;
	node = var->prsTail;
	tmp = var->split_pip[*j];
	var->split_pip[*j] = ft_strtrim(var->split_pip[*j], " ");
	free(tmp);
	node->args = ft_split(var->split_pip[*j], ' ');
	correct_flag_neg(var, i);
	node->cmd = node->args[0];
}
