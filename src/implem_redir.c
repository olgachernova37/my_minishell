/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implamentation_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2025/10/24 00:00:00 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input_redir(t_rdrs *rdr)
{
    int	fd;

    fd = open(rdr->filename, O_RDONLY);
    if (fd < 0)
    {
        perror(rdr->filename);
        return (1);
    }
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

 int	handle_output_redir(t_rdrs *rdr)
{
    int	fd;

    fd = open(rdr->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror(rdr->filename);
        return (1);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

 int	handle_append_redir(t_rdrs *rdr)
{
    int	fd;

    fd = open(rdr->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror(rdr->filename);
        return (1);
    }
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

int	handle_heredoc_redir(t_rdrs *rdr)
{
    int	fd;

    fd = handle_heredoc(rdr->filename);
    if (fd < 0)
        return (1);
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

int	process_single_redir(t_rdrs *rdr)
{
    if (rdr->redir_type == TOKEN_RDR_IN)
        return (handle_input_redir(rdr));
    else if (rdr->redir_type == TOKEN_RDR_OUT)
        return (handle_output_redir(rdr));
    else if (rdr->redir_type == TOKEN_APPND)
        return (handle_append_redir(rdr));
    else if (rdr->redir_type == TOKEN_HERE)
        return (handle_heredoc_redir(rdr));
    return (0);
}

int	implamentation_redir(t_cmnd *cmnd)
{
    t_rdrs	*rdr;

    rdr = cmnd->rdrs;
    while (rdr)
    {
        if (process_single_redir(rdr) != 0)
            return (1);
        rdr = rdr->next;
    }
    return (0);
}
