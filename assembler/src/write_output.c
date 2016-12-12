#include "assembler.h"

static char		*get_output_name(char *path, int path_len)
{
	char	new[path_len + 5];
	char	*tmp;

	ft_bzero(new, path_len + 5);
	ft_strcpy(new, path);
	if (!(tmp = ft_strrchr(new, '/')))
		tmp = new;
	if ((tmp = ft_strrchr(tmp, '.')))
		*tmp = '\0';
	ft_strcat(new, ".cor");
	return (ft_strdup(new));
}

static void		write_header(t_env *env, int fd)
{
	unsigned int	real_size;

	real_size = env->header.prog_size;
	env->header.magic = swap_uint(env->header.magic);
	env->header.prog_size = swap_uint(env->header.prog_size);
	write(fd, &env->header, sizeof(t_header));
	env->header.prog_size = real_size;
}

static void     write_instructions(t_env *env, int fd)
{
	char	data[env->header.prog_size + 3];
	t_list	*inst;
	int		i;

	i = 0;
	inst = env->instructions;
	ft_bzero(data, env->header.prog_size + 2);
	while (inst)
	{
		encode_inst((t_inst*)inst->content, data, &i);
		inst = inst->next;
	}
	write(fd, data, env->header.prog_size);
}

int	    		write_output(t_env *env, char *fname)
{
    char    *output;
    int		fd;

	if (!(output = get_output_name(fname, ft_strlen(fname))))
		return (0);
    if ((fd = open(output, O_CREAT | O_WRONLY, 0644)) < 0)
    {
        perror("asm");
		return (0);
    }
    write_header(env, fd);
    write_instructions(env, fd);
    (void)env;
    return (1);
}