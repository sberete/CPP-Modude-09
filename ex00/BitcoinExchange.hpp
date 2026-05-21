#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <cstdlib>
# include <stdexcept>
# include <cctype>

class BitcoinExchange
{
	private:
		std::map<std::string, double> _data;

		bool	isValidDate(const std::string &date) const;
		bool	isLeapYear(int year) const;
		bool	isValidValueString(const std::string &value) const;
		double	getRate(const std::string &date) const;
		double	toDouble(const std::string &str) const;
		std::string trim(const std::string &str) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	loadDatabase(const std::string &filename);
		void	processInput(const std::string &filename) const;
};

#endif