/*
** nm64.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump/nmsrc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Thu Feb 23 14:00:31 2017 Baptiste Veyssiere
** Last update Thu Feb 23 17:30:55 2017 Baptiste Veyssiere
*/

#include "nm.h"

static char	get_flag()
{
  return ('f');
}

static void	get_sections64(Elf64_Ehdr *data, Elf64_Shdr **strtab, Elf64_Shdr **symtab)
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

void	print_symbols(Elf64_Sym *symtab, char *strtab, Elf64_Ehdr *data, int nbr)
{
  char		*name;
  char		flag;
  Elf64_Shdr	*start;
  
  start = (Elf64_Shdr*)((void*)data + data->e_shoff);
  (void)start;
  for (int i = 0; i < nbr; i++)
    {
      name = strtab + symtab[i].st_name;
      if (name[0] == 0 || symtab[i].st_info == STT_FILE)
	continue;
      flag = get_flag();
      if (flag == 'U' || flag == 'w')
	printf("%17c", ' ');
      else
	printf("%016lx ", symtab[i].st_value);
      printf("%c %s\n", flag, name);
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
      fprintf(stderr, "%s: %s: no symbols\n", bin, filename);
      return ;
    }
  print_symbols((void*)data + symtab->sh_offset, (void*)data + strtab->sh_offset, data, symtab->sh_size / sizeof(Elf64_Sym));
}
