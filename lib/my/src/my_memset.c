/*
** my_memset.c for minishell2 in /home/k6/rendu/PSU_2014_minishell2
** 
** Made by Cano Chloe
** Login   <k6@epitech.net>
** 
** Started on  Sun Mar  8 04:48:05 2015 Cano Chloe
** Last update Sun Mar  8 04:50:10 2015 Cano Chloe
*/
#include <my.h>

void		my_memset(char *s, char c, size_t len)
{
  while (len > 0)
    s[--len] = c;
}
