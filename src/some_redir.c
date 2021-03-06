/*
** some_redir.c for  in /home/joubert/delivery/PSU_2016_minishell2
** 
** Made by Joubert Miguel
** Login   <miguel.joubert@epitech.eu>
** 
** Started on  Tue Apr  4 17:41:37 2017 Joubert Miguel
** Last update Tue Apr  4 18:54:42 2017 Joubert Miguel
*/

#include "../include/my.h"

int		is_some_redi(char *str)
{
  int           i;
  int           in;
  int           out;

  i = out = in = 0;
  while (str[i]) {
    if (str[i] == '<')
      out = 1;
    else if (str[i] == '>')
      in = 1;
    i++;
  }
  if (out && in)
    return (1);
  return (0);
}

int		ret_line(char **cmd)
{
  int		i;

  i = -1;
  while (cmd[++i])
    if (is_some_redi(cmd[i]))
      return (i);
  return (-1);
}

char		*ret_new_line(char *str)
{
  int		i;
  int		j;
  char		*dest;

  j = i = 0;
  dest = my_memset(my_strlen(str) + 1);
  while (str[i]) {
    if (str[i] == '<')
      i += 2;
    dest[j] = str[i];
    i++, j++;
  }
  return (dest);
}

char		**ret_news_cmd(char **cmd, int redis)
{
  char		**dest;
  int		i;

  i = -1;
  if ((dest = malloc(sizeof(char *) * 30)) == NULL)
    exit (84);
  while (++i < 30)
    dest[i] = my_memset(100);
  i = - 1;
  while (++i < redis)
    dest[i] = my_strdup(cmd[i]);
  dest[i] = ret_new_line(cmd[i]);
  while (cmd[++i])
    dest[i] = cmd[i];
  dest[i] = NULL;
  return (dest);
}
