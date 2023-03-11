/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:41:21 by hrakik            #+#    #+#             */
/*   Updated: 2023/03/10 16:53:31 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_prompt
{
	char				*cmds;
	char				*all;
	char				*st;
	int					quots;
	int					single_quots;
	int					dola;
	struct s_prompt		*next;
}						t_prompt;

typedef struct s_data
{
	char				**full_cmd;
	// t_file			*files;
	char				**infile;
	char				**herdoc;
	char				**outfile;
	int					out_open;
	struct s_data		*next;
}						t_data;
typedef struct s_list1
{
	char				*data;
	struct s_list1		*next;
}						t_list1;
typedef struct s_here_doc
{
	int					x;
	struct s_here_doc	*next;
}						t_here_doc;

typedef struct s_minishell
{
	int					q;
	char				**a;
	char				**k;
	char				*cmd;
	int					i;
	int					fd;
	int					fd1;
	int					j;
	int					her;
	int					fail_open;
	int					pid;
	int					track;
	int					fdp[2];
	int					*exits;

}						t_minishell;
unsigned char			exit_status;

char					**ft_split(char *s, char c);
char					**expand_Path(char **a, char **env);
char					**ft_fill_list(char **av, char *s);
void					msg_err(char *err);
void					msg_error(char *err);
void					msg_cmd_not_found(char *s);

//=======
char					**ft_cmdtrim(char const *s, char *set);
char					**break_cmd(char *s, char set);
int						count_word(char *s, char set);
// static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3]);
// static int	ft_count_words(const char *s, char *c, int i[2]);
void					ft_cmdsubsplit(char *s, char *set);
//========
void					divide_input(char **av, t_data **data);
//============
void					create_node(t_data **data, char **infile,
							char **outfile, char **full_cmd, int out_open,
							char **herdoc);
t_data					*l_lstlast(t_data **lst);
t_data					*l_lstnew(char **infile, char **outfile,
							char **full_cmd, int out_open, char **herdoc);
void					l_lstadd_back(t_data **lst, t_data *new);
int						l_lstsize(t_data *lst);
int						skip_infile(char **s);
void					multiple(t_data *m, char **env);
size_t					ft_strlen0(char *s);
char					*ft_strjoin0(char *s1, char *s2);
int						ft_strcmp_un(char *tmp, char *mv);
char					**split_path(char **env);
char					*ft_access(char **s_path, char *cmd);
void					divide_input_2(char **av, t_data **data, char **env);
void					mul_pipe(t_data *data, t_here_doc **x,
							t_minishell *mini, char **env, t_list1 **m,
							t_list1 **export);
int						ft_pwd(void);
void					ft_lstdelone1(t_data *lst, void (*del)(char **));
int						ft_strcmp(char *tmp, char *mv);
int						count_inf_open(char **av, int b, int y);
int					here_doc_open(t_data **data, t_here_doc **x,
							t_minishell *mini, char **env);
t_here_doc				*ft_lstnew0(int content);
int						ft_last(t_here_doc **her);
int						check_heredoc(char **k, int i);
int						here_doc(char *dat, int j, t_data *data,
							t_minishell *mini, char **env);
void					open_outfile(t_minishell *mini, t_data *data);
void					open_infile(t_minishell *mini, t_data *data,
							t_here_doc **x, char **env);
void					ft_lstadd_back3(t_here_doc **lst, t_here_doc *new);
void					open_infile_multiple(t_minishell *mini, t_data *data,
							t_here_doc **x);
int						print_exp_oonly(t_list1 **m);
int						ft_unset(t_list1 **head_ref, char *key);
int						ft_export(t_data *data, t_list1 **m, t_list1 **export);
t_list1					*ft_lstnew1(char *content);
int						builtin(t_data *data, t_list1 **m, t_list1 **export);
int						is_builtin(char *k);
int						ft_exit(t_data *data);
int						count_var(char *s, int index);
int						ft_cherche(char *s, char c);
char					*env_var_2(char **k, char **env);
char					**expand_Path_2(char **a, char **env);
char					*expande_var(char *s, char **env, int nb);
void					sort_export(t_list1 **export);
int						ft_atoi_exit(char *str);
char					**list_tabl(t_list1 **m);
int						ft_lstsize2(t_list1 *lst);
int						ft_strncmp1(const char *s1, const char *s2,
							unsigned int n);
void					one_command(t_data *data, t_minishell *mini,
							t_here_doc **x, char **envc, t_list1 **m,
							t_list1 **export);
void					envcpy(char **env, t_list1 **m);
int						print_env(t_list1 **m);
int						ft_echo(t_data *data);
int						ft_cd1(t_list1 **m, t_data *data);
void					rl_replace_line(const char *str, int undo);
// char				**ft_split(char const *s, char c);

#endif