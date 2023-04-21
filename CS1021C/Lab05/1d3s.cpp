#include <iostream>
#include <fstream>
#include <string>
#include <cassert>


const int ALPHABET_LENGTH{26};

int number_from_letter(char letter) {
  int offset = letter - (int)'a';
  if (offset < 0 || offset >= ALPHABET_LENGTH) {
    std::cout << "number_from_letter called with invalid argument (" << letter << ").\n";
    assert(false);
  }
  return offset;
}

char letter_from_number(int number) {

  if (number < 0 || number >= ALPHABET_LENGTH) {
    std::cout << "letter_from_number called with an invalid argument (" << number << ").\n";
    assert(false);
  }

  const char alphabet[] = { 'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z'};
  return alphabet[number];
}

int main() {
    std::ifstream equation_file{"input.txt"};

    if (!equation_file.is_open()) {
        //std::cout << "Oops: Could not read the direction from the input file.";
        return 0;
    }

    bool test_calculating{ true };
    
    char direction{' '};
    int shift{-1};
   
    if (!(equation_file >> direction)) {
        std::cout << "Oops: Could not read the direction from the input file.\n";
        return 0;
    }

    if (!(equation_file >> shift)) {
        std::cout << "Oops: Could not read the shift number from the input file.\n";
        return 0;
    }
    int change_v;
    int shift_1;
    if (shift > ALPHABET_LENGTH) {
        shift %= ALPHABET_LENGTH;
    }
    if (direction != 'l' && direction != 'r') {
        std::cout << "Oops: Invalid direction in the input file.\n";
        return 0;
    }
    if (direction == 'l' || direction == 'r') {
        if (shift < 0) {
            std::cout << "Oops: Could not read the shift number from the input file.\n";
            return 0;
        }
        if (direction == 'l') {
            while (test_calculating && !std::iscntrl(equation_file.peek()) && !equation_file.eof()) {
                char decrypt{ ' ' };
                equation_file >> decrypt;
                change_v = number_from_letter(decrypt) - shift;
                if (change_v < 0) {
                    change_v += ALPHABET_LENGTH;
                }
                std::cout << letter_from_number(change_v);
            }
            std::cout << "\n";
        }
        else if(direction == 'r') {
        
            while (test_calculating && !std::iscntrl(equation_file.peek()) && !equation_file.eof()) {
                char decrypt{ ' ' };
                equation_file >> decrypt;
                change_v = number_from_letter(decrypt) + shift;
                if (change_v >= 26) {
                    change_v -= ALPHABET_LENGTH;
                }
                std::cout << letter_from_number(change_v);
            }
            std::cout << "\n";
        }
    }
    equation_file.close();
    return 0;
}