/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:07:11 by ddevico           #+#    #+#             */
/*   Updated: 2018/01/08 11:36:15 by ddevico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int main()
{
	if (getuid())
	{
		std::cerr << "You must run matt_daemon as root" << std::endl;
		return (EXIT_FAILURE);
	}
	int lol = fork();
	if (lol == -1)
		std::cerr << "Failed to create daemon" << std::endl;
	else if (lol == 0)
		//run(lockfd);
	return (EXIT_SUCCESS);
}
