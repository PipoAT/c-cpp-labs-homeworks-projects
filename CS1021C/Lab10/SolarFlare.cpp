#include "httplib.h"
#include "json.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>

#include "Date.h"
#include "Location.h"
#include "LocationDateLength.h"

#define assert_with_message(condition, message)                                \
  if (!(condition)) {                                                          \
    assert((message, (condition)));                                            \
  }

/*
 * parse_json_daylength_response
 *
 * This function parses the JSON response from the Sunrise Sunset
 * Web API and replaces the length in the member of the first
 * parameter with the value embedded in the JSON.
 *
 * input: _raw_json_: The resulting data, as a std::string,
 *         of the Sunrise Sunset WebAPI call.
 * output: _day_length_response: A std::unique_ptr to a
 *         LocationDateLength struct whose length member is updated
 *         to match the daylength embedded in the 1st parameter.
 * return: A bool: true if the content downloaded from the Sunrise
 *         Sunset API was properly formatted; false otherwise.
 */
bool parse_json_daylength_response(std::string raw_json,
    LocationDateLength& day_length_response) {
    using nlohmann::json;
    try {
        auto parsed_json = json::parse(raw_json);
        auto iso_time{ parsed_json["results"]["day_length"].get<int>() };

        day_length_response.setLength(iso_time);
        return true;
    }
    catch (json::parse_error& e) {
        /*
         * There was a parsing error.
         */
        return false;
    }
}

/*
 * download
 *
 * This function will use HTTP to connect to the server, issue the
 * Web API call and download the server's response. In the case of
 * an error, the function will return false. Otherwise, the function
 * will return true.
 *
 * input: _host_: The name of the server from which to download.
 *        _path_: The path of the Web API.
 * output: _content_: The content of the Web API call's response.
 * return: A bool: true if the Web API was properly invoked; false, otherwise.
 */
bool download(std::string host, std::string path, std::string& content) {
    auto client = httplib::Client(host);

    auto result = client.Get(path.c_str());

    if (result && result->status == 200) {
        content = result->body;
        return true;
    }
    else {
        return false;
    }
}

/*
 * build_url_path
 *
 * The function will use the values in the LocationDateLength
 * C++ struct given as a parameter to create a properly-formatted WebAPI
 * query for the Sunrise Sunset API. The struct must contain valid values
 * for the date and the location. The resulting std::string can be used
 * as an argument to the download function.
 *
 * input: _daylength_: The date and location for which to request the
 *        daylength from the Sunrise Sunset Web API.
 * return: A std::string that contains the properly-formatted path of the
 *         Sunrise Sunset WebAPI request for the given date and location.
 */
std::string build_url_path(LocationDateLength& daylength) {
    assert_with_message(
        daylength.getDate().getDay() > 0 && daylength.getDate().getDay() < 32 &&
        daylength.getDate().getYear() > 999 &&
        daylength.getDate().getYear() < 3000 &&
        daylength.getDate().getMonth() > 0 &&
        daylength.getDate().getMonth() < 12,
        std::string{ "Date parameters in the argument appear to be invalid." });
    assert_with_message(
        std::abs(daylength.getLocation().getLatitude()) < 180.0 &&
        std::abs(daylength.getLocation().getLongitude()) < 180.0,
        std::string{ "Location parameters in argument appear to be invalid." });

    std::stringstream url_path_stream{ "" };
    url_path_stream << "/json?formatted=0&lat="
        << daylength.getLocation().getLatitude()
        << "&lng=" << daylength.getLocation().getLongitude()
        << "&date=" << daylength.getDate().getYear() << "-"
        << daylength.getDate().getMonth() << "-"
        << daylength.getDate().getDay();
    return url_path_stream.str();
}

/*
* readInt
* Reads an integer from the provided reference file, and will check
* if it can successfully read that integer. It will return true if
* successful and false if unsuccessful
*
* Input: std::ifstream myFile, int myInt
*
* Output: bool (true/false)
*/
bool readInt(std::ifstream& myFile, int& myInt) {
    if (!(myFile >> myInt)) {
        std::cout << "Oops: Could not read two valid dates from file.\n";
        return false;
    }
    return true;

}

/*
* readDate()
*
* Takes the year, month, and day and converts it to the recieved
* year, month, day. It will also check if it is successful.
*
* Inputs: std::ifstream myFile, Date myDate
*
* Outputs: boolean (True/false)
*/
bool readDate(std::ifstream& myFile, Date& myDate) {
    int day, month, year;
    char DASH; 
    if (!readInt(myFile, year)) { return false; }
    myFile >> DASH;
    if (!readInt(myFile, month)) { return false; }
    myFile >> DASH;
    if (!readInt(myFile, day)) { return false; }
    myDate.setYear(year);
    myDate.setMonth(month);
    myDate.setDay(day);
    return true;
}

const double CINCI_LATITUDE = 39.103119;
const double CINCI_LONGITUDE = -84.512016;
const std::string FILENAME = "query_file.txt";
const std::string HOST_NAME = "api.sunrise-sunset.org";

int main() {
    std::ifstream file;
    file.open(FILENAME);
    if (!file.is_open()) {
        std::cout << "Oops: Could not open the file!\n";
        return 0;
    }

    Date date1;
    Date date2;
    Location myLocation;
    myLocation.setLatitude(CINCI_LATITUDE);
    myLocation.setLongitude(CINCI_LONGITUDE);

    if (!readDate(file, date1)) { return 0; }
    if (!readDate(file, date2)) { return 0; }

    LocationDateLength myDateLength1(date1, myLocation);
    LocationDateLength myDateLength2(date2, myLocation);
    std::string myPath1 = build_url_path(myDateLength1);
    std::string myPath2 = build_url_path(myDateLength2);
    std::string myContent1;
    std::string myContent2;
    bool isDownloads1 = download(HOST_NAME, myPath1, myContent1);
    bool isDownloads2 = download(HOST_NAME, myPath2, myContent2);
    if (!isDownloads1) {
        std::cout << "Oops: There was a Web API error.\n";
        return 0;
    }
    if (!isDownloads2) {
        std::cout << "Oops: There was a Web API error.\n";
        return 0;
    }

    parse_json_daylength_response(myContent1, myDateLength1);
    parse_json_daylength_response(myContent2, myDateLength2);
    int length = myDateLength2 - myDateLength1;
    bool isLengthNegative = length < 0;
    length = abs(length);
    int hours = length / 3600;
    length %= 3600;
    int minutes = length / 60;
    length %= 60;
    int seconds = length;


    if (isLengthNegative) {
        std::cout << date2 << " was " << hours << " hour(s), " << minutes << " minute(s) and " << seconds << " second(s) shorter than " << date1 << ".\n";
    }
    else {
        std::cout << date2 << " was " << hours << " hour(s), " << minutes << " minute(s) and " << seconds << " second(s) longer than " << date1 << ".\n";
    }

    return 0;
}
