#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "json2verif.h"
using namespace std;

std::unordered_map<std::string,int> precedence_array () {
    std::unordered_map<std::string, int> precedence;
    precedence["~"] =12;
    precedence["!"] = 12;
    precedence["*"] = 12;
    precedence["/"] = 12;
    precedence["%"] = 12;
    precedence["+"] = 11;
    precedence["-"]  = 11;
    precedence["<<"] = 10;
    precedence[">>"]  = 10;
    precedence["<"]  = 9;
    precedence["<="]  = 9;
    precedence[">"] = 9;
    precedence[">="] = 9;
    precedence["=="] =8;
    precedence["!="] = 8;
    precedence["&"]   = 7;
    precedence["^"]   = 6;
    precedence["|"]    = 5;
    precedence["&&"] = 4;
    precedence["||"] = 3;
    precedence["="]  = 2;
    precedence["+="] = 2;
    precedence["-="] = 2;
    precedence["?:"]    = 1;    //ternary operator (lowest)
    return precedence;    
}



bool is_operator (const std::string& var) {
    std::unordered_map<std::string, int> precedence =precedence_array();
    if (precedence.find(var) != precedence.end()) {
        return true;
    }
    return false;
}

std::string join_with(const std::vector<std::string>& parts, const std::string& separator)
{
    if (parts.empty()) return "";

    std::string result = parts[0];

    for (size_t i = 1; i < parts.size(); i++) {
        result += separator;
        result += parts[i];
    }

    return result;
}

std::string toBinary(string k, int width) {
    std::string bin = "";
    int n=std::stoi(k);
    while (n > 0) {
        bin.push_back((n % 2) + '0');
        n /= 2;
    }
    std::reverse(bin.begin(), bin.end());

    // Pad leading zeros
    if ((int)bin.length() < width) {
        bin.insert(0, width - bin.length(), '0');
    }

    return bin;
}

std::vector<std::string> split_by_space(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> result;
    std::string word;

    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

//std::string validate_operand (string operand) {
//    string return_operand;
//    
//}


std::string दशमाननिर्गमः (std::string statement_temp,json port) {
    

    string print_operand = आद्यारम्भाङ्गोपाधानम्(statement_temp,port);
    std::string from;
    std::string to;
    size_t pos;
    from = ",";
    to = "+";
    pos = 0;
    while ((pos = print_operand.find(from, pos)) != std::string::npos) {
        print_operand.replace(pos, from.length(), to);
        pos += to.length(); // move past replaced text
    }
    from = "std::string(1";
    to = "std::string(1,";
    pos = 0;
    while ((pos = print_operand.find(from, pos)) != std::string::npos) {
        print_operand.replace(pos, from.length(), to);
        pos += to.length(); // move past replaced text
    }
    return "दशमिकपरिवर्तकः(" + print_operand +")";
}
