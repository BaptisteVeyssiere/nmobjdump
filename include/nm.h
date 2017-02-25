/*
** nm.h for nm in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_nmobjdump/include
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Thu Feb 23 14:02:52 2017 Baptiste Veyssiere
** Last update Fri Feb 24 20:12:35 2017 Baptiste Veyssiere
*/

#ifndef NM_H_
# define NM_H_

#include <elf.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

int	check_file(Elf32_Ehdr*, char*, char*);
int	nm(char*, char*);
  
void	nm64(void*, char*, char*);
void	nm32(void*, char*, char*);

int	is_arfile(void*, char*);

int	check_name64(Elf64_Ehdr*, char*);
int	check_name32(Elf32_Ehdr*, char*);

char	get_flag64(Elf64_Sym*, Elf64_Shdr*);

#endif /* !NM_H_ */
