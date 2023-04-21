#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/*
 * format_compression_ratio
 *
 * This function will properly format _compression_ratio_ according
 * to the specifications set forth in the lab document.
 *
 * input: a double, _compression_ratio_, that is the compression ratio
 *        to format.
 * output: a std::string that contains _compression_ratio_ properly
 *         formatted according to the specifications set forth in
 *         the lab document.
 */
std::string format_compression_ratio(double compression_ratio) {
	std::stringstream formatted_ss{};
	formatted_ss << std::fixed << std::setprecision(2) << compression_ratio;
	return formatted_ss.str();
}

/*
 * comp_string
 *
 * This formula takes a interger and a character and returns a string
 *
 * input: interger, character
 * output: a string
 */
std::string comp_string(int number, char character) {
	std::string comp{ "" };
	comp = std::to_string(number) + character;
	return comp.c_str();
}
/*
 * multiply_chars
 *
 * This function will properly format the outputs
 *
 * input: a double, _compression_ratio
 * output: a string
 */
std::string multiply_chars(int number, char character) {
	std::string temp{ "" };
	for (int i = 0; i < number; ++i) {
		temp.push_back(character);
	}
	return temp;
}

int main() {
	std::ifstream file;

	file.open("input.rle");
	if (!file.is_open()) {
		std::cout << "Could not open the file containing the compressed data!\n";
		return 0;
	}

	int n;
	char c;
	std::string compressed;
	std::string decompressed;
	while (!(std::iscntrl(file.peek())) && !file.eof()) {
		if (!(file >> n)) {
			std::cout << "Compressed data format error!\n";
			return 0;
		}

		if (file.eof()) {
			std::cout << "Compressed data format error!\n";
			return 0;
		}

		if (!(file >> c)) {
			std::cout << "Compressed data format error!\n";
			return 0;
		}
		if (file.eof()) {
			std::cout << "Compressed data format error!\n";
			return 0;
		}
		if (c == '-') {

			if (!(file >> c)) {
				std::cout << "Compressed data format error!\n";
				return 0;
			}

			compressed += comp_string(n, '-');
			compressed += c;
		}

		else {
			compressed += comp_string(n, c);
		}
		decompressed += multiply_chars(n, c);
	}
	file.close();
	double comp_ratio = static_cast<double>(decompressed.length()) / compressed.length();
	std::cout << decompressed << std::endl;
	std::cout << format_compression_ratio(comp_ratio) << std::endl;
	return 0;
}
