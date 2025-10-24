/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implem_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/24 00:00:00 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 char	*get_heredoc_filename(void)
{
    int	i = 0;
    char		*num;
    char		*filename;

    num = ft_itoa(i++);
    if (!num)
        return (NULL);
    filename = ft_strjoin("/tmp/.heredoc_", num);
    free(num);
    return (filename);
}

 void	heredoc_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_exit_status = 130;
        close(STDIN_FILENO);
    }
}

int	write_heredoc_content(int fd, char *delimiter)
{
    char	*line;
    size_t	delim_len;

    delim_len = ft_strlen(delimiter);
    signal(SIGINT, heredoc_signal_handler);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
            ft_putstr_fd("end-of-file (wanted `", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("')\n", 2);
            break ;
        }
        if (ft_strncmp(line, delimiter, delim_len) == 0
            && ft_strlen(line) == delim_len)
        {
            free(line);
            break ;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
    signal(SIGINT, handler_sig_int);
    return (0);
}

int	handle_heredoc(char *delimiter)
{
    char	*filename;
    int		fd;
    int		read_fd;

    filename = get_heredoc_filename();
    if (!filename)
        return (-1);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror(filename);
        free(filename);
        return (-1);
    }
    write_heredoc_content(fd, delimiter);
    close(fd);
    if (g_exit_status == 130)
    {
        unlink(filename);
        free(filename);
        return (-1);
    }
    read_fd = open(filename, O_RDONLY);
    unlink(filename);
    free(filename);
    return (read_fd);
}
