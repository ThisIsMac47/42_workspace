/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarchau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:17:33 by vmarchau          #+#    #+#             */
/*   Updated: 2016/03/22 14:16:54 by vmarchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_term(t_global *gbl)
{
	t_env		*entry;
	t_termios	term;

	(void)gbl;
	entry = find_entry(gbl, "TERM");
	if (entry == NULL)
		return (ft_putstr_fd("Term type not found in env, no termcaps\n", 2));
	if (tgetent(NULL, entry->value) != 1)
		return (ft_putstr_fd("Term not valid, no termcaps", 2));
	if (tcgetattr(0, &term) == -1)
		return (ft_putstr_fd("Error while get attr of term, no termcaps\n", 2));
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if ((tcsetattr(0, TCSADRAIN, &term)) == -1)
		return (ft_putstr_fd("Error while set attr of term, not termcaps", 2));
}

void	reset_term(t_global *gbl)
{
	t_termios	term;

	(void)gbl;
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return ;
}

char	*handle_input(t_global *gbl, char *input, char *line)
{
	char	*tmp;

	(void)gbl;
	if (ISKEYLEFT(input) && ft_strlen(line) > 0)
		ft_putstr(tgetstr("le", NULL));
	else if (ISKEYRIGHT(input))
		ft_putstr(tgetstr("nd", NULL));
	else if (ft_isprint(input[0]) || input[0] == '\n')
	{
		tmp = line;
		line = ft_strjoin(line, input);
		free(tmp);
		ft_putstr(input);
	}
	return (line);
}
