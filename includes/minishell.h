/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:51:36 by njeanbou          #+#    #+#             */
/*   Updated: 2024/07/02 17:56:33 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ms_libft/libft.h"

# include <readline/readline.h>
#include <readline/readline.h>
# include <readline/history.h>

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# define MSG_SYNTAX "minishell: syntax error near unexpected token\n"
# define MSG_QUOTE "minishell: unclosed quote\n"
# define MSG_HEREDOC "minishell: two heredoc\n"
# define MSG_FATAL "error 1 : fatal error\n"
# define MSG_EXEC "error 2 : ca a pas execute my J\n"
# define MSG_FLAGS "error 3 : seul echo peut avoir un flag dans l'enoncer\n"
# define MSG_ARG "error 4 : too many arguments\n"
# define MSG_NOT_FOUND "error: command not found: "

typedef enum e_operator
{
	none,
	PIPE,
	entre1,
	entre2,
	sortie1,
	sortie2,
}		t_operator;

typedef struct s_put
{
	char	*input;
	char	*output;
}	t_put;

typedef struct s_params
{
	char			**com;
	t_operator		inp_red;
	t_operator		out_red;
	struct s_params	*next;
}			t_params;

typedef struct s_env
{
	char			*env_name;
	char			*env_value;
	bool			is_exported;
	struct s_env	*next;
}			t_env;

typedef struct s_data
{
	int		p_fd[2];
	int		fd_in;
	int		fd_out;
	bool	exit;
	pid_t	pid;
}			t_data;

//cmd
int		ms_cd(t_params *para, t_env **env);
int		ms_echo(t_params *para);
int		ms_env(t_env **env);
void	ms_exit(t_params *para, t_env **env, t_data **data, t_put *put);
int		ms_export(t_params *para, t_env **env);
int		ms_pwd(void);
int		ms_unset(t_params *para, t_env **env);

//parsing
int		set_para(t_params **param, char *input, t_env **env, t_put **put);
void	set_put(t_put **put, t_params **para);
void	ft_doc(t_params **para, t_env **env, t_put **put);
void	set_var(t_params **para, t_env **env);
void	set_enum(t_params **para);
char	**set_cote(char **input);
char	**split_para(char *input);
int		error_quote(char *str);
int		count_quote(char *str, int *i);
int		count_red(char *str, int *i);
int		red_len(char *str, int *i);
int		quote_len(char *str, int *i);
int		ft_error(char **input, bool for_free);
void	free_error(t_params **para, t_put **put, t_data **data);
void	print_error(int error, char *input);
void	set_varbis(t_params **para, t_env **env);
char	*mid_var(char *str, t_env **env);
char	**mid_var_env(char **split_str, t_env **env);

//error
int		exec_error(int num);

//signal
void	exec_signal(int signal);
void	handler_signal(int signal);

//exec
int		ms_exec_loop(t_data *data, t_params **cmds, t_put *puts, t_env **env);
int		ms_exec_class(t_params *cmds, t_env **env, t_data **data, t_put *puts);
void	ms_exec(t_params *cmds, char **env);
void	ms_input(t_data *data, t_put *puts);
void	ms_output(t_data *data, t_put *puts, int rdr);
void	close_file(int fd);
int		open_file(char *file, int in_or_out);
char	*get_path(char *cmd, char **env);
int		ms_mycmds(t_params *cmds);
char	**get_env(t_env **env);
void	ft_free_tab(char **tab);
int		is_builded_cmd(char *cmd);
int		execve_checker(char **cmd);
int		check_exe(t_params **cmds);
pid_t	ft_getpid(void);

//utils
char	*clean_input(char *raw_input);
t_env	*set_env(char **env);
t_env	*new_node(char *env_name, char *env_value, bool export);
void	print_all(t_params **para, t_env **env, t_put **put);
void	print_com(t_params **para);
char	*recherche_env(char *str, t_env **env);
char	*ft_strjoin_sp(char const *s1, char *s2);
char	**split_var(char *str);
int		count_wd_var(char *str);
char	*clean_var(char *var);
void	free_all(t_params **para, t_put **put, t_data **data);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
int		ft_lstsize_env(t_env *lst);
void	add_status(t_env **env, int status);
char	*ft_strdup_quote(const char *s1);

#endif
