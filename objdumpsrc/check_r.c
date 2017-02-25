/*
** check_r.c for objdump in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sat Feb 25 16:37:20 2017 Baptiste Veyssiere
** Last update Sat Feb 25 16:38:41 2017 Baptiste Veyssiere
*/

#include "objdump.h"

int	check_r(int ret, char *bin, char *filename)
{
  if (ret == 1)
    {
      fprintf(stderr, "%s: %s: File format not recognized\n", bin, filename);
      return (1);
    }
  else if (ret == 2)
    {
      fprintf(stderr, "%s: %s: File truncated\n", bin, filename);
      return (1);
    }
  return (0);
}
