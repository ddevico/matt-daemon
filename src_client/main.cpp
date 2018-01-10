/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:07:11 by ddevico           #+#    #+#             */
/*   Updated: 2018/01/10 13:16:45 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tintin_reporter.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = strlen(s1) + strlen(s2);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	strcpy(str, s1);
	strcat(str, s2);
	return (str);
}

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_putstr(std::string str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putendl(std::string str)
{
	ft_putstr(str);
	write(1, "\n", 1);
}

static int				login_password(char **login)
{
	char				*line;
	char				*line2;
	int					ret;

	line = (char *)malloc(sizeof(char)* 1000);
	if (!(line = (char *)malloc(sizeof(char)* 1000)))
		exit(0);
	if (!(line2 = (char *)malloc(sizeof(char)* 1000)))
		exit(0);
	ft_putendl("Login:");
	ret = read(0, line, 999);
	line[ret - 1] = '\0';
	*login = strdup(line);
	ft_putendl("Password:");
	ret = read(0, line2, 999);
	line2[ret - 1] = '\0';
	line = ft_strjoin(line, ":");
	line = ft_strjoin(line, line2);
	/*send(sock, line, strlen(line) + 1, 0);
	recv(sock, line, 1023, 0);
	ft_putstr(line);
	if (strcmp(line, "ERROR"))
	{
		ft_putendl("ERROR: Wrong pass ...");
		exit(1);
	}*/
	if ((strcmp("admin:admin", line)) && (strcmp("admin:admin\n",
		line)))
	{
		ft_putstr("Password failed ");
		exit (0);
	}
	ft_putstr("Welcome ");
	ft_putendl(*login);
	return (0);
}

int				print_error(std::string str)
{
	std::cout << str;
	return (-1);
}

int				check_arg1(char *arg)
{
	int port;

	port = atoi(arg);
	if (port > 49151 || port < 1024)
	{
		printf("Invalid port\n");
		return (-1);
	}
	return (0);
}

int		check_args_client(int port)
{
	if (port > 49151 || port < 1024)
	{
		printf("Invalid port\n");
		return (-1);
	}
	return (0);
}


int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if (strcmp(addr, "localhost") == 0)
		sprintf(addr, "127.0.0.1");
	if (port == 0)
		return (print_error("error: invalid port\n"));
	if ((proto = getprotobyname("TCP")) == NULL)
		return (print_error("error: getprotobyname() failed\n"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (print_error("error: socket() failed\n"));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		printf("Error: Connect error.\n");
		exit (-1);
	}
	printf("SUCCESS - Connected to server.\n");
	return (sock);
}

void	prompt(char *login)
{
	ft_putstr("[ ");
	ft_putstr(login);
	ft_putstr(" ] / >");
}

void	client_prompt(int sock, char *login)
{
	int		ret;
	char	buff[1000];

	while (1)
	{
		prompt(login);
		ret = read(0, buff, 999);
		buff[ret] = '\0';
		write(sock, buff, strlen(buff));
		if (strncmp(buff, "quit", 4) == 0)
			break ;
	}
}

int main(int argc, char **argv)
{
	int			port;
	int			sock;
	char		*login;

	if (argc != 3)
	{
		printf("Usage: [Address] [port]\n");
		exit(-1);
	}
	else
	{
		port = atoi(argv[2]);
		if (check_args_client(port) != 0)
			return (-1);
		sock = create_client(argv[1], port);
		if (login_password(&login) == -1)
			return (0);
		client_prompt(sock, login);
		close(sock);
	}
	return (0);
}
