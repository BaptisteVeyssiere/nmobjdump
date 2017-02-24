/*
** objdump.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Feb 20 19:34:12 2017 Baptiste Veyssiere
** Last update Fri Feb 24 00:25:38 2017 Baptiste Veyssiere
*/

#include "objdump.h"

void	print_flags(uint32_t flags)
{
  int	values[] = {HAS_RELOC, EXEC_P, HAS_LINENO, HAS_DEBUG,
		  HAS_SYMS, HAS_LOCALS, DYNAMIC, WP_TEXT,
		  D_PAGED};
  char*	strings[] = {"HAS_RELOC", "EXEC_P", "HAS_LINENO",
		   "HAS_DEBUG", "HAS_SYMS", "HAS_LOCALS",
		   "DYNAMIC", "WP_TEXT", "D_PAGED"};
  int	start;

  start = 1;
  for (int i = 0; i < 9; i++)
    if (flags & values[i])
      {
	if (!start)
	  printf(", ");
	printf("%s", strings[i]);
	start = 0;
      }
  printf("\n");
}

static void	*getdata(char *filename, char *bin)
{
  FILE	*file;
  long	fsize;
  char	*buffer;

  if (!(file = fopen(filename, "rb")))
    {
      fprintf(stderr, "%s: '%s': No such file\n", bin, filename);
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

int	check_file(Elf32_Ehdr *header, char *file, char *bin)
{
  if (header->e_ident[EI_MAG0] != ELFMAG0 ||
      header->e_ident[EI_MAG1] != ELFMAG1 ||
      header->e_ident[EI_MAG2] != ELFMAG2 ||
      header->e_ident[EI_MAG3] != ELFMAG3 ||
      header->e_type == ET_NONE)
    {
      fprintf(stderr, "%s: %s: File format not recognized\n", bin, file);
      return (1);
    }
  return (0);
}

int	objdump(char *filename, char *bin)
{
  void		*data;
  Elf32_Ehdr	*header;
  int		ret;
  
  if (!(data = getdata(filename, bin)))
    return (-1);
  header = (Elf32_Ehdr*)data;
  if (is_arfile(data, filename, bin))
    return (0);
  else if (check_file(header, filename, bin))
    return (1);
  if (header->e_ident[EI_CLASS] == ELFCLASS32)
    {
      ret = check_name32(data, filename);
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
      objdump32(data, filename);
    }
  else if (header->e_ident[EI_CLASS] == ELFCLASS64)
    {
      ret = check_name64(data, filename);
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
      objdump64(data, filename);
    }
  return (0);
}

int	main(int ac, char **av)
{
  int	ret;
  char	*bin;

  ret = 0;
  if (ac < 1)
    return (-1);
  bin = av[0];
  if (ac > 1)
    {
      for (int i = 1; i < ac; i++)
	if (objdump(av[i], bin) == -1)
	  ret = 1;
    }
  else if (objdump("a.out", bin) == -1)
    ret = 1;
  return (ret);
}
