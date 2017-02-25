/*
** nm64.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump/nmsrc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Thu Feb 23 14:00:31 2017 Baptiste Veyssiere
** Last update Sat Feb 25 16:19:46 2017 Baptiste Veyssiere
*/

#include "nm.h"

static int	get_lower(Elf64_Sym **tab, char *strtab, int nbr)
{
  int	ndx;
  char	*name_right;
  char	*name_left;

  ndx = -1;
  for (int i = 0; i < nbr; i++)
    if (tab[i] != NULL)
      {
	ndx = i;
	break;
      }
  if ((nbr - 1) == ndx || ndx == -1)
    return (ndx);
  for (int i = 1; i < nbr; i++)
    {
      if (tab[i] == NULL)
	continue;
      name_right = strtab + (tab[i])->st_name;
      name_left = strtab + (tab[ndx])->st_name;
      if (strcoll(name_left, name_right) > 0)
	ndx = i;
    }
  return (ndx);
}

static void	sort_tab(Elf64_Sym **tab, char *strtab, int nbr)
{
  Elf64_Sym	**tmp;
  int		j;
  int		i;

  if (!(tmp = malloc(sizeof(Elf64_Sym*) * (nbr + 1))))
    return ;
  tmp[nbr] = NULL;
  j = -1;
  while ((i = get_lower(tab, strtab, nbr)) > -1)
    {
      tmp[++j] = tab[i];
      tab[i] = NULL;
    }
  for (i = 0; i < nbr; i++)
    tab[i] = tmp[i];
  free(tmp);
}

static void	get_sections64(Elf64_Ehdr *data, Elf64_Shdr **strtab,
			       Elf64_Shdr **symtab)
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
      if (strcmp(name, ".symtab") == 0)
	*symtab = &start[i];
      else if (strcmp(name, ".strtab") == 0)
	*strtab = &start[i];
    }
}

static void	print_symbols(Elf64_Sym *symtab, char *strtab,
			      Elf64_Ehdr *data, int nbr)
{
  char		*name;
  Elf64_Shdr	*start;
  Elf64_Sym	**sorted_symtab;
  int		j;

  if (!(sorted_symtab = malloc(sizeof(Elf64_Sym*) * (nbr + 1))))
    return ;
  sorted_symtab[nbr] = NULL;
  start = (Elf64_Shdr*)((void*)data + data->e_shoff);
  j = -1;
  for (int i = 0; i < nbr; i++)
    {
      name = strtab + symtab[i].st_name;
      if (name[0] != 0 && symtab[i].st_info != STT_FILE)
	sorted_symtab[++j] = &(symtab[i]);
    }
  nbr = j + 1;
  sort_tab(sorted_symtab, strtab, nbr);
  for (int i = 0; i < nbr; i++)
    {
      name = strtab + sorted_symtab[i]->st_name;
      if (name[0] == 0 || sorted_symtab[i]->st_info == STT_FILE)
	continue;
      printer64(sorted_symtab[i], start, name);
    }
}

void	nm64(void *data, char *filename, char *bin)
{
  Elf64_Ehdr	*header;
  Elf64_Shdr	*symtab;
  Elf64_Shdr	*strtab;

  symtab = NULL;
  strtab = NULL;
  header = (Elf64_Ehdr*)data;
  if (!header)
    return ;
  get_sections64(data, &strtab, &symtab);
  if (strtab == NULL || symtab == NULL)
    {
      fprintf(stdout, "%s: %s: no symbols\n", bin, filename);
      return ;
    }
  print_symbols((void*)data + symtab->sh_offset, (void*)data +
		strtab->sh_offset, data, symtab->sh_size / sizeof(Elf64_Sym));
}
