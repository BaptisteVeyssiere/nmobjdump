/*
** nm.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump/nmsrc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Thu Feb 23 13:54:45 2017 Baptiste Veyssiere
** Last update Sun Feb 26 19:20:53 2017 Baptiste Veyssiere
*/

#include "nm.h"

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
  if (header->e_ident[EI_MAG0] == 0 ||
      header->e_ident[EI_MAG1] == 0 ||
      header->e_ident[EI_MAG2] == 0 ||
      header->e_ident[EI_MAG3] == 0 ||
      header->e_type == 0)
    {
      fprintf(stderr, "%s: %s: File truncated\n", bin, file);
      return (1);
    }
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

static int	check_r(int ret, char *bin, char *filename, int multi)
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
  if (multi)
    printf("\n%s:\n", filename);
  return (0);
}

int	nm(char *filename, char *bin, int multi)
{
  void		*data;
  Elf32_Ehdr	*header;
  int		ret;

  if (!(data = getdata(filename, bin)))
    return (-1);
  header = (Elf32_Ehdr*)data;
  if (is_arfile(data, bin, multi, filename))
    return (0);
  else if (check_file(header, filename, bin))
    return (1);
  if (header->e_ident[EI_CLASS] == ELFCLASS32)
    {
      if (check_r((ret = check_name32(data, filename)), bin, filename, multi))
	return (1);
      nm32(data, filename, bin);
    }
  else if (header->e_ident[EI_CLASS] == ELFCLASS64)
    {
      if (check_r((ret = check_name64(data, filename)), bin, filename, multi))
	return (1);
      nm64(data, filename, bin);
    }
  return (0);
}

int	main(int ac, char **av)
{
  int	ret;
  char	*bin;
  int	multi;

  ret = 0;
  if (ac < 1)
    return (-1);
  bin = av[0];
  setlocale(LC_ALL, "");
  if (ac > 1)
    {
      multi = ac > 2 ? 1 : 0;
      for (int i = 1; i < ac; i++)
	if (nm(av[i], bin, multi) == -1)
	  ret = 1;
    }
  else if (nm("a.out", bin, 0) == -1)
    ret = 1;
  return (ret);
}
