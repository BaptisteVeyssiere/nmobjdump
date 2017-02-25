/*
** printer.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sat Feb 25 16:00:00 2017 Baptiste Veyssiere
** Last update Sat Feb 25 16:23:28 2017 Baptiste Veyssiere
*/

#include "nm.h"

void	printer64(Elf64_Sym *sorted_symtab, Elf64_Shdr *start, char *name)
{
  char	flag;

  flag = get_flag64(sorted_symtab, start);
  if (flag == 'U' || flag == 'w')
    printf("%17c", ' ');
  else
    printf("%016lx ", sorted_symtab->st_value);
  printf("%c %s\n", flag, name);
}

void	printer32(Elf32_Sym *sorted_symtab, Elf32_Shdr *start, char *name)
{
  char	flag;

  flag = get_flag32(sorted_symtab, start);
  if (flag == 'U' || flag == 'w')
    printf("%9c", ' ');
  else
    printf("%08x ", sorted_symtab->st_value);
  printf("%c %s\n", flag, name);
}
