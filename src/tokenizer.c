/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/10/23 17:02:58 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// t_input	*alloc_new_node(void)
// {
//     t_input *node;

//     node = malloc(sizeof(t_input));
//     if (node == NULL)
//         return (NULL);
//     node->word = NULL;
//     node->next = NULL;
//     node->type = -1;
//     return (node);
// }

// char	*extract_word(char *input, t_len_type_qts *ltq)
// {
//     int				i;
//     char			*res;
//     t_quote_state	*state;

//     i = 0;
//     state = NULL;
//     res = malloc(sizeof(char) * (ltq->len - ltq->qts + 1));
//     if (res == NULL)
//         return (NULL);
//     while (input && i < (ltq->len - ltq->qts))
//     {
//         state = dtct_inquotes(*input);
//         if ((state->inquotes && state->type == *input) || state->closed)
//             input++;
//         else
//             res[i++] = *input++;
//     }
//     res[i] = '\0';
//     reset_state_sttc(state);
//     return (res);
// }

// t_input	*do_node(t_len_type_qts *ltq, char *input)
// {
//     t_input	*new_node;
//     char	*res;

//     if (!input || !ltq)
//         return (NULL);
//     new_node = alloc_new_node();
//     if (new_node == NULL)
//         return (NULL);
//     res = extract_word(input, ltq);
//     if (res == NULL)
//     {
//         free(new_node);
//         return (NULL);
//     }
//     new_node->word = res;
//     new_node->next = NULL;
//     if (ltq->qts)
//         new_node->type = TOKEN_COMPLEX;
//     else
//         new_node->type = ltq->type;
//     return (new_node);
// }


// every uninquoted qutes should be skipped
// probably should be added free(words) if (words != NULL)
t_input	*do_node(t_len_type_qts *ltq, char *input)
{
	int				i;
	char			*res;
	t_input			*new_node;
	t_quote_state	*state;

	i = 0;
	state = NULL;
	new_node = malloc(sizeof(t_input));
	if (new_node == NULL || !input)
		return (NULL);
	res = malloc(sizeof(char) * (ltq->len - ltq->qts + 1));
	if (res == NULL)
	{
		free(new_node);
		return (NULL);
	}
	while (input && i < (ltq->len - ltq->qts))
	{
		state = dtct_inquotes(*input);
		if ((state->inquotes && state->type == *input) || state->closed)
			input++;
		else
			res[i++] = *input++;
	}
	res[i] = '\0';
	new_node->word = res;
	new_node->next = NULL;
	if (ltq->qts)
		new_node->type = TOKEN_COMPLEX;
	else
		new_node->type = ltq->type;
	reset_state_sttc(state);
	return (new_node);
}

void	add_node(t_input **words, t_input *new_word)
{
	t_input	*tmp;

	if (!words || !new_word)
		return ;
	if (*words == NULL)
	{
		*words = new_word;
		return ;
	}
	tmp = *words;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_word;
}

int	creat_tokenz(char *input, t_input **words)
{
	t_len_type_qts	*ltq;
	int				cnsmd;

	ltq = malloc(sizeof(t_len_type_qts));
	if (!ltq)
		exit(1);
	ltq->qts = 0;
	ltq->len = 0;
	ltq->type = -1;
	if (*input == '|')
		add_node(words, do_node(tk_pipe(input, ltq), input));
	else if (*input == '>')
		add_node(words, do_node(tk_out_appnd(input, ltq), input));
	else if (*input == '<')
		add_node(words, do_node(tk_in_here(input, ltq), input));
	else
		add_node(words, do_node(tk_word(input, ltq), input));
	cnsmd = ltq->len;
	free(ltq);
	return (cnsmd);
}

t_input	*tokenize(t_input *words, char *input)
{
	int res;

	res = 0;
	while (*input)
	{
		if (*input != ' ' && *input != '\t')
		{
			res = creat_tokenz(input, &words);
			input += res;
		}
		else
			input++;
	}
	return (words);
}
