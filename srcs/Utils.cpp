#include "../include/Utils.hpp"
#include "../include/Colors.hpp"

void	ft::print_f_all(std::string string)
{
	// std::ofstream myfile;
	// myfile.open("LISTE_MSG_CLIENT.txt");
	// for (int i = 0; text[i]; i++)
	// {
	// 	if (isprint(text[i]))
	// 		myfile << text[i];
	// 	else if (static_cast<int>(static_cast<unsigned char>(text[i])) == 13)
	// 		myfile << "<CR>";
	// 	else if (static_cast<int>(static_cast<unsigned char>(text[i])) == 10)
	// 		myfile << "<LF>";
	// 	else
	// 		myfile << "\\Ox" << std::hex << static_cast<int>(static_cast<unsigned char>(text[i]));
	// }
	// myfile << "\n";
	// myfile.close();
	const char * text = string.c_str();
	for (int i = 0; text[i]; i++)
	{
		if (isprint(text[i]))
			std::cout << text[i];
		else if (static_cast<int>(static_cast<unsigned char>(text[i])) == 13)
			std::cout << DARKVIOLET << "<CR>" << RESET;
		else if (static_cast<int>(static_cast<unsigned char>(text[i])) == 10)
			std::cout << DARKVIOLET << "<LF>" << RESET;
		else
			std::cout << "\\Ox" << std::hex << static_cast<int>(static_cast<unsigned char>(text[i]));
	}
}

void	ft::write_f_all(char * text)
{
	std::ofstream myfile;
	myfile.open("LISTE_MSG_CLIENT.txt", std::ios_base::app);
	for (int i = 0; text[i]; i++)
	{
		if (isprint(text[i]))
			myfile << text[i];
		else if (static_cast<int>(static_cast<unsigned char>(text[i])) == 13)
			myfile << "<CR>";
		else if (static_cast<int>(static_cast<unsigned char>(text[i])) == 10)
			myfile << "<LF>";
		else
			myfile << "\\Ox" << std::hex << static_cast<int>(static_cast<unsigned char>(text[i]));
	}
	myfile << "\n";
	myfile.close();
}

std::string		ft::strToUpper(std::string str_target)
{
	std::string s(str_target);
	std::string::iterator current = s.begin();
	for (std::string::iterator it = str_target.begin(); it != str_target.end(); it++, current++)
		*current = toupper(*it);
	return s;
}

std::vector<std::string> ft::split(std::string str, std::string delimiter)
{
	std::vector<std::string> values = std::vector<std::string>();
	size_t position;

	while ((position = str.find(delimiter)) != std::string::npos)
	{
		values.push_back(str.substr(0, position));
		str.erase(0, position + delimiter.length());
	}
	values.push_back(str);

	return values;
}

// Probablement a virer, je sais plus pk cest la ^^'
void ft::error(std::string message, bool stop)
{
	std::cerr << RED << "error: " << message << RESET << std::endl;
	if (stop)
		throw std::runtime_error(std::string("socket failed"));
}

std::string		ft::intToStr(int n)
{
	char		buffer[2];
	std::string	ret;
	size_t		val;

	buffer[1] = '\0';
	if (n < 0)
	{
		val = n * -1;
		ret + "-";
	}
	else
		val = n;
	while (ret.empty() || val > 0)
	{
		buffer[0] = val % 10 + '0';
		ret.insert(0, buffer);
		val /= 10;
	}
	return (ret);
};
