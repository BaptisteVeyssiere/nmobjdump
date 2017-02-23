/*
** nm.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump/nmsrc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Thu Feb 23 13:54:45 2017 Baptiste Veyssiere
** Last update Thu Feb 23 16:34:48 2017 Baptiste Veyssiere
*/

#include "nm.h"

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

int	nm(char *filename, char *bin)
{
  void		*data;
  Elf32_Ehdr	*header;
  
  if (!(data = getdata(filename, bin)))
    return (-1);
  header = (Elf32_Ehdr*)data;
  if (is_arfile(data, bin))
    return (0); 
  else if (check_file(header, filename, bin))
    return (1);
  if (header->e_ident[EI_CLASS] == ELFCLASS32)
    {
      if (check_name32(data))
	{
	  fprintf(stderr, "%s: %s: File format not recognized\n", bin, filename);
	  return (1);
	}
      nm32(data, filename, bin);
    }
  else if (header->e_ident[EI_CLASS] == ELFCLASS64)
    {
      if (check_name64(data))
	{
	  fprintf(stderr, "%s: %s: File format not recognized\n", bin, filename);
	  return (1);
	}
      nm64(data, filename, bin);
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
  if (av[0][0] == '.')
    bin = av[0] + 2;
  else
    bin = av[0];
  if (ac > 1)
    {
      for (int i = 1; i < ac; i++)
	if (nm(av[i], bin) == -1)
	  ret = 1;
    }
  else if (nm("a.out", bin) == -1)
    ret = 1;
  return (ret);
}
