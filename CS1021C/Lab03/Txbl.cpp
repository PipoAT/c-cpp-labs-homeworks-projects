#include <iostream>
#include <string>
#include <iomanip>

/**
 * @brief Truncate a string to a certain length.
 *
 * @param value The string to truncate.
 * @param width The length to which to truncate \p value.
 * @return std::string The truncated string.
 */
std::string truncate_string(const std::string &value, int width) {
  return value.substr(0, width);
}

/**
 * @brief Get an integer from the user
 *
 * @return int The user's input, as an integer.
 */
int get_int() {
  int value{0};
  std::cin >> value;
  return value;
}

/**
 * @brief Get a string from the user.
 *
 * @return std::string The user's input, as a string.
 */
std::string get_string() {
  std::string value{""};
  std::getline(std::cin, value);
  return value;
}

int main() { 

	double creditperkwH{ 0.018 };
	double profitperkwH{ 0.114951 };


	std::string companyname;
	double energygeneration;
	double solargeneration;
	double windgeneration;
	double hydrogeneration;
	double sharesoutstanding;
	double renewabletotal;
	double totaltaxcredit;
	double revenue;
	double totaltaxablerevenue;
	double taxrevpershare;

	std::cout << "Enter company name: ";
	std::getline(std::cin, companyname);
	companyname = truncate_string(companyname, 40);

	std::cout << "Enter the total energy generation (in kwH): ";
	std::cin >> energygeneration;

	std::cout << "Enter solar generation (in kwH): ";
	std::cin >> solargeneration;

	std::cout << "Enter wind generation (in kwH): ";
	std::cin >> windgeneration;

	std::cout << "Enter hydro generation (in kwH): ";
	std::cin >> hydrogeneration;

	std::cout << "Enter shares outstanding: ";
	std::cin >> sharesoutstanding;

	renewabletotal = (solargeneration + windgeneration + hydrogeneration);
	totaltaxcredit = renewabletotal * creditperkwH;
	revenue = energygeneration * profitperkwH;
	totaltaxablerevenue = revenue - totaltaxcredit;
	taxrevpershare = totaltaxablerevenue / sharesoutstanding;

	std::cout << "Revenue Per Share Report Generator" << std::endl;
	std::cout << std::setfill('=') << std::setw(80) << "" << "\n";
	std::cout << "Prepared For: " << std::right << std::setfill(' ') << std::setw(66) << companyname << std::endl;
	std::cout << "Taxable Total Revenue: " << std::right << std::setw(57) << std::fixed << std::setprecision(2) << totaltaxablerevenue << std::endl;
	std::cout << "Taxable Revenue Per Share: " << std::right << std::setw(53) << std::fixed << std::setprecision(2) << taxrevpershare << std::endl;
	std::cout << std::setfill('=') << std::setw(80) << "" << "\n";
	
	return 0;
}
