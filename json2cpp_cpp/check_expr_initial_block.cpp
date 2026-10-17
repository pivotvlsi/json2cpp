#include <iostream>
#include <stdexcept>
#include <string> 
//#include "definitions.h"
#include <stack>
#include <regex>
#include <ranges>
#include "json.hpp"
#include "json2verif.h"
using json = nlohmann::json;
using namespace std;




std::string आद्याङ्गपरिक्षाप्रकटम् (std::vector<std::string> statement_temp) {
    std::stack<std::string> calc_stack;

    std::string statement = "";
    std::string first_operand;
    std::string second_operand;
    std::string operand1;
    std::string operand2;
    for (int temp=0; temp<statement_temp.size(); temp++) {
        if (is_operator(statement_temp[temp])) {
            if (!calc_stack.empty()) {
                    operand1 = calc_stack.top();
                    calc_stack.pop();
                } else {
                    cerr <<"Error from aadyaangavaakyam while getting oerand1; Ill formed expression";
                }
                if (!calc_stack.empty()) {
                    operand2 = calc_stack.top();
                    calc_stack.pop();
                } else {
                    cerr <<"Error from aadyaangavaakyam while getting oerand1; Ill formed expression";
                }
            first_operand=operand1;
            second_operand=operand2;
            if (statement_temp[temp] == "==") {
                statement = "आद्यारम्भाङ्गम्_तार्किकसमतापरीक्षणम्("+first_operand+","+second_operand+")";
            } else if (statement_temp[temp] == "<") {
                statement = "आद्यारम्भाङ्गम्_तार्किककनिष्ठात्परीक्षणम्("+first_operand+","+second_operand+")";
            } else if (statement_temp[temp] == ">") {
                statement = "आद्यारम्भाङ्गम्_तार्किकज्यायान्परीक्षणम्("+first_operand+","+second_operand+")";
            } else if (statement_temp[temp] == "<=") {
                statement = "आद्यारम्भाङ्गम्_तार्किककनिष्ठसमपरीक्षणम्("+first_operand+","+second_operand+")";
            } else if (statement_temp[temp] == ">=") {
                statement = "आद्यारम्भाङ्गम्_तार्किकज्यायान्समपरीक्षणम्("+first_operand+","+second_operand+")";
            } else if (statement_temp[temp] == "=") {
                statement = first_operand+"="+second_operand;
            } else {

                cerr <<"didnot handled the operator "<<statement_temp[temp];
            }
        } else {
            calc_stack.push(statement_temp[temp]);
        }    
    }
    return statement;
}


