/*
** flag.c for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Fri Feb 24 00:39:41 2017 Baptiste Veyssiere
** Last update Sat Feb 25 16:25:43 2017 Baptiste Veyssiere
*/

#include "nm.h"

char	get_flag64(Elf64_Sym *symtab, Elf64_Shdr *start)
{
  char	c;

  if (ELF64_ST_BIND(symtab->st_info) == STB_GNU_UNIQUE)
     c = 'u';
  if (ELF64_ST_BIND(symtab->st_info) == STB_WEAK)
    {
      c = 'W';
      if (symtab->st_shndx == SHN_UNDEF)
	c = 'w';
    }
  else if (ELF64_ST_BIND(symtab->st_info) == STB_WEAK &&
	   ELF64_ST_TYPE(symtab->st_info))
    {
      c = 'V';
      if (symtab->st_shndx == SHN_UNDEF)
	c = 'v';
    }
  else if (symtab->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (symtab->st_shndx == SHN_ABS)
    c = 'A';
  else if (symtab->st_shndx == SHN_COMMON)
    c = 'C';
  else if (start[symtab->st_shndx].sh_type == SHT_NOBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == SHF_ALLOC)
    c = 'R';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (start[symtab->st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  else
    c = '?';
  if (ELF64_ST_BIND(symtab->st_info) == STB_LOCAL && c != '?')
    c += 32;
  if ((start[symtab->st_shndx].sh_type == SHT_FINI_ARRAY ||
       start[symtab->st_shndx].sh_type == SHT_INIT_ARRAY) &&
      start[symtab->st_shndx].sh_flags == 3)
    c = 't';
  return (c);
}

char	get_flag32(Elf32_Sym *symtab, Elf32_Shdr *start)
{
  char	c;

  if (ELF32_ST_BIND(symtab->st_info) == STB_GNU_UNIQUE)
     c = 'u';
  if (ELF32_ST_BIND(symtab->st_info) == STB_WEAK)
    {
      c = 'W';
      if (symtab->st_shndx == SHN_UNDEF)
	c = 'w';
    }
  else if (ELF32_ST_BIND(symtab->st_info) == STB_WEAK &&
	   ELF32_ST_TYPE(symtab->st_info))
    {
      c = 'V';
      if (symtab->st_shndx == SHN_UNDEF)
	c = 'v';
    }
  else if (symtab->st_shndx == SHN_UNDEF)
    c = 'U';
  else if (symtab->st_shndx == SHN_ABS)
    c = 'A';
  else if (symtab->st_shndx == SHN_COMMON)
    c = 'C';
  else if (start[symtab->st_shndx].sh_type == SHT_NOBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'B';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == SHF_ALLOC)
    c = 'R';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
    c = 'D';
  else if (start[symtab->st_shndx].sh_type == SHT_PROGBITS &&
	   start[symtab->st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    c = 'T';
  else if (start[symtab->st_shndx].sh_type == SHT_DYNAMIC)
    c = 'D';
  else
    c = '?';
  if (ELF32_ST_BIND(symtab->st_info) == STB_LOCAL && c != '?')
    c += 32;
  if ((start[symtab->st_shndx].sh_type == SHT_FINI_ARRAY ||
       start[symtab->st_shndx].sh_type == SHT_INIT_ARRAY) &&
      start[symtab->st_shndx].sh_flags == 3)
    c = 't';
  return (c);
}
