#include "assembler.h"

static int     read_lines(int fd, t_env *env)
{
	int		ret;
    int     error;

    error = 0;
	while ((ret = get_next_line(fd, &env->line)) > 0)
	{
        if (parse_line(env))
            error = 1;
        env->line_number++;
		free(env->line);
	}
	free(env->line);
    return (ret == -1 || error);
}

int			parse_file(t_env *env, char *fname)
{
    int     fd;
    int     error;

    error = 0;
    fd = open(fname, O_RDONLY);
    if (fd > 0)
    {
        error = read_lines(fd, env);
        close(fd);
    }
    else
    {
        error = 1;
        perror("asm");
    }
    return (!error);
}