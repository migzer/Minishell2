/*
** exec_pipe.c for  in /home/joubert/delivery/PSU_2016_minishell2
** 
** Made by Joubert Miguel
** Login   <miguel.joubert@epitech.eu>
** 
** Started on  Mon Mar 13 12:16:06 2017 Joubert Miguel
** Last update Tue Apr  4 13:16:26 2017 Joubert Miguel
*/

#include "../include/my.h"

int             is_piped(char *str)
{
  int           i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '|')
	return (1);
      i++;
    }
  return (0);
}

char		*ret_good_path(int index, char **env, char **cmd)
{
  char          **command;
  char          **path;
  int           i;

  i = -1;
  path = my_ret_path_env(env, "PATH", 5);
  command = my_str_to_wordtab(cmd[index], ' ', 0);
  while (path[++i] != NULL)
    if (access(my_strcat(my_strcat(path[i], "/"), *command), F_OK) != -1
	&& access(my_strcat(my_strcat(path[i], "/"), *command), R_OK) != -1)
      break;
  path[i] = my_strcat(my_strcat(path[i], "/"), *command);
  return (path[i]);
}

void		exec_pipe_son(char **cmd, char **env, int index)
{
  char          **command;
  char          **args;
  char		*path;
  pid_t		pid;
  int   	pfd[2];

  if (pipe(pfd) == - 1)
    exit (84);
  if ((pid = fork()) == -1)
    exit (84);
  else if (pid == 0)
    {
      command = my_str_to_wordtab(cmd[index], ' ', 0);
      path = ret_good_path(index, env, cmd);
      args = my_ret_args(command, path);
      if (dup2(pfd[1], 1) == -1)
	exit (84);
      if (close(pfd[0]) == -1)
	exit (84);
      if (!my_strncmp(cmd[index], "cd", 2) ||
	  !my_strncmp(cmd[index], "env", 3) ||
	  !my_strncmp(cmd[index], "setenv", 6) ||
	  !my_strncmp(cmd[index], "unsetenv", 8))
	env = my_env(env, cmd[index++]);
      else execve(path, args, env);
      exit(0);
    }
  else
    {
      command = my_str_to_wordtab(cmd[index + 1], ' ', 0);
      path = ret_good_path(index + 1, env, cmd);
      args = my_ret_args(command, path);
      if (dup2(pfd[0], 0) == -1)
	exit (84);
      if (close(pfd[1]) == -1)
	exit (84);
      if (index < my_strlen_d_char(cmd) - 2)
	return (exec_pipe_son(cmd, env, ++index));
      else if (is_out(cmd[index + 1]) == 1)
	return (exec_out(cmd[index + 1], env));
      else if (is_in(cmd[index + 1]) == 1)
	return (exec_in(cmd[index + 1], env));
      else if (my_strncmp(cmd[index + 1], "cd", 2) == 0) builtin_to_file("cd");
      else if (my_strncmp(cmd[index + 1], "env", 3) == 0) builtin_to_file("env");
      else if (my_strncmp(cmd[index + 1], "setenv", 6) == 0) builtin_to_file("setenv");
      else if (my_strncmp(cmd[index + 1], "unsetenv", 8) == 0) builtin_to_file("unsetenv");
      else execve(path, args, env);
      wait(NULL);
      
    }
}

int		exec_pipe(char **cmd, char ***env, t_shell Sh)
{
  pid_t		pid;
  int		i;
  int		nf;
  int		tmp;
  int		is_exit;
  char		*is_builtin;

  is_builtin = my_memset(10);
  is_exit = nf = 0;
  i = -1;
  while (cmd[++i]) {
    if (!my_strcmp(cmd[i], "exit")) is_exit = 1;
    else nf = verify_cmd(*env, cmd[i], 9, 0);
    (nf == 1) ? tmp = 1 : 0;
  }
  nf = tmp;
  is_file_to_create(cmd, *env);
  if ((pid = fork()) == -1)
    exit (84);
  if (pid == 0)
    {
      exec_pipe_son(cmd, *env, 0);
      exit(0);
    }
  else
    wait(NULL);
  is_builtin = is_builtin_in_file(*env, Sh);
  if (my_strncmp(is_builtin, "cd", 2) == 0)
    *env = my_cd(cmd[--i], *env);
  if (my_strncmp(is_builtin, "env", 3) == 0 ||
      my_strncmp(is_builtin, "setenv", 3) == 0 ||
      my_strncmp(is_builtin, "unsetenv", 3) == 0)
    *env = my_env(*env, cmd[--i]);
  if (is_exit)
    exit (nf);
  return (nf);
}

char		**get_pipe_cmd(char *str)
{
  char		**cmd;
  char		**dest;
  int		i;
  int		j;
  int		k;

  j = k = 0;
  i = (str[0] == ' ') ? 1 : 0;
  if ((dest = malloc(sizeof(char *) * 50)) == NULL)
    return (NULL);
  if ((cmd = malloc(sizeof(char *) * 50)) == NULL)
    return (NULL);
  cmd[0] = my_memset(100);
  while (str[i + 1])
    {
      if (str[i + 1] == '|')
	{
	  cmd[j][k++] = str[i];
	  k = 0;
	  i += 2, j++;
	  cmd[j] = my_memset(100);
	}
      cmd[j][k] = str[i];
      i++, k++;
    }
  cmd[j][k] = str[i];
  cmd[++j] = NULL;
  j = -1;
  while (cmd[++j])
    {
      dest[j] = my_memset(my_strlen(cmd[j]) * 10);
      dest[j] = check_space(cmd[j]);
    }
  dest[j] = NULL;
  return (dest);
}