std::string आद्याङ्गवाक्यम् (std::vector<std::string> statement_temp, json port, std::string module_name) {
    string first_operand = "";
    string second_operand = "";
    string operand1 = "";
    string operand2 = "";

    
    std::stack<std::string> गणनापुटः;
    for (int temp =0; temp < statement_temp.size(); temp = temp+1) {
        if (is_operator(statement_temp[temp])) {
            if (statement_temp[temp] == "+") {
                if (!गणनापुटः.empty()) {
                    operand1 = गणनापुटः.top();
                    गणनापुटः.pop();
                } else {
                    cerr <<"Error from aadyaangavaakyam while getting oerand1; Ill formed expression";
                }
                if (!गणनापुटः.empty()) {
                    operand2 = गणनापुटः.top();
                    गणनापुटः.pop();
                } else {
                    cerr <<"Error from aadyaangavaakyam while getting oerand1; Ill formed expression";
                }
                


                first_operand      = आद्यारम्भाङ्गोपाधानम्(operand1,port);
                second_operand = आद्यारम्भाङ्गोपाधानम्(operand2, port);
                std::string from;
                std::string to;
                size_t pos;
                from = ",";
                to = "+";
                pos = 0;
                while ((pos = first_operand.find(from, pos)) != std::string::npos) {
                    first_operand.replace(pos, from.length(), to);
                    pos += to.length(); // move past replaced text
                }
                from = "std::string(1";
                to = "std::string(1,";
                pos = 0;
                while ((pos = first_operand.find(from, pos)) != std::string::npos) {
                    first_operand.replace(pos, from.length(), to);
                    pos += to.length(); // move past replaced text
                }
                from = ",";
                to = "+";
                pos = 0;
                while ((pos = second_operand.find(from, pos)) != std::string::npos) {
                    second_operand.replace(pos, from.length(), to);
                    pos += to.length(); // move past replaced text
                }
                from = "std::string(1";
                to = "std::string(1,";
                pos = 0;
                while ((pos = second_operand.find(from, pos)) != std::string::npos) {
                    second_operand.replace(pos, from.length(), to);
                    pos += to.length(); // move past replaced text
                }

                गणनापुटः.push("आद्यारम्भाङ्गम्_द्विबिन्दुयोजनम् ("+first_operand+","+ second_operand +")");
                              

            } else if (statement_temp[temp] == "=") {
                if (!गणनापुटः.empty()) {
                    operand1 = गणनापुटः.top();
                    गणनापुटः.pop();
                } else {
                    cerr <<"Error from aadyaangavaakyam while getting oerand1; Ill formed expression";
                }
                if (!गणनापुटः.empty()) {
                    operand2 = गणनापुटः.top();
                    गणनापुटः.pop();
                } else {
                    cerr <<"Error from aadyaangavaakyam while getting oerand1; Ill formed expression";
                }
                

                
                first_operand = आद्यारम्भाङ्गोपाधानम्(operand1,port);
                
                
                second_operand = आद्यारम्भाङ्गोपाधानम्_नियोजनम् (operand2,port,module_name);
               
                गणनापुटः.push("आद्यारम्भाङ्गम्_द्विनियोजनम् (" +second_operand +"," + first_operand + ")");

            } else {
                cerr << "Unhandled in check_expr_initial_block aadyangavaakyam\n" ;
            }
        
        } else {
            
            गणनापुटः.push(statement_temp[temp]);
        }
    }
    if (गणनापुटः.size() ==1) {
        return गणनापुटः.top()+";";
    } else {
        cout << "Mal formed statement in aadyaangavaakyam\n";
        exit(1);
    }
}



bool onlySpaces(const std::string& s) {
    for (char c : s) {
        if (c != ' ')
            return false;
    }
    return true;
}


