/*
** checks.c for objdump in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Thu Feb 23 00:36:52 2017 Baptiste Veyssiere
** Last update Thu Feb 23 14:01:03 2017 Baptiste Veyssiere
*/

#include "nm.h"

int	check_name64(Elf64_Ehdr *data)
{
  Elf64_Shdr	*start;
  Elf64_Shdr	shstrtab_section;
  char		*namestring;
  Elf64_Shdr	section_header;
  char		*name;

  start = (Elf64_Shdr*)((void*)data + data->e_shoff);
  shstrtab_section = start[data->e_shstrndx];
  namestring = (char*)((void*)data + shstrtab_section.sh_offset);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = start[i];
      name = namestring + section_header.sh_name;
      for (int i = 0; name[i]; i++)
	if (!isprint(name[i]))
	  return (1);
    }
  return (0);
}

int	check_name32(Elf32_Ehdr *data)
{
  Elf32_Shdr	*start;
  Elf32_Shdr	shstrtab_section;
  char		*namestring;
  Elf32_Shdr	section_header;
  char		*name;

  start = (Elf32_Shdr*)((void*)data + data->e_shoff);
  shstrtab_section = start[data->e_shstrndx];
  namestring = (char*)((void*)data + shstrtab_section.sh_offset);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = start[i];
      name = namestring + section_header.sh_name;
      for (int i = 0; name[i]; i++)
	if (!isprint(name[i]))
	  return (1);
    }
  return (0);
}
