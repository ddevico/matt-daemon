/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tintin_reporter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:07:11 by ddevico           #+#    #+#             */
/*   Updated: 2018/01/09 08:56:10 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TINTIN_REPORTER_HPP
# define TINTIN_REPORTER_HPP

#include <iostream>
#include <ctime>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <vector>
#include <csignal>
#include <poll.h>
#include <netdb.h>

class Tintin_reporter
{
	private:
		int file;
		void append(std::string type, std::string str);

	public:
		std::string filename;
		Tintin_reporter(std::string filename);
		Tintin_reporter(const Tintin_reporter &src);
		~Tintin_reporter();
		Tintin_reporter &operator = (const Tintin_reporter &src);
		void print_log(std::string types, std::string str);
};

#endif