std::string आद्यारम्भाङ्गोपाधानम् (std::string उपाधानम्, json j) {

    std::string अस्थायि;
    std::string कूटाङ्कः;
    std::string pattern;
    std::vector <std::string> सरणिः = {};
    std::vector <std::string> सरणिः_अस्थायि = {};

    std::regex re1("^\\s*[A-Za-z]");

    std::regex re2("^\\s*([A-Za-z][A-Za-z0-9_]*)");

    std::regex re3("^\\s*\\[");
    //];
    std::regex re4(R"(^\\s*\\[(\\d+):(\\d+)\\])");

    std::regex re5(R"(^\\s*\\[(\\d+)\\])");
    std::regex re6("^\\s*'([ohdb])\\s*([0-9_A-Fa-f]+)");
    //re7 is between the function
    std::regex re8("^\\d+$");
    std::regex re9("^\\s*(\\d+)\\s*'([ohdb])\\s*([0-9_A-Fa-f]+)");
    std::regex re10("^(\\d+)");
    

    std::smatch match;
    std::vector <int> कनिष्ठम्;
    std::vector <int> ज्येष्ठम्;
    int अवगाढता;
    int अवगाढता_अस्थायि;
    int high1;
    int low1;
    int loop=0;
    while (onlySpaces(उपाधानम्) ==false) {
        if (loop == 1) exit(1);
        loop++;
        if  (उपाधानम्.find("आद्यारम्भाङ्गम्") != std::string::npos ) {
            return उपाधानम्;
        } else if (std::regex_search(उपाधानम्, re1)) {
            if (std::regex_search(उपाधानम्, match, re2)) {
                अस्थायि = match[1];
                
                कनिष्ठम् = {};
                ज्येष्ठम् = {};
                if (j.contains(अस्थायि)) {
                    उपाधानम् = std::regex_replace(उपाधानम्, std::regex(अस्थायि), "");
    
                    if (!j[अस्थायि].contains("अवगाढता")) {
                       std::cerr << " from aadyaarambaangopaadhaanam in check_expr_initial_block\n" ;
                    }
                    
                    अवगाढता = j[अस्थायि]["अवगाढता"];
                    अवगाढता_अस्थायि =0;
                    int high1;
                    int low1;
                    while (std::regex_search(उपाधानम्, re3)) {
                        if (std::regex_search(उपाधानम्, match, re4)) {
                            high1 = std::stoi(match[1]);
                            low1 = std::stoi(match[2]);
                            ज्येष्ठम्.push_back(high1);
                            कनिष्ठम्.push_back(low1);
                            pattern = "\\[" + std::to_string(high1) + ":" + std::to_string(low1) + "\\]";
                            उपाधानम् = std::regex_replace(उपाधानम्, std::regex(pattern), "");
                        } else if  ( std::regex_search(उपाधानम्, match, re5)) {
    
                            ज्येष्ठम्.push_back(high1);
                            कनिष्ठम्.push_back(high1);
                            pattern = "\\[" + std::to_string(high1) + "\\]";
                            उपाधानम् = std::regex_replace(उपाधानम्, std::regex(pattern), "");
                        } else {
                            cerr << "Error in CheckExprInitialBlock with array\n";
                        }
                    }
                    int i;

                    while (अवगाढता_अस्थायि < अवगाढता) {
                        अवगाढता_अस्थायि++;
                        if (अवगाढता_अस्थायि == 1) {
                            if (ज्येष्ठम्.size() > अवगाढता_अस्थायि) {
                                i = ज्येष्ठम्[अवगाढता_अस्थायि-1];
                                while (i <= कनिष्ठम्[अवगाढता_अस्थायि-1]) {
                                    सरणिः.push_back(अस्थायि+"["+std::to_string(i)+"]");
                                    i++;
                                }
                            } else {
                                if ( !j[अस्थायि].contains(std::to_string(अवगाढता_अस्थायि)+"_आद्यसूचकः")) {
                                    cerr << "Error from aadyaarambhaangopaadhaanam for array aadyasoochaka\n";
                                }
                                if ( !j[अस्थायि].contains(std::to_string(अवगाढता_अस्थायि)+"_अन्त्यसूचकः")) {
                                    cerr << "Error from aadyaarambhaangopaadhaanam for array antyasoochaka\n";
                                }
                                i = std::stoi(j[अस्थायि][std::to_string(अवगाढता_अस्थायि)+"_आद्यसूचकः"].get<string>());
                                while (i <= std::stoi(j[अस्थायि][std::to_string(अवगाढता_अस्थायि)+"_अन्त्यसूचकः"].get<string>())) {
                                    सरणिः.push_back(अस्थायि+"["+std::to_string(i)+"]");
                                    i++;
                                }
                            }

                            
                        } else {
                            if (ज्येष्ठम्.size() > अवगाढता_अस्थायि) {

                                for (i = ज्येष्ठम्[अवगाढता_अस्थायि-1]; i <=कनिष्ठम्[अवगाढता_अस्थायि-1]; i++) {
                                    for (int k=0; k < सरणिः_अस्थायि.size(); k++) {
                                        सरणिः.push_back(सरणिः_अस्थायि[k]+"["+std::to_string(i)+"]");
                                    }
                                }

                            } else {
                                for ( i = j[अस्थायि][अवगाढता_अस्थायि+"_आद्यसूचकः"];
                                    i <= j[अस्थायि][अवगाढता_अस्थायि+"_अन्त्यसूचकः"]; i++) {
                                    for (int k=0; k < सरणिः_अस्थायि.size(); k++) {
                                        सरणिः.push_back(सरणिः_अस्थायि[k]+"["+std::to_string(i)+"]");
                                    }
    
                                }
                            }
                        }

                        for (int k=0; k < सरणिः.size(); k++) {
                            सरणिः_अस्थायि.push_back("std::string(1" +सरणिः[k] +".getVal())");
                        }

                        सरणिः = {};
                    }


                
                }else {
                    cerr << "Error from identifying the variable "<<अस्थायि ;
                }
            }

            सरणिः = सरणिः_अस्थायि;
            कूटाङ्कः = join_with(सरणिः, ",");
            

        } else if (std::regex_search(उपाधानम्, match, re6) ) {
            string j1= match[1];
            string k = match[2];
            cout << " Into else if" << j1 << " " << k << "\n";
            pattern = "\\s*'" + j1 + "\\s*" + k;
            std::regex re7(pattern);
            उपाधानम् = std::regex_replace(उपाधानम्, re7, "");
            
            if (j1 == "b") {
                cerr << "Fill binary afterwards from aadyaarambhaangopaadhaanam";
                //$कूटाङ्कः{"स्थिरम्"} = 1;
                //if ($k =~ /^[01_]+$/) {

                //    $कूटाङ्कः{"मूल्यम्"} = $k;
                //    $कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";

                //} else {
                //    cerr "Unknown characters in binary in $उपाधानम्";
                //}
            } else if (j1 == "d") {

                if (std::regex_match(k, re8)) {
                    कूटाङ्कः = '"'+toBinary(k, 32)+ '"';


                } else {
                    cerr << "Unknown characters in decimal in " <<उपाधानम्;
                }

            } else if (j1 == "o") {
                cerr << "Fill octal afterwards from aadyaarambhaangopaadhaanam";

                //if ($k =~ /^[0-7_]+$/) {
                //    $कूटाङ्कः{"स्थिरम्"} = 1;
                //    $कूटाङ्कः{"मूल्यम्"} = sprintf("%032b", oct($k));
                //    $कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
                //} else {
                //    die "Unknown characters in octal in $उपाधानम्";
                //}

            } else if (j1 == "h") {
                cerr << "Fill hexa afterwards from aadyaarambhaangopaadhaanam";

                //if ($k =~ /^[\dA-Fa-f_]+$/) {
                //    $कूटाङ्कः{"स्थिरम्"} = 1;
                //    $कूटाङ्कः{"मूल्यम्"} = sprintf "%032b", hex $k;
                //    $कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
                //} else {
                //    die "Unknown characters in decimal in $उपाधानम्";
                //}
                //$कूटाङ्कः{"स्थिरम्"} = 1;
                //$कूटाङ्कः{"मूल्यम्"} = sprintf "%032b", hex $k;
                //$कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
            }
            
        } else if (std::regex_search(उपाधानम्, match, re9)) {
            string i1 =match[1];
            string j1= match[2];
            string k = match[3];
            pattern = i1 + "\\s*" + "'" + "\\s*" + j1 + "\\s*" + k;
            उपाधानम् = std::regex_replace(उपाधानम्, std::regex(pattern), "");
            if (j1 == "b") {
                //$कूटाङ्कः{"स्थिरम्"} = 1;
                //if ($k =~ /^[01_]+$/) {
                //    if (length($k) == $i) {
                //        $कूटाङ्कः{"मूल्यम्"} = $k;
                //        $कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
                //    } else {
                //        die "No of bits in binary is wrong in $उपाधानम्";
                //    }
                //} else {
                //    die "Unknown characters in binary in $उपाधानम्";
                //}
            } else if (j1 == "d") {
                if (std::regex_match(k, re8)) {
                    कूटाङ्कः = '"' +toBinary(k, std::stoi(i1))+'"';


                } else {
                    cerr << "Unknown characters in decimal in " << उपाधानम्;
                }


            } else if (j1 == "o") {
                cerr << "Fill octal afterwards from aadyaarambhaangopaadhaanam";

                //if ($k =~ /^[0-7_]+$/) {
                //    $कूटाङ्कः{"स्थिरम्"} = 1;
                //    $कूटाङ्कः{"मूल्यम्"} = sprintf("%0${i}b", oct($k));
                //    $कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
                //} else {
                //    die "Unknown characters in octal in $उपाधानम्";
                //}



            } else if (j1 == "h") {
                cerr << "Fill octal afterwards from aadyaarambhaangopaadhaanam";

                //if ($k =~ /^[\dA-Fa-f_]+$/) {
                //    $कूटाङ्कः{"स्थिरम्"} = 1;
                //    $कूटाङ्कः{"मूल्यम्"} = sprintf "%0${i}b", hex $k;
                //    $कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
                //} else {
                //    die "Unknown characters in decimal in $उपाधानम्";
                //}
                //$कूटाङ्कः{"स्थिरम्"} = 1;
                //$कूटाङ्कः{"मूल्यम्"} = sprintf "%0${i}b", hex $k;
                //$कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
            }
            //$कूटाङ्कः{"परिमाणम्"} = $i;
             
        } else if(std::regex_search(उपाधानम्, match, re10)) {
            std::string k = match[1];
            cerr << "Fill full decimal afterwards from aadyaarambhaangopaadhaanam";

            //my $k = $1;
            //$उपाधानम्  =~ s/$k//;
            //$कूटाङ्कः{"मूल्यम्"} = sprintf("%032b", $k);
            //$कूटाङ्कः{"वर्णः_वा"} = "असत्यम्";
            //$कूटाङ्कः{"स्थिरम्"} = 1;
            //$कूटाङ्कः{"परिमाणम्"} = 32;
        } else {
            cerr <<  "Unknown bareword "<< उपाधानम् <<"\n" ;
        }

    }
    return कूटाङ्कः;
    

}

