/*
** out.c for  in /home/joubert/delivery/PSU_2016_minishell2
** 
** Made by Joubert Miguel
** Login   <miguel.joubert@epitech.eu>
** 
** Started on  Wed Mar 15 20:57:05 2017 Joubert Miguel
** Last update Thu Mar 23 13:56:43 2017 Joubert Miguel
*/

#include "../include/my.h"

int		is_out(char *str)
{
  int		i;
  int		count;

  count = 0;
  i = -1;
  while (str[++i])
    {
      if (str[i] == '>' && str[i + 1] == '>')
	return (0);
      else if (str[i] == '>' && str[i + 1] != '>')
	count++;
    }
  if (count == 1)
    return (1);
  else if (count > 1) {
    my_putstr("Ambiguous output redirect.\n");
    return (-1);
  }
  return (0);
}

void		create_file_before(char *cmd, char **env)
{
  char		**args;
  char		**command;
  char		*path;
  char		**new;
  pid_t		pid;

  if ((pid = fork()) == -1)
    exit (1);
  else if (pid == 0)
    {
      command = my_str_to_wordtab(cmd, '>', 0);
      if ((new = malloc(sizeof(char *) * 2)) == NULL)
	exit (84);
      new[0] = my_strcat("touch ", check_space(command[1]));
      new[1] = NULL;
      path = ret_good_path(0, env, new);
      args = my_ret_args(my_str_to_wordtab(new[0], ' ', 0), path);
      execve(path, args, env);
      exit (0);
    }
  else
    wait(NULL);
}

void		exec_out(char *cmd, char **env)
{
  int		fd;
  int		pid;
  char		**command;
  char          **args;
  char		*path;

  command = my_str_to_wordtab(cmd, '>', 0);
  fd = open(check_space(command[1]), O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if ((pid = fork()) < 0)
    exit (84);
  if (pid == 0)
    {
      dup2(fd, 1);
      path = ret_good_path(0, env, my_str_to_wordtab(command[0], ' ', 0));
      args = my_ret_args(my_str_to_wordtab(command[0], ' ', 0), path);
      execve(path, args, env);
      exit (0);
    }
  else
    {
      close (fd);
      wait(NULL);
    }
}
