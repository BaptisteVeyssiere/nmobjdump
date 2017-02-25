/*
** flags.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed Feb 22 01:29:29 2017 Baptiste Veyssiere
** Last update Sat Feb 25 19:22:42 2017 Baptiste Veyssiere
*/

#include "objdump.h"

int	has_symtab64(Elf64_Ehdr *data)
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
      (void)name;
      if (section_header.sh_type == SHT_SYMTAB &&
	  strcmp(name, ".symtab") == 0)
	return (1);
    }
  return (0);
}

int	has_paged64(Elf64_Ehdr *data)
{
  Elf64_Shdr	*start;
  Elf64_Shdr	section_header;

  start = (Elf64_Shdr*)((void*)data + data->e_shoff);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = start[i];
      if (section_header.sh_type == SHT_DYNAMIC)
	return (1);
    }
  return (0);
}

int	has_symtab32(Elf32_Ehdr *data)
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
      if (section_header.sh_type == SHT_SYMTAB &&
	  strcmp(name, ".symtab") == 0)
	return (1);
    }
  printf("nop");
  return (0);
}

int	has_paged32(Elf32_Ehdr *data)
{
  Elf32_Shdr	*start;
  Elf32_Shdr	section_header;

  start = (Elf32_Shdr*)((void*)data + data->e_shoff);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = start[i];
      if (section_header.sh_type == SHT_DYNAMIC)
	return (1);
    }
  return (0);
}
