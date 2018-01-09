/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tintin_reporter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddevico <ddevico@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:07:11 by ddevico           #+#    #+#             */
/*   Updated: 2018/01/09 09:19:44 by davydevico       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tintin_reporter.hpp"

Tintin_reporter::Tintin_reporter(std::string filename): filename(filename)
{
	if ((this->file = open(this->filename.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		throw std::exception();
}

Tintin_reporter::Tintin_reporter(const Tintin_reporter &src)
{
	this->filename = src.filename;
	if ((this->file = open(this->filename.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		throw std::exception();
}

Tintin_reporter::~Tintin_reporter()
{
	if (this->file)
		close(this->file);
}

Tintin_reporter &Tintin_reporter::operator = (const Tintin_reporter &src)
{
	this->filename = src.filename;
	if ((this->file = open(this->filename.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		throw std::exception();
	return (*this);
}

void Tintin_reporter::append(std::string type, std::string str)
{
	time_t 			t = time(NULL);
	struct 			tm *lti = localtime(&t);

	std::string day = lti->tm_mday < 10 ? "0" + std::to_string(lti->tm_mday) : std::to_string(lti->tm_mday);
	std::string month = lti->tm_mon < 10 ? "0" + std::to_string(lti->tm_mon + 1) : std::to_string(lti->tm_mon + 1);
	std::string hour = lti->tm_hour < 10 ? "0" + std::to_string(lti->tm_hour) : std::to_string(lti->tm_hour);
	std::string minute = lti->tm_min < 10 ? "0" + std::to_string(lti->tm_min) : std::to_string(lti->tm_min);
	std::string second = lti->tm_sec < 10 ? "0" + std::to_string(lti->tm_sec) : std::to_string(lti->tm_sec);
	std::string year = std::to_string(1900 + lti->tm_year);
	std::string printstr = "[" + day + "/" + month + "/" + year + " - " + hour + ":" + minute + ":" + second + "] [ " + type + " ] " + str + "\n";
	write(this->file, printstr.c_str(), printstr.length());
}

void Tintin_reporter::print_log(std::string type, std::string str)
{
	append(type, str);
}
