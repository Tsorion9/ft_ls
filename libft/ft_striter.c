/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:05:58 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/10 16:18:04 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char*))
{
	int		i;

	if (s && f)
	{
		i = 0;
		while (s[i] != '\0')
		{
			f(&s[i]);
			i++;
		}
	}
}
