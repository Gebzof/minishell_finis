/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:16:18 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/28 12:16:21 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmeb, size_t n);
void	*ft_realloc(void *ptr, size_t size, size_t old_size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_iswhitespace(char c);
char	*ft_itoa(int n);
char	*ft_ltoa(long n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	**ft_split_quote(char *str);
char	*ft_strchr(const char *s, int n);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strnstr(const char *little, const char *big, size_t len);
char	*ft_strrchr(const char*s, int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
long	ft_atol(const char *str);
char	**free_tabtab(char **str);
t_list	*ft_lstlast(t_list *lst);
char	*get_next_line(int fd);
void	ft_print_tab_tab_debug(char **tab);
int		ft_count_in_quotes(char *str, int *i);
int		ft_count_word_part(char *str, int *i);
int		ft_count_words(char *str);
char	*ft_extract_quoted_part(char *str, int *i, char quote, int *len);
char	*ft_extract_quoted(char *str, int *i, char quote);
char	*ft_extract_word(char *str, int *i);
char	*ft_extract_word_part(char *str, int *i, int *len);
char	*export_word_quote(char *str, int *i, char quote, int len);

#endif
