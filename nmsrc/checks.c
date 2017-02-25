/*
** checks.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri Feb 24 00:24:34 2017 Baptiste Veyssiere
** Last update Sat Feb 25 15:35:21 2017 Baptiste Veyssiere
*/

#include "nm.h"

long	get_filesize(char *file)
{
  long	filesize;
  int	fd;

  if ((fd = open(file, O_RDONLY)) == -1)
    return (-1);
  filesize = lseek(fd, 0, SEEK_END);
  if (close(fd) == -1)
    return (-1);
  return (filesize);
}

int	check_name64(Elf64_Ehdr *data, char *file)
{
  Elf64_Shdr	*start;
  Elf64_Shdr	shstrtab_section;
  char		*namestring;
  Elf64_Shdr	*section_header;
  char		*name;
  long		size;

  if ((size = get_filesize(file)) == -1)
    return (1);
  if ((uint32_t)(data->e_shoff + data->e_shentsize * data->e_shnum) > size)
    return (2);
  start = (Elf64_Shdr*)((void*)data + data->e_shoff);
  shstrtab_section = start[data->e_shstrndx];
  namestring = (char*)((void*)data + shstrtab_section.sh_offset);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = &(start[i]);
      if (section_header->sh_name >
	  (uint32_t)(data->e_shoff + data->e_shentsize * data->e_shnum))
	return (1);
      name = namestring + section_header->sh_name;
      for (int i = 0; name[i]; i++)
	if (!isprint(name[i]))
	  return (1);
    }
  return (0);
}

int	check_name32(Elf32_Ehdr *data, char *file)
{
  Elf32_Shdr	*start;
  Elf32_Shdr	shstrtab_section;
  char		*namestring;
  Elf32_Shdr	*section_header;
  char		*name;
  long		size;

  if ((size = get_filesize(file)) == -1)
    return (1);
  if ((uint32_t)(data->e_shoff + data->e_shentsize * data->e_shnum) > size)
    return (2);
  start = (Elf32_Shdr*)((void*)data + data->e_shoff);
  shstrtab_section = start[data->e_shstrndx];
  namestring = (char*)((void*)data + shstrtab_section.sh_offset);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = &(start[i]);
      if (section_header->sh_name >
	  (uint32_t)(data->e_shoff + data->e_shentsize * data->e_shnum))
	return (1);
      name = namestring + section_header->sh_name;
      for (int i = 0; name[i]; i++)
	if (!isprint(name[i]))
	  return (1);
    }
  return (0);
}
