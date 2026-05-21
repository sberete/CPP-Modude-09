#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string &str) const
{
	size_t start;
	size_t end;

	start = 0;
	while (start < str.size() && std::isspace(str[start]))
		start++;
	end = str.size();
	while (end > start && std::isspace(str[end - 1]))
		end--;
	return (str.substr(start, end - start));
}

double BitcoinExchange::toDouble(const std::string &str) const
{
	std::stringstream ss(str);
	double value;
	char c;

	ss >> value;
	if (ss.fail())
		throw std::runtime_error("Error: bad number.");
	if (ss >> c)
		throw std::runtime_error("Error: bad number.");
	return (value);
}

bool BitcoinExchange::isLeapYear(int year) const
{
	if (year % 400 == 0)
		return (true);
	if (year % 100 == 0)
		return (false);
	if (year % 4 == 0)
		return (true);
	return (false);
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	int year;
	int month;
	int day;
	int maxDays[12] = {31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31};

	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (int i = 0; i < 10; i++)
	{
		if (i != 4 && i != 7 && !std::isdigit(date[i]))
			return (false);
	}
	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return (false);
	if (isLeapYear(year))
		maxDays[1] = 29;
	if (day < 1 || day > maxDays[month - 1])
		return (false);
	return (true);
}

bool BitcoinExchange::isValidValueString(const std::string &value) const
{
	int dots;

	if (value.empty())
		return (false);
	dots = 0;
	for (size_t i = 0; i < value.size(); i++)
	{
		if (value[i] == '.')
			dots++;
		else if (value[i] == '-' || value[i] == '+')
		{
			if (i != 0)
				return (false);
		}
		else if (!std::isdigit(value[i]))
			return (false);
	}
	if (dots > 1)
		return (false);
	return (true);
}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	std::string line;
	std::string date;
	std::string value;

	if (!file.is_open())
		throw std::runtime_error("Error: could not open database.");
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		if (!std::getline(ss, date, ','))
			continue;
		if (!std::getline(ss, value))
			continue;
		date = trim(date);
		value = trim(value);
		if (isValidDate(date) && isValidValueString(value))
			_data[date] = toDouble(value);
	}
	if (_data.empty())
		throw std::runtime_error("Error: empty database.");
}

double BitcoinExchange::getRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it;

	it = _data.lower_bound(date);
	if (it != _data.end() && it->first == date)
		return (it->second);
	if (it == _data.begin())
		throw std::runtime_error("Error: no previous date in database.");
	--it;
	return (it->second);
}

void BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream file(filename.c_str());
	std::string line;
	std::string date;
	std::string value;
	double number;
	double rate;

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t pipe = line.find('|');
		if (pipe == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		date = trim(line.substr(0, pipe));
		value = trim(line.substr(pipe + 1));
		if (!isValidDate(date) || !isValidValueString(value))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		number = toDouble(value);
		if (number < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (number > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		rate = getRate(date);
		std::cout << date << " => " << number << " = "
			<< number * rate << std::endl;
	}
}