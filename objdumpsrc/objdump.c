/*
** objdump.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Feb 20 19:34:12 2017 Baptiste Veyssiere
** Last update Tue Feb 21 11:37:15 2017 Baptiste Veyssiere
*/

#include "objdump.h"

static void	*getdata(char *filename)
{
  FILE	*file;
  long	fsize;
  char	*buffer;

  if (!(file = fopen(filename, "rb")))
    {
      fprintf(stderr, "objdump: '%s': No such file\n", filename);
      return (NULL);
    }
  if (fseek(file, 0, SEEK_END) == -1 ||
      (fsize = ftell(file)) == -1 ||
      fseek(file, 0, SEEK_SET) == -1 ||
      !(buffer = malloc(fsize + 1)) ||
      fread(buffer, fsize, 1, file) == 0 ||
      fclose(file) == -1)
    return (NULL);
  buffer[fsize] = 0;
  return (buffer);
}

static int	check_file(Elf32_Ehdr *header, char *file)
{
  if (header->e_ident[EI_MAG0] != ELFMAG0 ||
      header->e_ident[EI_MAG1] != ELFMAG1 ||
      header->e_ident[EI_MAG2] != ELFMAG2 ||
      header->e_ident[EI_MAG3] != ELFMAG3 ||
      header->e_type == ET_NONE)
    {
      fprintf(stderr, "objdump: %s: File format not recognized\n", file);
      return (1);
    }
  return (0);
}

static int	objdump(char *filename)
{
  void		*data;
  Elf32_Ehdr	*header;

  if (!(data = getdata(filename)))
    return (-1);
  header = (Elf32_Ehdr*)data;
  if (check_file(header, filename))
    return (1);
  if (header->e_ident[EI_CLASS] == ELFCLASS32)
    objdump32(data, filename);
  else if (header->e_ident[EI_CLASS] == ELFCLASS64)
    objdump64(data, filename);
  return (0);
}

int	main(int ac, char **av)
{
  int	ret;

  ret = 0;
  if (ac > 1)
    {
      for (int i = 1; i < ac; i++)
	if (objdump(av[i]) == -1)
	  ret = 1;
    }
  else if (objdump("a.out") == -1)
    ret = 1;
  return (ret);
}
