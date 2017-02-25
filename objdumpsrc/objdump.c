/*
** objdump.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Feb 20 19:34:12 2017 Baptiste Veyssiere
** Last update Sat Feb 25 16:37:02 2017 Baptiste Veyssiere
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
  int	fd;
  long	fsize;
  void	*buffer;

  if ((fd = open(filename, O_RDONLY)) == -1)
    {
      fprintf(stderr, "%s: '%s': No such file\n", bin, filename);
      return (NULL);
    }
  if ((fsize = lseek(fd, 0, SEEK_END)) == -1)
    return (NULL);
  if ((buffer = mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
      return (NULL);
  if (close(fd) == -1)
    return (NULL);
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
      if (check_r((ret = check_name32(data, filename)), bin, filename))
	return (1);
      objdump32(data, filename);
    }
  else if (header->e_ident[EI_CLASS] == ELFCLASS64)
    {
      if (check_r((ret = check_name64(data, filename)), bin, filename))
	return (1);
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
