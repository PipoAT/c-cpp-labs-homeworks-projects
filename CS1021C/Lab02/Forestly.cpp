#include <iostream>

double const CO_EMISSIONS_PER_ACRE{ 26.7 };

int main() {

	int year1;
	double acre1;
	int year2;
	double acre2;
	double percentvalue;
	double calculatedvalue;
	double calculatedvalue2;

	std::cout << "Enter the first year: ";
	std::cin >> year1;
	std::cout << "Enter the acres consumed by forest fire that year: ";
	std::cin >> acre1;
	std::cout << "Enter the second year: ";
	std::cin >> year2;
	std::cout << "Enter the acres consumed by forest fire that year: ";
	std::cin >> acre2;

	calculatedvalue = acre1 * CO_EMISSIONS_PER_ACRE;
	calculatedvalue2 = acre2 * CO_EMISSIONS_PER_ACRE;
	percentvalue = (acre2 / acre1) - 1;
	percentvalue = percentvalue * 100;

	std::cout << "In year " << year1 << "," << " forest fires generated " << calculatedvalue << " tons of carbon dioxide." << std::endl;
	std::cout << "In year " << year2 << "," << " forest fires generated " << calculatedvalue2 << " tons of carbon dioxide." << std::endl;
	std::cout << "Between " << year1 << " and " << year2 << "," << " there was a " << percentvalue << "% increase in acres consumed by forest fires." << std::endl;



	return 0;

}
