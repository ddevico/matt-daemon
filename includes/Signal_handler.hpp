/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_handler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:07:11 by ddevico           #+#    #+#             */
/*   Updated: 2018/01/09 08:52:49 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_HPP
# define SIGNAL_HANDLER_HPP

#include <csignal>
#include <unistd.h>
#include <iostream>
#include <string>
#include "Tintin_reporter.hpp"

class Signal_handler
{
	public:
		Signal_handler();
		Signal_handler(const Signal_handler &copy);
		~Signal_handler();
		Signal_handler &operator = (const Signal_handler &src);
		static void signal_handler(int sig);
		void sig();
};

#endif
