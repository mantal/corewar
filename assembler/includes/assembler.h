#ifndef H_ASSEMBLER
# define H_ASSEMBLER
# include "libft.h"
# include "ftstring.h"
# include "ft_get_next.h"
# include "ftio.h"
# include "op.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define LABEL_LENGTH 32
# define PARAM_LENGTH (LABEL_LENGTH + 1)

extern t_op		g_op_tab[17];

typedef struct	s_label
{
	char		name[LABEL_LENGTH];
	int			offset;
}				t_label;

typedef struct	s_param
{
	char		value[PARAM_LENGTH];
	long		integer_value;
	char		type;
	char		required_bytes;
}				t_param;

typedef struct	s_inst
{
	int			index;
	t_param		params[4]; // TODO: Figure out params count
	int			offset;
	int			line_number;
}               t_inst;

typedef struct  s_env
{
    t_header    header;
    int         current_offset;
    t_inst      current_instruction;
	t_list		*instructions;
	t_list		*labels;
	char		*line;
	int			line_number;
}               t_env;

t_env           *init_data(void);
int 			parse_file(t_env *env, char *fname);
int             parse_line(t_env *env);
int             parse_instructions(t_env *env, char *data);
bool	        is_comment_char(char c);
bool        	is_whitespace(char c);
int		        count_whitespace_offset(char *str);
int		        cout_word_offset(char *str);
bool	        is_end_of_line(char *line);
int				count_word_offset(char *str);
int             error_space_expected(t_env *env, char *line);
int             error_opening_quote_expected(t_env *env);
int             error_closing_quote_expected(t_env *env);
int             error_string_too_long(t_env *env, int max_length);
int             error_unexpected_characters(t_env *env, char *end);
int             error_duplicate_symbol(t_env *env, char *type);
int             error_label_expected(t_env *env, char *end);
char    		*error_wrong_param_number(t_env *env);
int				error_invalid_parameter_format(t_env *env, char *pos, int i);
int				parse_parameters(t_env *env, char *data);
t_list	        *list_add(t_list **list, void const *content, size_t content_size);
int             is_data_correct(t_env *env);
int				check_instructions(t_list *list, t_list *labels);
char			*get_param_type(t_inst *inst, int i);
int             error_wrong_param_type(t_inst *inst, int index);
long int		ft_atoli(char *str);
int				error_wrong_param_number_impl(t_inst *instruction, int line_number);
int             error_label_not_found(t_inst *inst, int offset, int index);
int				write_output(t_env *env, char *fname);
void			encode_inst(t_inst *inst, char *data, int *pos);
#endif