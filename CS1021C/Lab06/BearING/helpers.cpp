#include <cassert>
#include <ios>
#include <iostream>

/*
* is_vowel
*
* is_vowel takes a character as an input and returns true if the character is a vowel,
* and returns false if the character is not
*
* input: a single character
* output: bool (true/false)
*/

bool is_vowel(char letter) {

	if ((letter == 'a') || (letter == 'e') || (letter == 'i') || (letter == 'o') || (letter == 'u')) {
		return true;
	}
	else {
		return false;
	}
}

/*
* is_consonant
*
* is_consonant takes a character as an input and returns true if the character is a consonant,
* and returns false if the character is not
*
* input: a single character
* output: bool (true/false)
*/

bool is_consonant(char letter) {

	if (is_vowel(letter) == false) {
		return true;
	}
	else {
		return false;
	}
}

/*
* ends_with
*
* ends_with takes two strings, candidate and suffix and returns true if the last
* characters in candidate are the same as the characters in suffix, otherwise it
* returns false
*
* input: two strings, candidate and suffix
* output: bool (true/false)
*/

bool ends_with(std::string candidate, std::string suffix) {
	if (candidate == "" && suffix == "") {
		return true;
	}
	if (candidate == "" && !(suffix == "")) {
		return false;
	}

	if (candidate.length() < suffix.length()) {
		return false;
	}

	int i = 0;

	for (i = 0; i < suffix.length(); ++i) {

		if (suffix.at(suffix.length() - 1 - i) != candidate.at(candidate.length() - 1 - i)) {

			return false;

		}

	}

	return true;

}

/*
* ends_with_double_consonant
*
* ends_with_double_consonant takes a single string as its input, then it checks if the last two
* characters in the string are both the same letter, and are both consonants. If both of these
* conditions are met, it returns true, otherwise it returns false
*
* input: string
* output: bool (ture/false)
*/

bool ends_with_double_consonant(std::string stringA) {
	
	if (stringA.length() < 2) {

		return false;

	}

	else if ((stringA.at(stringA.length() - 1) == stringA.at(stringA.length() - 2)) && is_consonant(stringA.at(stringA.length() - 1)) == true) {

		return true;

	}

	else {

		return false;

	}

}

/*
* ends_with_cvc
*
* ends_with_cvc takes a single string as its input, and checks if it ends with a consonant, vowel, and consonant
* in that order and returns true if that is the case
*
* input: astring
* output: bool (true/false)
*/

bool ends_with_cvc(std::string stringA) {

	if (stringA.length() < 3) {

		return false;

	}

	else if ((is_consonant(stringA.at(stringA.length() - 1)) == true) && (is_vowel(stringA.at(stringA.length() - 2)) == true) && (is_consonant(stringA.at(stringA.length() - 3)) == true)) {

		return true;

	}

	else {

		return false;

	}

}

int i = 0;

/*
* count_consonants_at_front
*
* count_consonants_at_front takes a single string as its input and returns the number of
* consecutive consonants present starting from the beginning of the string until a vowel is
* detected.
*
* input: string
* output: integer number type
*/

int count_consonants_at_front(std::string stringA) {

	if (stringA == "") {

		return 0;

	}

	else {

		int consonants_at_front = 0;

		for (i = 0; i < stringA.length(); ++i) {

			if (is_consonant(stringA.at(i)) == true) {

				consonants_at_front = consonants_at_front + 1;

			}

			else {

				break;

			}

		}

		return consonants_at_front;

	}

}

int j = 0;

/*
* count_vowels_at_back
*
* count_vowels_at_back takes a single string and returns the number of
* consecutive vowels present starting from the end of the string until a consonant
* is detected
*
* input: string
* output: integer number type
*/

int count_vowels_at_back(std::string stringA) {

	if (stringA == "") {

		return 0;

	}

	else {

		int vowels_at_back = 0;

		for (j = stringA.length() - 1; j >= 0; --j) {

			if (is_vowel(stringA.at(j)) == true) {

				vowels_at_back = vowels_at_back + 1;

			}

			else {

				break;

			}

		}

		return vowels_at_back;

	}

}

int k = 0;

/*
* contains_vowel
*
* contains_vowel takes a single string and examines every character in the
* string to see if there is at least one vowel in the string
*
* input: string
* output: bool (true/false)

*/

bool contains_vowel(std::string stringA) {

	if (stringA == "") {

		return false;

	}

	else {

		for (k = 0; k < stringA.length(); ++k) {

			if ((is_vowel(stringA.at(k))) == true) {

				return true;

			}

			else {

			}

		}

		return false;

	}

}

/*
* new_ending
*
* new_ending takes two strings, candidate and suffix, as well as an integer
* and creates a new string of characters from the end of candidate 
* and replacing the removed characters with the string
* suffix and presents the new string
*
* input: a string candidate, a string suffix, and an integer length
* output: a string
*/

std::string new_ending(std::string candidate, int length, std::string replacement) {

	return candidate.replace(candidate.length() - length, candidate.length(), replacement);

}