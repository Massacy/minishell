/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imasayos <imasayos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:11:33 by imasayos          #+#    #+#             */
/*   Updated: 2023/10/22 17:11:37 by imasayos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_error_with_rtn1(const char *func, const char *err)
{
	builtin_error(func, NULL, err);
	return (1);
}

int	builtin_cd(char **argv, t_map *env)
{
	char	*home_path;
	char	*current_pwd;
	char	target_path[PATH_MAX];
	char	new_pwd[PATH_MAX];

	current_pwd = get_kv_value(env, "PWD");
	set_kv_in_map(env, "OLDPWD", current_pwd);
	if (argv[1] == NULL) // cdの対象がない場合
	{
		home_path = get_kv_value(env, "HOME");
		if (home_path == NULL)
			return(builtin_error_with_rtn1("cd", "HOME not found"));
	}
	ft_strlcpy(target_path, argv[1], PATH_MAX);
	if (chdir(target_path) < 0)
		return(builtin_error_with_rtn1("cd", "chdir"));
	// new_pwd = builtin_pwd(); // todo: builtin_pwdに変えるかも。
	if (getcwd(new_pwd, PATH_MAX) == NULL)
		return (builtin_error_with_rtn1("cd", "getcwd"));
	set_kv_in_map(env, "PWD", new_pwd);

	return (0);
}
