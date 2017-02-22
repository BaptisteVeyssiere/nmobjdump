/*
** objdump32.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Tue Feb 21 11:54:14 2017 Baptiste Veyssiere
** Last update Tue Feb 21 12:01:57 2017 Baptiste Veyssiere
*/

#include "objdump.h"

static void	print_string(unsigned int i, char *buffer, unsigned int *newline)
{
  printf("  ");
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

static void	print_section32(Elf32_Ehdr *data, Elf32_Shdr section_header)
{
  char		*buffer;
  int		address;
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

static void	print_sections32(Elf32_Ehdr *data)
{
  Elf32_Shdr	*start;
  Elf32_Shdr	shstrtab_section;
  char		*namestring;
  Elf32_Shdr	section_header;
  char		*name;

  start = (Elf32_Shdr*)((void*)data + data->e_shoff);
  shstrtab_section = start[data->e_shstrndx];
  namestring = (char*)((void*)data + shstrtab_section.sh_offset);
  for (int i = 1; i < data->e_shnum; i++)
    {
      section_header = start[i];
      name = namestring + section_header.sh_name;
      if (strcmp(name, ".strtab") == 0 ||
	  strcmp(name, ".shstrtab") == 0 ||
	  strcmp(name, ".symtab") == 0 ||
	  strcmp(name, ".bss") == 0)
	continue;
      printf("Section content %s :\n", name);
      print_section32(data, section_header);
    }
}

void	objdump32(void *data, char *filename)
{
  Elf32_Ehdr	*header;
  char		*architecture;

  header = (Elf32_Ehdr*)data;
  if (header->e_machine == EM_X86_64)
    architecture = "i386:x86-64";
  if (header->e_machine == EM_386)
    architecture = "i386";
  else
    architecture = "notf";
  printf("\n%s:     file format elf32-i386\n", filename);
  printf("architecture: %s, flags 0x%08x:\n", architecture, header->e_flags);
  printf("start adress 0x%016x\n\n", (int)header->e_entry);
  print_sections32(data);
}
