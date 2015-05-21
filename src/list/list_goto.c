/*
** list_goto.c for list go to in /home/gascon/Epitech/PSU/42tmp
**
** Made by Vertigo
** Login   <gascon@epitech.net>
**
** Started on  Thu May 14 20:02:50 2015 Vertigo
** Last update Fri May 15 08:23:07 2015 Vertigo
*/

#include <stdlib.h>
#include <mysh.h>

void	list_goto_root_hist(t_mysh *sh)
{
  while (sh->history->key[0] != '\0')
    sh->history = sh->history->next;
}
