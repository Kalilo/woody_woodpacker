/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t00.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 10:03:31 by khansman          #+#    #+#             */
/*   Updated: 2017/11/23 10:03:32 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// includes
# include "../libft/includes/libft.h"

// structures
typedef struct		s_node
{
	unsigned long	frequency;
	struct s_node	*left;
	struct s_node	*right;
	unsigned char	value;
}					t_node;

// globals
t_node				*g_nodes[256 + 1];
int					g_last_node_pos;

void	error_quit(char *error_msg)
{
	ft_putstr("ERROR: ");
	ft_putendl(error_msg);
	exit(0);
}

t_node	*create_node(unsigned char value, unsigned long frequency)
{
	t_node		*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		error_quit("Insifficient memory");
	node->left = NULL;
	node->right = NULL;
	node->frequency = frequency;
	node->value = value;
	return node;
}

t_node	*join_nodes(t_node *left, t_node *right)
{
	t_node		*new_node;

	new_node = create_node(0, 0);
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

// int		get_last_node_pos(void)
// {
// 	int			k;

// 	k = 0;
// 	while (g_nodes[k])
// 		k++;
// 	return (k);
// }

// int		get_last_node_pos2(int start)
// {
// 	int			k;

// 	k = start;
// 	while (g_nodes[k])
// 		k++;
// 	return (k);
// }

// char	join_last_two_nodes(void)
// {
// 	int			k;
// 	t_node		*first_node;
// 	t_node		*second_node;

// 	if ((k = get_last_node_pos()) == 0)
// 		return (0);
// 	second_node = g_nodes[k];
// 	first_node = g_nodes[k - 1];
// 	if (second_node->frequency < first_node->frequency)
// 		first_node = join_nodes(second_node, first_node);
// 	else
// 		first_node = join_nodes(first_node, second_node);
// 	g_nodes[k] = NULL;
// 	g_nodes[k - 1] = first_node;
// 	return (1);
// }

// void	swap_nodes(int pos_a, int pos_b)
// {
// 	t_node		*tmp;

// 	tmp = g_nodes[pos_a];
// 	g_nodes[pos_a] = g_nodes[pos_b];
// 	g_nodes[pos_b] = tmp;
// }

// void	sort_nodes(void)
// {
// 	int			k;
// 	int			l;
// 	int			last;

// 	k = 0;
// 	last = get_last_node_pos();
// 	while (k + 1 <= last)
// 	{
// 		l = k + 1;
// 		while (l <= last)
// 		{
// 			if (g_nodes[k]->frequency < g_nodes[l]->frequency)
// 				swap_nodes(k, l);
// 			l++;
// 		}
// 		k++;
// 	}
// }

int		find_node_pos_from_value(unsigned char value)
{
	int		k;

	k = 0;
	while (g_nodes[k])
		if (g_nodes[k]->value == value)
			return (k);
	return (-1);
}

int		find_lowest_pos(void)
{
	int		k;
	int		lowest;

	k = 0;
	lowest = 0;
	while (g_nodes[k])
	{
		if (g_nodes[k] < g_nodes[lowest])
			lowest = k;
		k++;
	}
	return (lowest);
}

t_node	*extract_lowest(void)
{
	int		k;
	int		l;
	t_node	*node;

	k = find_lowest_pos();
	l = g_last_node_pos;
	node = g_nodes[k];
	g_nodes[k] = g_nodes[l];
	g_nodes[l] = NULL;
	g_last_node_pos--;
	return (node);
}

void	buid_tree(void)
{
	t_node	*first_node;
	t_node	*second_node;

	while (g_nodes[1])
	{
		first_node = extract_lowest();
		second_node = extract_lowest();
		g_nodes[++g_last_node_pos] = join_nodes(first_node, second_node);
	}
}

void	inc_node_freq(unsigned char value)
{
	int		k;

	if ((k = find_node_pos_from_value(value)) == -1)
		g_nodes[++g_last_node_pos] = create_node(value, 1);
	else
		g_nodes[k]->frequency++;
}
