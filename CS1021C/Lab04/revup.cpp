#include <string.h>

#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>

std::string intended_use{""};
double requested_loan_amt{0.0};
bool non_profit_business{false};

void get_input(int argc, char **argv) {
  if (argc == 1) {
    intended_use = "debt";
    requested_loan_amt = 200.0;
    non_profit_business = true;
  } else if (argc == 4) {
    // The first CLI parameter is the intended use for the loan.
    intended_use = argv[1];

    // NB: No error checking is done here. User must be careful to only
    // pass valid numbers!
    requested_loan_amt = static_cast<double>(atoi(argv[2]));

    // The final CLI parameter is whether the applicant's business is
    // a non-profit. If the parameter is "true", then the business is
    // a non-profit.
    if (!strcmp("true", argv[3])) {
      non_profit_business = true;
    }
  } else {
    exit(EXIT_FAILURE);
  }
}

void print_horizontal_line(int columns) {
  auto flags = std::cout.flags();
  auto fill = std::cout.fill();
  std::cout << std::setfill('=') << std::setw(columns) << ""
            << "\n";
  std::cout.flags(flags);
  std::cout.fill(fill);
}

std::string format_money(double money) {
  std::stringstream formatted_money{};
  formatted_money << std::fixed << std::setprecision(2) << std::showpoint;
  formatted_money << "$" << money;
  return formatted_money.str();
}

std::string format_percentage(double percentage) {
  std::stringstream formatted_percentage{};
  formatted_percentage << std::fixed << std::setprecision(2) << std::showpoint;
  formatted_percentage << percentage << "%";
  return formatted_percentage.str();
}

std::string bool_to_yes_no(bool value) {
  std::string yes_no{""};
  if (value) {
    yes_no = std::string{"Yes"};
  } else {
    yes_no = std::string{"No"};
  }
  return yes_no;
}

void print_labeled_value(const std::string &label, int label_width,
                         const std::string &value, int value_width) {
  auto flags = std::cout.flags();
  auto fill = std::cout.fill();
  std::cout << std::setfill(' ') << std::left << std::setw(label_width) << label
            << std::right << std::setw(value_width) << value << "\n";
  std::cout.flags(flags);
  std::cout.fill(fill);
}

int main(int argc, char **argv) {
  get_input(argc, argv);

 

  double interestrate;
  double fee;
  std::string collateral;
  std::string personal;


  // Complete the implementation of main according to the specifications in the
  // lab document! Do not remove any code that exists. Simply add additional
  // code to meet the description of RevUp's operation.

  /*This program can determine is the user is eligible for a loan from the US
  government for a small business during the pandemic */

  if (intended_use != "payroll" && intended_use != "rent" &&
      intended_use != "mortgage" && intended_use != "utilities" &&
      intended_use != "debt" && intended_use != "ordinary business expenses") {

      print_horizontal_line(80);
      print_labeled_value("Eligibility Status:", 0, "No", 61);
      print_horizontal_line(80);
  }

  else {
      if (requested_loan_amt > 2000000.0) {
      print_horizontal_line(80);
      print_labeled_value("Eligibility Status:", 0, "No", 61);
      print_horizontal_line(80);

      }
      else {
        if (non_profit_business == true) {
          interestrate = 2.75;
          if (requested_loan_amt <= 25000.0) {
            fee = 0;
            collateral = "No";

            if (requested_loan_amt > 200000.0) {
              personal = "Yes";
              print_horizontal_line(80);
              print_labeled_value("Eligibility Status:", 0, "Yes", 61);
              print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
              print_labeled_value("Application Fee:", 0, format_money(fee), 64);
              print_labeled_value("Collateral Required:", 0, collateral, 60);
              print_labeled_value("Personal Guaranty:", 0, personal, 62);
              print_horizontal_line(80);
            }

            else {
              personal = "No";
              print_horizontal_line(80);
              print_labeled_value("Eligibility Status:", 0, "Yes", 61);
              print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
              print_labeled_value("Application Fee:", 0, format_money(fee), 64);
              print_labeled_value("Collateral Required:", 0, collateral, 60);
              print_labeled_value("Personal Guaranty:", 0, personal, 62);
              print_horizontal_line(80);
            }
          }

          else {
            fee = 100;
            collateral = "Yes";

            if (requested_loan_amt > 200000.0) {
              personal = "Yes";
              print_horizontal_line(80);
              print_labeled_value("Eligibility Status:", 0, "Yes", 61);
              print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
              print_labeled_value("Application Fee:", 0, format_money(fee), 64);
              print_labeled_value("Collateral Required:", 0, collateral, 60);
              print_labeled_value("Personal Guaranty:", 0, personal, 62);
              print_horizontal_line(80);

            } else {
              personal = "No";
              print_horizontal_line(80);
              print_labeled_value("Eligibility Status:", 0, "Yes", 61);
              print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
              print_labeled_value("Application Fee:", 0, format_money(fee), 64);
              print_labeled_value("Collateral Required:", 0, collateral, 60);
              print_labeled_value("Personal Guaranty:", 0, personal, 62);
              print_horizontal_line(80);
            }
          }
        }

        
        
        
        else {
            interestrate = 3.75;
            if (requested_loan_amt <= 25000.0) {
                fee = 0;
                collateral = "No";

                if (requested_loan_amt > 200000.0) {
                    personal = "Yes";
                print_horizontal_line(80);
                print_labeled_value("Eligibility Status:", 0, "Yes", 61);
                print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
                print_labeled_value("Application Fee:", 0, format_money(fee), 64);
                print_labeled_value("Collateral Required:", 0, collateral, 60);
                print_labeled_value("Personal Guaranty:", 0, personal, 62);
                print_horizontal_line(80);

              

            }   else {
                personal = "No";
                print_horizontal_line(80);
                print_labeled_value("Eligibility Status:", 0, "Yes", 61);
                print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
                print_labeled_value("Application Fee:", 0, format_money(fee), 64);
                print_labeled_value("Collateral Required:", 0, collateral, 60);
                print_labeled_value("Personal Guaranty:", 0, personal, 62);
                print_horizontal_line(80);
            }

          } else {
                fee = 100;
                collateral = "Yes";

                if (requested_loan_amt > 200000.0) {
                    personal = "Yes";
                    print_horizontal_line(80);
                    print_labeled_value("Eligibility Status:", 0, "Yes", 61);
                    print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
                    print_labeled_value("Application Fee:", 0, format_money(fee), 64);
                    print_labeled_value("Collateral Required:", 0, collateral, 60);
                    print_labeled_value("Personal Guaranty:", 0, personal, 62);
                    print_horizontal_line(80);

              
            }   else {
                    personal = "No";
                    print_horizontal_line(80);
                    print_labeled_value("Eligibility Status:", 0, "Yes", 61);
                    print_labeled_value("Interest Rate:", 0, format_percentage(interestrate), 66);
                    print_labeled_value("Application Fee:", 0, format_money(fee), 64);
                    print_labeled_value("Collateral Required:", 0, collateral, 60);
                    print_labeled_value("Personal Guaranty:", 0, personal, 62);
                    print_horizontal_line(80);
            }
          }

        
        
        }



      }
  }

  return 0;
}
