/*
** ar_file_parser.c for objdump in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Wed Feb 22 21:05:20 2017 Baptiste Veyssiere
** Last update Sun Feb 26 01:49:00 2017 Baptiste Veyssiere
*/

#include "objdump.h"

static int	ar_objdump(void *data, char *filename, char *bin)
{
  Elf32_Ehdr	*header;

  header = (Elf32_Ehdr*)data;
  if (is_arfile(data, filename, bin))
    return (0);
  else if (check_file(header, filename, bin))
    return (1);
  if (header->e_ident[EI_CLASS] == ELFCLASS32)
    objdump32(data, filename);
  else if (header->e_ident[EI_CLASS] == ELFCLASS64)
    objdump64(data, filename);
  return (0);
}

static int	get_header_size(void *data)
{
  char	*string;
  int	size;

  if (!(string = malloc(16)))
    return (-1);
  for (int i = 0; i < 16; i++)
    string[i] = 0;
  for (int i = 0; i < 10 && ((char*)data)[i] != ' '; i++)
    string[i] = ((char*)(data))[i];
  size = atoi(string);
  free(string);
  return (size);
}

static char	*get_file_name(void *data)
{
  char	*name;

  if (!(name = malloc(17)))
    return (NULL);
  for (int i = 0; i < 17; i++)
    name[i] = 0;
  for (int i = 0; i < 16 && ((char*)data)[i] != '/'; i++)
    {
      name[i] = ((char*)data)[i];
      name[i + 1] = 0;
    }
  return (name);
}

static int	ar_file_reader(void *data, char *bin)
{
  int	size;
  char	end;
  char	*file;

  end = 0;
  while (end == 0)
    {
      if ((file = get_file_name(data)) == NULL)
	return (0);
      data += 48;
      if ((size = get_header_size(data)) < 1)
	return (0);
      data += 12;
      ar_objdump(data, file, bin);
      data += size;
      if (!data || !((char*)data)[0])
	end = 1;
    }
  return (1);
}

int	is_arfile(void *data, char *filename, char *bin)
{
  char	*magic_string;
  char	*string;
  int	size;

  if (!data)
    return (0);
  magic_string = "!<arch>\n";
  string = (char*)data;

  for (int i = 0; i < 7; i++)
    if (magic_string[i] != string[i])
      return (0);
  printf("In archive %s:\n", filename);
  data += 56;
  if ((size = get_header_size(data)) < 1)
    return (0);
  data += 12 + size;
  return (ar_file_reader(data, bin));
}
