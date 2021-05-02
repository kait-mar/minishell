#ifndef DOLLAR_SIGN_H
#define DOLLAR_SIGN_H

typedef struct  s_sign
{

    int     remove;
    int     space_front;
    int     space_back;
    int     on;
    int     valid;
    int     i;
    int     j;
    char    *s;
    char    *string;
    int     error;
}              t_sign;

int     count_escap(char *s);
char    *adding_escape(char *s, int count);
int     dollar_len(char *str, int i);
char    *take_word(char *str, int i, int len);
int    dollar_parsing(char *s);
t_sign	change_valid(t_sign lst, char *str, char **env);
char    *chang_dollar(char *s, char **env, int *on);
t_sign	change_dollar_helper(t_sign lst, char **str, char **env);
char    *realloc_input(char *str, char *s, int len, int string_len, int i);
t_sign	change_dollar_core(t_sign lst, char **str, char **env);
char    *take_away_dollar(char *s);
void    take_after_equal_support(char *s, int *i, int *k, int *j);
char    *take_after_equal(char *s);

#endif