#include "../headers/minishell.h"

t_env	*create_node(char **key_value)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env));
	list->key = ft_strdup(key_value[0]);
	list->value = ft_strdup(key_value[1]);
	if (!ft_strncmp(key_value[1], "(null)", 6))
		list->print = 0;
	else
		list->print = 1;
	list->next = NULL;
	return (list);
}

void	get_env(char **envp, t_var *var)
{
	t_env	*current;
	char	**key_value;

	while (*envp)
	{
		key_value = ft_split(*envp, '=');
		current = create_node(key_value);
		ft_lstadd_back(&var->head_env, current);
		ft_free_args(key_value);
		envp++;
	}
}

void	init_env(t_var *var, char **env)
{
	get_env(env, var);
	var->home = find_value("HOME", var);
	g_var = var;
	signal(SIGINT, signal_handler_c);
	signal(SIGQUIT, signal_handler_quit);
}
