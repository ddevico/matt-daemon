/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:07:11 by ddevico           #+#    #+#             */
/*   Updated: 2018/01/10 14:00:35 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tintin_reporter.hpp"
#include "Signal_handler.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <csignal>
#include <poll.h>

Tintin_reporter *reporter = NULL;
int flag = 0;

void				test_pass(int sock)
{
	int		ret;
	char	buff[1024];

	ret = 0;
	buff[0] = '\0';
	reporter->print_log("INFO", "Enter");
	while ((ret = recv(sock, &buff, 999, 0)) > 0)
	{
		if (!(strcmp("admin:admin", buff)) && !(strcmp("admin:admin\n",
			buff)))
		{
			reporter->print_log("ERROR", "Password incorrect");
			exit(0);
		}
		else
		{
			reporter->print_log("INFO", "Password good");
			return ;
		}
	}
}

void listen(int sock)
{
	struct pollfd tmp;
	std::vector<struct pollfd> polls;
	std::vector<int> clients;
	std::vector<std::string> datas;
	//reporter->print_log("INFO", "Entering Daemon mode");
	//reporter->print_log("INFO", "started. PID: " + std::to_string(getpid()));
	while (true)
	{
		struct sockaddr sa;
		socklen_t sl;
		int newsock;
		if ((newsock = accept(sock, &sa, &sl)) == -1)
		{
			if (errno != EWOULDBLOCK && errno != EAGAIN)
			{
				close(sock);
				reporter->print_log("ERROR", "Failed to accept new client on socket");
				return;
			}
			goto readClients;
		}
		if (clients.size() >= 3)
		{
			close(newsock);
			reporter->print_log("INFO", "Client number limit reached");
			goto readClients;
		}
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 100000;
		if (setsockopt(newsock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
		{
			close(sock);
			reporter->print_log("ERROR", "Failed setsockopt timeout");
			return;
		}
		reporter->print_log("INFO", "New client");
		clients.push_back(newsock);
		tmp.fd = newsock;
		tmp.events = POLLIN | POLLPRI;
		tmp.revents = 0;
		polls.push_back(tmp);
		datas.push_back(std::string());
readClients:
		poll(&polls.front(), polls.size(), 10);
		for (int i = 0; i < static_cast<int>(clients.size()); ++i)
		{
			ssize_t result;
			char res;
			while ((result = recv(clients[i], &res, 1, MSG_NOSIGNAL)) > 0)
			{
				if (res == '\n')
				{
					if (!datas[i].compare("quit"))
					{
						close(sock);
						reporter->print_log("INFO", "Request quit");
						return;
					}
					reporter->print_log("INFO", "User input: " + datas[i]);
					datas[i].clear();
				}
				else
					datas[i] += res;
			}
			if (result == 0 || (result == -1 && errno != EWOULDBLOCK && errno != EAGAIN))
			{
				reporter->print_log("INFO", "Client shutdown");
				clients.erase(clients.begin() + i);
				datas.erase(datas.begin() + i);
				i--;
			}
		}
	}
	close(sock);
}

int	connect_server()
{
	reporter->print_log("INFO", "Creating server");
	int sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		reporter->print_log("ERROR", "Failed to create socket");
		return (-1);
	}
	struct sockaddr_in server_addr;
	std::memset((char *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(4242);
	if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		close(sock);
		reporter->print_log("ERROR", "Failed to bind socket");
		return (-1);
	}
	if (listen(sock, 222) == -1)
	{
		close(sock);
		reporter->print_log("ERROR", "Failed to listen socket");
		return (-1);
	}
	int flags = fcntl(sock, F_GETFL, 0);
	if (flags < 0)
	{
		close(sock);
		reporter->print_log("ERROR", "Failed to set non blocking socket on client");
		return (-1);
	}
	flags |= O_NONBLOCK;
	if (fcntl(sock, F_SETFL, flags) == -1)
	{
		close(sock);
		reporter->print_log("ERROR", "Failed to set non blocking socket");
		return (-1);
	}
	reporter->print_log("INFO", "Server Created");
	return (sock);
}


bool checkdir()
{
	struct stat d4rkh4xx0r;
	if (stat("/var/log/matt_daemon", &d4rkh4xx0r) == -1)
	{
		if (mkdir("/var/log/matt_daemon", 0755) == -1)
		{
			try
			{
				std::cerr << "Can't create /var/log/matt_daemon directory" << std::endl;
			}
			catch (std::exception &e)
			{
				// None of my business
			}return (false);
		}
	}
	else if (!S_ISDIR(d4rkh4xx0r.st_mode))
	{
		try
		{
			std::cerr << "File /var/log/matt_daemon already exists and is not a directory" << std::endl;
		}
		catch (std::exception &e)
		{
			// None of my business
		}
		return (false);
	}
	return (true);
}

void run(int lockfd)
{
	int sock;
	if (setsid() == -1)
	{
		reporter->print_log("ERROR", "Can't setsid");
		exit(EXIT_FAILURE);
	}
	Signal_handler *signal_handler = new Signal_handler();
	signal_handler->sig();
	reporter->print_log("INFO", "Signals binded, sucessfully daemonized");
	sock = connect_server();
	listen(sock);
	if (flock(lockfd, LOCK_UN | LOCK_NB) == -1)
	{
		reporter->print_log("ERROR", "Can't unlock: /var/lock/matt_daemon.lock");
		exit(EXIT_FAILURE);
	}
	unlink("/var/lock/matt_daemon.lock");
	reporter->print_log("INFO", "Ended");
}

int main()
{
	int fd;

	if (getuid())
	{
		std::cerr << "You must run matt_daemon as root" << std::endl;
		return (EXIT_FAILURE);
	}
	if (!checkdir())
		exit(EXIT_FAILURE);
	try
	{
		if (chdir("/var/log/matt_daemon") == -1)
			system("mkdir \"/var/log/matt_daemon\"");
		reporter = new Tintin_reporter("/var/log/matt_daemon/matt_daemon.log");
	}
	catch (std::exception &e)
	{
		std::cerr << "Can't open /var/log/matt_daemon/matt_daemon.log" << std::endl;
		exit(EXIT_FAILURE);
	}
	reporter->print_log("INFO", "Started");
	if ((fd = open("/var/lock/matt_daemon.lock", O_CREAT | O_RDONLY, 0644)) == -1)
	{
		std::cerr << "Can't open: /var/lock/matt_daemon.lock" << std::endl;
		reporter->print_log("ERROR", "Can't open LockFile");
		reporter->print_log("INFO", "Quitting");
		exit(EXIT_FAILURE);
	}
	if (flock(fd, LOCK_EX | LOCK_NB) == -1)
	{
		std::cerr << "Can't lock: /var/lock/matt_daemon.lock" << std::endl;
		reporter->print_log("ERROR", "File is lock");
		reporter->print_log("INFO", "Quitting");
		exit(EXIT_FAILURE);
	}
	int pid = fork();
	if (pid == -1)
		std::cerr << "Error: Impossible to create daemon" << std::endl;
	else if (pid == 0)
		run(fd);
	return (EXIT_SUCCESS);
}