std::string आद्यारम्भाङ्गोपाधानम्_नियोजनम् (std::string उपाधानम्, json j, std::string module_name) {

    std::string अस्थायि;
    std::string कूटाङ्कः;
    std::string pattern;
    std::vector <std::string> सरणिः = {};
    std::vector <std::string> सरणिः_अस्थायि = {};

    std::regex re1("^\\s*[A-Za-z]");

    std::regex re2("^\\s*([A-Za-z][A-Za-z0-9_]*)");

    std::regex re3("^\\s*\\[");
    //];
    std::regex re4(R"(^\\s*\\[(\\d+):(\\d+)\\])");

    std::regex re5(R"(^\\s*\\[(\\d+)\\])");
    std::regex re6("^\\s*'([ohdb])\\s*([0-9_A-Fa-f]+)");
    //re7 is between the function
    std::regex re8("^\\d+$");
    std::regex re9("^\\s*(\\d+)\\s*'([ohdb])\\s*([0-9_A-Fa-f]+)");
    std::regex re10("^(\\d+)");
    

    std::smatch match;
    std::vector <int> कनिष्ठम्;
    std::vector <int> ज्येष्ठम्;
    int अवगाढता;
    int अवगाढता_अस्थायि;
    int high1;
    int low1;
    int loop=0;
    while (onlySpaces(उपाधानम्) ==false) {
        if (loop == 1) exit(1);
        loop++;
        if  (उपाधानम्.find("आद्यारम्भाङ्गम्") != std::string::npos ) {
            return उपाधानम्;
        } else if (std::regex_search(उपाधानम्, re1)) {
            if (std::regex_search(उपाधानम्, match, re2)) {
                अस्थायि = match[1];
                
                कनिष्ठम् = {};
                ज्येष्ठम् = {};
                if (j.contains(अस्थायि)) {
                    उपाधानम् = std::regex_replace(उपाधानम्, std::regex(अस्थायि), "");
    
                    if (!j[अस्थायि].contains("अवगाढता")) {
                       std::cerr << " from aadyaarambaangopaadhaanam in check_expr_initial_block\n" ;
                    }
                    
                    अवगाढता = j[अस्थायि]["अवगाढता"];
                    अवगाढता_अस्थायि =0;
                    int high1;
                    int low1;
                    while (std::regex_search(उपाधानम्, re3)) {
                        if (std::regex_search(उपाधानम्, match, re4)) {
                            high1 = std::stoi(match[1]);
                            low1 = std::stoi(match[2]);
                            ज्येष्ठम्.push_back(high1);
                            कनिष्ठम्.push_back(low1);
                            pattern = "\\[" + std::to_string(high1) + ":" + std::to_string(low1) + "\\]";
                            उपाधानम् = std::regex_replace(उपाधानम्, std::regex(pattern), "");
                        } else if  ( std::regex_search(उपाधानम्, match, re5)) {
    
                            ज्येष्ठम्.push_back(high1);
                            कनिष्ठम्.push_back(high1);
                            pattern = "\\[" + std::to_string(high1) + "\\]";
                            उपाधानम् = std::regex_replace(उपाधानम्, std::regex(pattern), "");
                        } else {
                            cerr << "Error in CheckExprInitialBlock with array\n";
                        }
                    }

                    int i;

                    while (अवगाढता_अस्थायि < अवगाढता) {
                        अवगाढता_अस्थायि++;

                        if (अवगाढता_अस्थायि == 1) {
                            if (ज्येष्ठम्.size() > अवगाढता_अस्थायि) {
                                i = ज्येष्ठम्[अवगाढता_अस्थायि-1];
                                
                                while (i <= कनिष्ठम्[अवगाढता_अस्थायि-1]) {
                                    सरणिः.push_back(अस्थायि+"["+std::to_string(i)+"]");
                                    i++;
                                }

                            } else {
                                if ( !j[अस्थायि].contains(std::to_string(अवगाढता_अस्थायि)+"_आद्यसूचकः")) {
                                    cerr << "Error from aadyaarambhaangopaadhaanam for array aadyasoochaka\n";
                                }
                                if ( !j[अस्थायि].contains(std::to_string(अवगाढता_अस्थायि)+"_अन्त्यसूचकः")) {
                                    cerr << "Error from aadyaarambhaangopaadhaanam for array antyasoochaka\n";
                                }
                               
                                
                                i = std::stoi(j[अस्थायि][std::to_string(अवगाढता_अस्थायि)+"_आद्यसूचकः"].get<string>());
                                if (!j[अस्थायि].contains(std::to_string(अवगाढता_अस्थायि)+"_अन्त्यसूचकः")) {
                                    cerr << "Error from aadyaarambhaangopaadhaanam for invalid "<< अस्थायि << "With array index " << अवगाढता_अस्थायि << "\n";
                                }
                                while (i <= std::stoi(j[अस्थायि][std::to_string(अवगाढता_अस्थायि)+"_अन्त्यसूचकः"].get<string>())) {
                                    सरणिः.push_back(अस्थायि+"["+std::to_string(i)+"]");
                                    i++;
                                }
                            }
                            
                            
                        } else {
                            if (ज्येष्ठम्.size()-1 >= अवगाढता_अस्थायि) {

                                for (i = ज्येष्ठम्[अवगाढता_अस्थायि-1]; i <=कनिष्ठम्[अवगाढता_अस्थायि-1]; i++) {
                                    for (int k=0; k < सरणिः_अस्थायि.size(); k++) {
                                        सरणिः.push_back(सरणिः_अस्थायि[k]+"["+std::to_string(i)+"]");
                                    }
                                }

                            } else {
                               
                                for ( i = j[अस्थायि][std::to_string(अवगाढता_अस्थायि)+"_आद्यसूचकः"];
                                    i <= j[अस्थायि][std::to_string(अवगाढता_अस्थायि)+"_अन्त्यसूचकः"]; i++) {
                                    for (int k=0; k < सरणिः_अस्थायि.size(); k++) {
                                        सरणिः.push_back(सरणिः_अस्थायि[k]+"["+std::to_string(i)+"]");
                                    }
    
                                }
                            }
                        }
                        for (int k=0; k < सरणिः.size(); k++) {
                            सरणिः_अस्थायि.push_back("&"+module_name+"::"+सरणिः[k]);
                        }

                        सरणिः = {};
                    }


                
                }else {
                    cerr << "Error from identifying the variable "<<अस्थायि ;
                }
            }
            सरणिः = सरणिः_अस्थायि;
            कूटाङ्कः = "{"+join_with(सरणिः, ",") + "}";
            


        } else {
            cerr <<  "Unknown bareword "<< उपाधानम् << "in आद्यारम्भाङ्गोपाधानम्_नियोजनम् \n "<<"\n" ;
        }

    }
    return कूटाङ्कः;
    

}