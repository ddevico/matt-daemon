/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signal_handler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:07:11 by ddevico           #+#    #+#             */
/*   Updated: 2018/01/09 09:16:43 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Signal_handler.hpp"

Signal_handler::Signal_handler()
{
}

Signal_handler::Signal_handler(const Signal_handler &src)
{
	*this = src;
}

Signal_handler::~Signal_handler()
{
}

Signal_handler &Signal_handler::operator = (const Signal_handler &src)
{
	(void)src;
	return (*this);
}

void Signal_handler::signal_handler(int sig)
{
	unlink("/var/lock/matt_daemon.lock");
	try
	{
		Tintin_reporter reporter("/var/log/matt_daemon/matt_daemon.log");
		std::string signame = "UNKNOWN";
		if (sig == SIGHUP)
			signame = "SIGHUP";
		else if (sig == SIGINT)
			signame = "SIGINT";
		else if (sig == SIGQUIT)
			signame = "SIGQUIT";
		else if (sig == SIGILL)
			signame = "SIGILL";
		else if (sig == SIGABRT)
			signame = "SIGABRT";
		else if (sig == SIGFPE)
			signame = "SIGFPE";
		else if (sig == SIGKILL)
			signame = "SIGKILL";
		else if (sig == SIGSEGV)
			signame = "SIGSEGV";
		else if (sig == SIGPIPE)
			signame = "SIGPIPE";
		else if (sig == SIGALRM)
			signame = "SIGALRM";
		else if (sig == SIGTERM)
			signame = "SIGTERM";
		else if (sig == SIGUSR1)
			signame = "SIGUSR1";
		else if (sig == SIGUSR2)
			signame = "SIGUSR2";
		else if (sig == SIGCHLD)
			signame = "SIGCHLD";
		else if (sig == SIGCONT)
			signame = "SIGCONT";
		else if (sig == SIGSTOP)
			signame = "SIGSTOP";
		else if (sig == SIGTSTP)
			signame = "SIGTSTP";
		else if (sig == SIGTTIN)
			signame = "SIGTTIN";
		else if (sig == SIGTTOU)
			signame = "SIGTTOU";
		else if (sig == SIGBUS)
			signame = "SIGBUS";
		//else if (sig == SIGPOLL)
			//signame = "SIGPOLL";
		else if (sig == SIGPROF)
			signame = "SIGPROF";
		else if (sig == SIGSYS)
			signame = "SIGSYS";
		else if (sig == SIGTRAP)
			signame = "SIGTRAP";
		else if (sig == SIGURG)
			signame = "SIGURG";
		else if (sig == SIGVTALRM)
			signame = "SIGVTALRM";
		else if (sig == SIGXCPU)
			signame = "SIGXCPU";
		else if (sig == SIGXFSZ)
			signame = "SIGXFSZ";
		else if (sig == SIGIOT)
			signame = "SIGIOT";
		//else if (sig == SIGSTKFLT)
			//signame = "SIGSTKFLT";
		else if (sig == SIGIO)
			signame = "SIGIO";
		//else if (sig == SIGCLD)
			//signame = "SIGCLD";
		//else if (sig == SIGPWR)
			//signame = "SIGPWR";
		else if (sig == SIGWINCH)
			signame = "SIGWINCH";
		//else if (sig == SIGUNUSED)
		//	signame = "SIGUNUSED";
		reporter.print_log("ERROR", "Signal handler");
		reporter.print_log("INFO", "Quitting");
	}
	catch (std::exception &e)
	{
		std::cerr << "Can't append signal /var/log/matt_daemon/matt_daemon.log" << std::endl;
	}
	unlink("/var/lock/matt_daemon.lock");
	exit(EXIT_FAILURE);
}

void Signal_handler::sig()
{
	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGILL, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGFPE, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGPIPE, signal_handler);
	signal(SIGALRM, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGCHLD, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGSTOP, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGTTIN, signal_handler);
	signal(SIGTTOU, signal_handler);
	signal(SIGBUS, signal_handler);
	//signal(SIGPOLL, signal_handler);
	signal(SIGPROF, signal_handler);
	signal(SIGSYS, signal_handler);
	signal(SIGTRAP, signal_handler);
	signal(SIGURG, signal_handler);
	signal(SIGVTALRM, signal_handler);
	signal(SIGXCPU, signal_handler);
	signal(SIGXFSZ, signal_handler);
	signal(SIGIOT, signal_handler);
	//signal(SIGSTKFLT, signal_handler);
	signal(SIGIO, signal_handler);
	//signal(SIGCLD, signal_handler);
	//signal(SIGPWR, signal_handler);
	signal(SIGWINCH, signal_handler);
	//signal(SIGUNUSED, signal_handler);
}
