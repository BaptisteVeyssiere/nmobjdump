/*
** nm32.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump/nmsrc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Thu Feb 23 13:59:38 2017 Baptiste Veyssiere
** Last update Thu Feb 23 16:34:22 2017 Baptiste Veyssiere
*/

#include "nm.h"

void	nm32(void *data, char *filename, char *bin)
{
  Elf32_Ehdr	*header;

  (void)bin;
  header = (Elf32_Ehdr*)data;
  if (!header)
    return ;
  (void)filename;
}
