/*
** objdump64.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Feb 20 19:45:00 2017 Baptiste Veyssiere
** Last update Thu Feb 23 00:47:48 2017 Baptiste Veyssiere
*/

#include "objdump.h"

static void	get_flags(Elf64_Ehdr *data)
{
  if (data->e_type == ET_REL)
    data->e_flags |= HAS_RELOC;
  else if (data->e_type == ET_EXEC)
    data->e_flags |= EXEC_P;
  else if (data->e_type == ET_DYN)
    data->e_flags |= DYNAMIC;

  if (has_symtab64(data))
    data->e_flags |= HAS_SYMS;
  if (has_paged64(data))
    data->e_flags |= D_PAGED;
}

static void	print_string(unsigned int i, char *buffer, unsigned int *newline)
{
  printf(" ");
  while (*newline < i)
    {
      if (isprint(buffer[*newline]))
	printf("%c", buffer[*newline]);
      else
	printf(".");
      ++(*newline);
    }
  while ((*newline)++ % 16)
    printf(" ");
  *newline = i;
  printf("\n");
}

static void	print_section64(Elf64_Ehdr *data, Elf64_Shdr section_header)
{
  char	*buffer;
  int	address;
  unsigned int	newline;
  unsigned int	i;

  newline = 0;
  address = section_header.sh_addr;
  buffer = (char*)((char*)data + section_header.sh_offset);
  i = 0;
  while (i < section_header.sh_size)
    {
      printf(" %04x ", address);
      for (unsigned int j = 0; j < 4; j++)
	{
	  for (unsigned int k = 0; k < 4; k++)
	    if (i < section_header.sh_size)
	      printf("%02x", ((unsigned char*)buffer)[i++]);
	    else
	      printf("  ");
	  printf(" ");
	}
      address += 16;
      print_string(i, buffer, &newline);
    }
}

static void	print_sections64(Elf64_Ehdr *data)
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
      if (strcmp(name, ".strtab") == 0 ||
	  strcmp(name, ".shstrtab") == 0 ||
	  strcmp(name, ".symtab") == 0 ||
	  strcmp(name, ".bss") == 0 ||
	  strcmp(name, ".rela.text") == 0 ||
	  strcmp(name, ".rela.eh_frame") == 0 ||
	  section_header.sh_size == 0)
	continue;
      printf("Contents of section %s:\n", name);
      print_section64(data, section_header);
    }
}

void	objdump64(void *data, char *filename)
{
  Elf64_Ehdr	*header;
  char		*architecture;

  header = (Elf64_Ehdr*)data;
  if (!header)
    return ;
  if (header->e_machine == EM_X86_64)
    architecture = "i386:x86-64";
  else if (header->e_machine == EM_386)
    architecture = "i386";
  else
    architecture = "notf";
  get_flags(header);
  printf("\n%s:     file format elf64-x86-64\n", filename);
  printf("architecture: %s, flags 0x%08x:\n", architecture, header->e_flags);
  print_flags(header->e_flags);
  printf("start address 0x%016x\n\n", (int)header->e_entry);
  print_sections64(data);
}
