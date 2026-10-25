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


void आद्याङ्गवाक्यम्(कुञ्जीमूल्यरूपम्& प्रकरणसूची, std::string& वाक्यम्, unsigned long& अवस्थाचरण,  std::string& आद्यारम्भाङ्गनामम्, int वर्तमानाद्याङ्गम्, std::string& सञ्चिकापाठ, कुञ्जीमूल्यरूपम्& घटकप्रकरणसूची,const std::string& घटकनाम) {
    कुञ्जीमूल्यरूपम्* द्विरुक्तप्रकरणसूची = &प्रकरणसूची;
    int प्रथमक्रमः = 0;
    std::string कुञ्जी;
    std::string मूल्यम्;
    bool प्राप्तम् = false;   
    while (प्रथमक्रमः < द्विरुक्तप्रकरणसूची->size()) {
        if(शब्दशब्दनक्शा* आन्तरिकनक्शा = std::get_if<शब्दशब्दनक्शा>(&(*द्विरुक्तप्रकरणसूची)[प्रथमक्रमः])) {
            for (const auto& [कुञ्जी_1, मूल्यम्_1] : *आन्तरिकनक्शा) {
                कुञ्जी = कुञ्जी_1; 
                मूल्यम् = मूल्यम्_1;
                उद्धरणचिह्ननिष्कासनम्(कुञ्जी);
                if (कुञ्जी == "वाक्यम्") {
                    उद्धरणचिह्ननिष्कासनम्(मूल्यम्);
                    std::string व्यञ्जकम् = "";
                    आद्यारम्भाङ्गपश्चव्यञ्जकरूपान्तरणम् (मूल्यम्, व्यञ्जकम्, घटकप्रकरणसूची, अवस्थाचरण, आद्यारम्भाङ्गनामम्, वर्तमानाद्याङ्गम्, सञ्चिकापाठ, घटकनाम);
                    वाक्यम् = वाक्यम् +"\t\t\t\t" + व्यञ्जकम् + "\n";
                    प्राप्तम् = true;
                }

            }
            if (प्राप्तम्) {
                break;
            }  
        }
        प्रथमक्रमः++;

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



void आद्यारम्भाङ्गपश्चव्यञ्जकरूपान्तरणम् (std::string& मूल्यम्,std::string& व्यञ्जकम्, कुञ्जीमूल्यरूपम्& प्रकरणसूची, unsigned long& अवस्थाचरण,  std::string& आद्यारम्भाङ्गनामम्, int वर्तमानाद्याङ्गम्, std::string& सञ्चिकापाठ,const std::string& घटकनाम) {
    std::stack<std::string> स्तूपः;
    std::stringstream प्रवाहः(मूल्यम्);
    std::string अस्थायी;
    std::vector<std::string> प्रतीकाः;

    // The >> operator extracts strings separated by whitespace
    while (प्रवाहः >> अस्थायी) {
        प्रतीकाः.push_back(अस्थायी);
    }


    for (const std::string& प्रतीकः : प्रतीकाः) {
        if (!is_operator(प्रतीकः)) {
            स्तूपः.push(प्रतीकः);
        } else if (प्रतीकः == "U-") {
            std::string पदम् = स्तूपः.top();
            स्तूपः.pop();
            स्तूपः.push("-" + पदम्);
        } else if (प्रतीकः.find("शृङ्खला") != std::string::npos) {
            // Extract number of elements (e.g. 2 from "शृङ्खला2")
            std::string सङ्ख्यापाठः = प्रतीकः.substr(std::string("शृङ्खला").length());
            int गणना = std::stoi(सङ्ख्यापाठः);
            std::vector<std::string> अङ्गानि(गणना);
            // Pop in reverse order
            for (int ण = गणना - 1; ण >= 0; --ण) {
                अङ्गानि[ण] = स्तूपः.top();
                स्तूपः.pop();
            }
            // Format as pointer list: "&a, &b"
            std::string परिणामः = "";
            for (int ण = 0; ण < गणना; ++ण) {
                if (ण > 0) परिणामः += ", ";
                if (!अङ्गानि[ण].empty() && अङ्गानि[ण][0] == '&') {
                    परिणामः += अङ्गानि[ण];
                } else {
                    परिणामः += "&" + अङ्गानि[ण];
                }
            }
            स्तूपः.push(परिणामः);
        } else if (प्रतीकः == "+:" || प्रतीकः == "-:") {
            std::string द्वितीयाङ्गम् = स्तूपः.top();
            स्तूपः.pop();
            std::string प्रथमाङ्गम् = स्तूपः.top();
            स्तूपः.pop();
            स्तूपः.push(प्रथमाङ्गम् + प्रतीकः + द्वितीयाङ्गम्);
        } else {
            if (प्रतीकः == ":") {
                std::string द्वितीयाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                std::string प्रथमाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                स्तूपः.push(प्रथमाङ्गम् + ":" + द्वितीयाङ्गम्);

            } else if (प्रतीकः == "सूचकः") {
                std::string द्वितीयाङ्गम् = स्तूपः.top(); 
                स्तूपः.pop();
                std::string प्रथमाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                if (तारपरीक्षणम्(द्वितीयाङ्गम्, प्रकरणसूची)) {
                    स्तूपः.push(प्रथमाङ्गम् + "[" + द्वितीयाङ्गम् + ".getVal() - '0']");
                } else {
                    स्तूपः.push(प्रथमाङ्गम् + "[" + द्वितीयाङ्गम् + "]");
                }
            } else if (प्रतीकः == "=") {
                std::string द्वितीयाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                std::string प्रथमाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                std::string अस्थायितार = "";
                std::string अन्तर्विलम्बः = "";

                if (प्रथमाङ्गम्.find("#") != std::string::npos) {

                    अन्तर्विलम्बः = प्रथमाङ्गम्.substr(प्रथमाङ्गम्.find("#") + 1);
                    प्रथमाङ्गम् = स्तूपः.top(); 
                    स्तूपः.pop();
                    std::string अस्थायितार = "_" + अन्तर्विलम्बः + "_" + द्वितीयाङ्गम्;
                    सञ्चिकापाठ += "\twire " + अस्थायितार + ";\n";
                    std::string अन्तर्विलम्बाङ्गम् = "";
                    if (तारपरीक्षणम्(द्वितीयाङ्गम्, प्रकरणसूची)) {
                        // Confirmed via JSON AST: it is a wire!
                        अन्तर्विलम्बाङ्गम्  += "\t\t\t\tआद्यारम्भाङ्गम्_द्विनियोजनम्({&" + अस्थायितार + "}, string(1, " + द्वितीयाङ्गम् + ".getVal()));\n";
                    } else {
                        अन्तर्विलम्बाङ्गम्  += "\t\t\t\tआद्यारम्भाङ्गम्_द्विनियोजनम्({&" + अस्थायितार + "}, \"" + द्वितीयाङ्गम् + "\");\n";
                    }
                    अन्तर्विलम्बाङ्गम् += "\t\t\t\tआगामिनिष्पादनक्रमः_" + आद्यारम्भाङ्गनामम् + " = वर्तमानकालः + " + अन्तर्विलम्बः + ";\n";
                    अवस्थाचरण++;
                    अन्तर्विलम्बाङ्गम् += "\t\t\t\tनिष्पादनक्रमः_" + आद्यारम्भाङ्गनामम् + "++;\n";
                    अन्तर्विलम्बाङ्गम् += "\t\t\tcase " + std::to_string(अवस्थाचरण) + ":\n";
                    अन्तर्विलम्बाङ्गम् += "\t\t\t\tif (वर्तमानकालः == आगामिनिष्पादनक्रमः_" + आद्यारम्भाङ्गनामम् + ") निष्पादनक्रमः_" + आद्यारम्भाङ्गनामम् + "++;\n";
                    अन्तर्विलम्बाङ्गम् += "\t\t\t\telse break;\n";
                    अवस्थाचरण++;
                    अन्तर्विलम्बाङ्गम् += "\t\t\tcase " + std::to_string(अवस्थाचरण) + ":\n";

                    // 4. After delay, assign to destination wire (a)
                    अन्तर्विलम्बाङ्गम् += "\t\t\t\tआद्यारम्भाङ्गम्_द्विनियोजनम्({&" + प्रथमाङ्गम् + "}, string(1, " + अस्थायितार + ".getVal()))";
    
                    स्तूपः.push(अन्तर्विलम्बाङ्गम्);

                } else {
                    std::string स्रोतनाम, लक्ष्यनाम;
                    int स्रोत_उच्च, स्रोत_निम्न;
                    int लक्ष्य_उच्च, लक्ष्य_निम्न;
                    std::string सापेक्षित_उच्चपाठः, सापेक्षित_निम्नपाठः;
                    bool सापेक्षित_लक्ष्य_सूचकः = सापेक्षितसूचकपरीक्षणम्(प्रथमाङ्गम्, लक्ष्यनाम, सापेक्षित_उच्चपाठः, सापेक्षित_निम्नपाठः, प्रकरणसूची);
                    bool स्रोत_सूचकः = अङ्गसूचकपरीक्षणम्(द्वितीयाङ्गम्, स्रोतनाम, स्रोत_उच्च, स्रोत_निम्न);
                    bool लक्ष्य_सूचकः = अङ्गसूचकपरीक्षणम्(प्रथमाङ्गम्, लक्ष्यनाम, लक्ष्य_उच्च, लक्ष्य_निम्न);
                    if (लक्ष्य_सूचकः && अनावृतपरीक्षणम्(लक्ष्यनाम, प्रकरणसूची)) {
                        लक्ष्य_सूचकः = false;
                    }
                    if (स्रोत_सूचकः && अनावृतपरीक्षणम्(स्रोतनाम, प्रकरणसूची)) {
                        स्रोत_सूचकः = false;
                    }
                    if (सापेक्षित_लक्ष्य_सूचकः) {
                        // LHS has relative indexed-part-select: a[idx +: 4] = ...
                        std::string द्वितीयमूल्यम् = तारपरीक्षणम्(द्वितीयाङ्गम्, प्रकरणसूची) ? ("string(1, " + द्वितीयाङ्गम् + ".getVal())") : ("\"" + द्वितीयाङ्गम् + "\"");
                        स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्_लक्ष्यसूचकम्(" + लक्ष्यनाम + ", " + सापेक्षित_उच्चपाठः + ", " + सापेक्षित_निम्नपाठः + ", " + द्वितीयमूल्यम् + ")");
                    } else if (स्रोत_सूचकः && लक्ष्य_सूचकः) {
                        // Both LHS and RHS sliced: a[7:0] = b[7:0]
                        स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्_उभयसूचकम्(" + लक्ष्यनाम + ", " + std::to_string(लक्ष्य_उच्च) + ", " + std::to_string(लक्ष्य_निम्न) + ", " + स्रोतनाम + ", " + std::to_string(स्रोत_उच्च) + ", " + std::to_string(स्रोत_निम्न) + ")");
                    } else if (स्रोत_सूचकः) {
                        // RHS is sliced: a = b[7:0]
                        स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्_सूचकम्({&" + प्रथमाङ्गम् + "}, " + स्रोतनाम + ", " + std::to_string(स्रोत_उच्च) + ", " + std::to_string(स्रोत_निम्न) + ")");
                    } else if (लक्ष्य_सूचकः) {
                        // LHS is sliced: a[7:0] = ...
                        std::string द्वितीयमूल्यम् = तारपरीक्षणम्(द्वितीयाङ्गम्, प्रकरणसूची) ? ("string(1, " + द्वितीयाङ्गम् + ".getVal())") : ("\"" + द्वितीयाङ्गम् + "\"");
                        स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्_लक्ष्यसूचकम्(" + लक्ष्यनाम + ", " + std::to_string(लक्ष्य_उच्च) + ", " + std::to_string(लक्ष्य_निम्न) + ", " + द्वितीयमूल्यम् + ")");
                    } else if (तारपरीक्षणम्(द्वितीयाङ्गम्, प्रकरणसूची)) {
                         // Confirmed via JSON AST: it is a normal wire!
                        int तारविस्तार = तारविस्तारप्राप्तिः(प्रथमाङ्गम्, प्रकरणसूची);
                        std::string लक्ष्यसूची;
                        if (तारविस्तार > 1 && प्रथमाङ्गम्.find("[") == std::string::npos && प्रथमाङ्गम्.find("&") == std::string::npos) {
                            लक्ष्यसूची = "{";
                            for (int ब = तारविस्तार - 1; ब >= 0; --ब) {
                                if (ब < तारविस्तार - 1) लक्ष्यसूची += ", ";
                                लक्ष्यसूची += "&" + प्रथमाङ्गम् + "[" + std::to_string(ब) + "]";
                            }
                            लक्ष्यसूची += "}";
                        } else {
                            लक्ष्यसूची = (प्रथमाङ्गम्.find("&") != std::string::npos) ? ("{" + प्रथमाङ्गम् + "}") : ("{&" + प्रथमाङ्गम् + "}");
                        }
                        स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्(" + लक्ष्यसूची + ", string(1, " + द्वितीयाङ्गम् + ".getVal()))");
                    } else {
                        // Otherwise: it is a literal constant!
                        int तारविस्तार = तारविस्तारप्राप्तिः(प्रथमाङ्गम्, प्रकरणसूची);
                        std::string लक्ष्यसूची;
                        if (तारविस्तार > 1 && प्रथमाङ्गम्.find("[") == std::string::npos && प्रथमाङ्गम्.find("&") == std::string::npos) {
                            लक्ष्यसूची = "{";
                            for (int ब = तारविस्तार - 1; ब >= 0; --ब) {
                                if (ब < तारविस्तार - 1) लक्ष्यसूची += ", ";
                                लक्ष्यसूची += "&" + प्रथमाङ्गम् + "[" + std::to_string(ब) + "]";
                            }
                            लक्ष्यसूची += "}";
                        } else {
                            लक्ष्यसूची = (प्रथमाङ्गम्.find("&") != std::string::npos) ? ("{" + प्रथमाङ्गम् + "}") : ("{&" + प्रथमाङ्गम् + "}");
                        }
                        स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्(" + लक्ष्यसूची + ", \"" + द्वितीयाङ्गम् + "\")");
                    }
                }
            } else if (प्रतीकः == "<=") {
                std::string द्वितीयाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                std::string प्रथमाङ्गम् = स्तूपः.top();
                स्तूपः.pop();

                if (प्रथमाङ्गम्.find("#") != std::string::npos) {
                    std::string अन्तर्विलम्बः = प्रथमाङ्गम्.substr(प्रथमाङ्गम्.find("#") + 1);
                    प्रथमाङ्गम् = स्तूपः.top();
                    स्तूपः.pop();
                    static int छायाक्रमाङ्कः = 0;
                    std::string छायानाम = "_छाया_" + प्रथमाङ्गम् + "_" + std::to_string(छायाक्रमाङ्कः);
                    std::string कालनाम = "_कालः_" + प्रथमाङ्गम् + "_" + std::to_string(छायाक्रमाङ्कः);
                    std::string कृतम्नाम = "_कृतम्_" + प्रथमाङ्गम् + "_" + std::to_string(छायाक्रमाङ्कः);
                    std::string फलननाम = घटकनाम + "_" + प्रथमाङ्गम् + "_" + आद्यारम्भाङ्गनामम् + "_" + std::to_string(छायाक्रमाङ्कः);
                    छायाक्रमाङ्कः++;
                    
                    सञ्चिकापाठ += "\twire " + छायानाम + ";\n";
                    सञ्चिकापाठ += "\tint " + कालनाम + " = -1;\n";
                    सञ्चिकापाठ += "\tbool " + कृतम्नाम + " = false;\n";
                    सञ्चिकापाठ += "\tvoid " + फलननाम + "() {\n";
                    सञ्चिकापाठ += "\t\tif (वर्तमानकालः >= " + कालनाम + " && " + कालनाम + " != -1 && !" + कृतम्नाम + ") {\n";
                    सञ्चिकापाठ += "\t\t\t" + प्रथमाङ्गम् + " = " + छायानाम + ";\n";
                    सञ्चिकापाठ += "\t\t\t" + कृतम्नाम + " = true;\n";
                    सञ्चिकापाठ += "\t\t}\n";
                    सञ्चिकापाठ += "\t}\n";
                    
                    std::ofstream नामसञ्चिका("all_functions.txt", std::ios::app);
                    if (नामसञ्चिका.is_open()) {
                        नामसञ्चिका << फलननाम << "\n";
                    }
                    

                    std::string अन्तर्विलम्बाङ्गम् = "";
                    if (तारपरीक्षणम्(द्वितीयाङ्गम्, प्रकरणसूची)) {
                        अन्तर्विलम्बाङ्गम् += "\t\t\t\tआद्यारम्भाङ्गम्_द्विनियोजनम्(" + छायानाम + ", " + द्वितीयाङ्गम् + ");\n";
                    } else {
                        अन्तर्विलम्बाङ्गम् += "\t\t\t\tआद्यारम्भाङ्गम्_द्विनियोजनम्({&" + छायानाम + "}, \"" + द्वितीयाङ्गम् + "\");\n";
                    }
                    अन्तर्विलम्बाङ्गम् += "\t\t\t\t" + कालनाम + " = वर्तमानकालः + " + अन्तर्विलम्बः + ";";
                    स्तूपः.push(अन्तर्विलम्बाङ्गम्);
                } else {
                    // Regular non-blocking assignment without delay (e.g. a <= b)
                    if (तारपरीक्षणम्(द्वितीयाङ्गम्, प्रकरणसूची)) {
                        std::string लक्ष्यसूची = (प्रथमाङ्गम्.find("&") != std::string::npos) ? ("{" + प्रथमाङ्गम् + "}") : ("{&" + प्रथमाङ्गम् + "}");
                        if (प्रथमाङ्गम्.find("&") == std::string::npos && प्रथमाङ्गम्.find("[") == std::string::npos) {
                            स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्(" + प्रथमाङ्गम् + ", " + द्वितीयाङ्गम् + ")");
                        } else {
                            स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्(" + लक्ष्यसूची + ", string(1, " + द्वितीयाङ्गम् + ".getVal()))");
                        }

                    } else {
                        std::string लक्ष्यसूची = (प्रथमाङ्गम्.find("&") != std::string::npos) ? ("{" + प्रथमाङ्गम् + "}") : ("{&" + प्रथमाङ्गम् + "}");
                        स्तूपः.push("आद्यारम्भाङ्गम्_द्विनियोजनम्(" + लक्ष्यसूची + ", \"" + द्वितीयाङ्गम् + "\")");
                    }
                }
            } else if (प्रतीकः == "/" || प्रतीकः == "+" || प्रतीकः == "-" || प्रतीकः == "*" || प्रतीकः == "%") {
                std::string द्वितीयाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                std::string प्रथमाङ्गम् = स्तूपः.top();
                स्तूपः.pop();
                स्तूपः.push("(" + प्रथमाङ्गम् + " " + प्रतीकः + " " + द्वितीयाङ्गम् + ")");
            } else {
                cerr << "To handle this operator " << प्रतीकः << endl;
            }
        }
    }
    if (स्तूपः.size() == 1) {
        व्यञ्जकम् = स्तूपः.top() + ";\n";
    } else {
        cerr << "Error in postfix expression " << मूल्यम्;
        exit(1);
    }

}

bool तारपरीक्षणम् (const std::string& चरनाम, कुञ्जीमूल्यरूपम्& प्रकरणसूची) {
    std::string शुद्धनाम = चरनाम;
    उद्धरणचिह्ननिष्कासनम्(शुद्धनाम);
    // If it's an indexed or sliced wire like "b[7:0]" or "b[3]", extract the base name "b"
    size_t pos = शुद्धनाम.find("[");
    if (pos != std::string::npos) {
        शुद्धनाम = शुद्धनाम.substr(0, pos);
    }
    for (const auto& वस्तु : प्रकरणसूची) {
        if (const auto* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&वस्तु)) {
            for (const auto& [कुञ्जी, मूल्यधारकः] : *आन्तरिकनक्शा) {
                std::string नाम = कुञ्जी;
                उद्धरणचिह्ननिष्कासनम्(नाम);
                if (नाम == शुद्धनाम && मूल्यधारकः.स्थानधारकः) {
                    for (const auto& उपवस्तु : *(मूल्यधारकः.स्थानधारकः)) {
                        if (const auto* उपनक्शा = std::get_if<शब्दशब्दनक्शा>(&उपवस्तु)) {
                            for (const auto& [उकुञ्जी, उमूल्यम्] : *उपनक्शा) {
                                std::string k = उकुञ्जी, v = उमूल्यम्;
                                उद्धरणचिह्ननिष्कासनम्(k);
                                उद्धरणचिह्ननिष्कासनम्(v);
                                if (k == "प्रकारः" && v == "तारः") {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}


bool अङ्गसूचकपरीक्षणम् (const std::string& पदम्, std::string& तारनाम, int& उच्च, int& निम्न) {
    size_t स्थानम्  = पदम्.find("[");
    if (स्थानम्  != std::string::npos && पदम्.back() == ']') {
        तारनाम = पदम्.substr(0, स्थानम् );
        std::string range = पदम्.substr(स्थानम्  + 1, पदम्.size() - स्थानम् - 2);
        size_t विरामस्थानम्  = range.find(":");
        if (विरामस्थानम्  != std::string::npos) {
            std::string उच्च_पाठ्य = range.substr(0, विरामस्थानम् );
            std::string निम्न_पाठ्य = range.substr(विरामस्थानम्  + 1);
            if (पूर्णाङ्कपरीक्षणम्(उच्च_पाठ्य) && पूर्णाङ्कपरीक्षणम्(निम्न_पाठ्य)) {
                उच्च = std::stoi(उच्च_पाठ्य);
                निम्न = std::stoi(निम्न_पाठ्य);
                return true;
            }
            return false;
        } else {
            if (पूर्णाङ्कपरीक्षणम्(range)) {
                उच्च = निम्न = std::stoi(range);
                return true;
            }
            return false;
         
        }
    }
    return false;
}

bool पूर्णाङ्कपरीक्षणम् (const std::string& पाठ्यम्) {
    if (पाठ्यम्.empty()) return false;
    for (char c : पाठ्यम्) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

bool अनावृतपरीक्षणम् (const std::string& चरनाम, कुञ्जीमूल्यरूपम्& प्रकरणसूची) {
    std::string शुद्धनाम = चरनाम;
    उद्धरणचिह्ननिष्कासनम्(शुद्धनाम);
    for (const auto& वस्तु : प्रकरणसूची) {
        if (const auto* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&वस्तु)) {
            for (const auto& [कुञ्जी, मूल्यधारकः] : *आन्तरिकनक्शा) {
                std::string नाम = कुञ्जी;
                उद्धरणचिह्ननिष्कासनम्(नाम);
                if (नाम == शुद्धनाम && मूल्यधारकः.स्थानधारकः) {
                    for (const auto& उपवस्तु : *(मूल्यधारकः.स्थानधारकः)) {
                        if (const auto* उपनक्शा = std::get_if<शब्दपिण्डनक्शा>(&उपवस्तु)) {
                            for (const auto& [उकुञ्जी, उमूल्यम्] : *उपनक्शा) {
                                std::string k = उकुञ्जी;
                                उद्धरणचिह्ननिष्कासनम्(k);
                                if (k.find("अनावृत_अवगाढता") != std::string::npos) {
                                    return true; // Confirmed: It is an array/memory!
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool सापेक्षितसूचकपरीक्षणम् (const std::string& पदम्, std::string& तारनाम, std::string& उच्चपाठः, std::string& निम्नपाठः, कुञ्जीमूल्यरूपम्& प्रकरणसूची) {
    size_t स्थानम् = पदम्.find("[");
    if (स्थानम् != std::string::npos && पदम्.back() == ']') {
        तारनाम = पदम्.substr(0, स्थानम्);
        std::string सीमा = पदम्.substr(स्थानम् + 1, पदम्.size() - स्थानम् - 2);
        
        size_t धनस्थानम् = सीमा.find("+:");
        size_t ऋणस्थानम् = सीमा.find("-:");
        
        if (धनस्थानम् != std::string::npos) {
            std::string आधारः = सीमा.substr(0, धनस्थानम्);
            std::string विस्तारपाठः = सीमा.substr(धनस्थानम् + 2);
            std::string आधारव्यञ्जकम् = तारपरीक्षणम्(आधारः, प्रकरणसूची) ? ("(" + आधारः + ".getVal() - '0')") : आधारः;
            int विस्तारः = std::stoi(विस्तारपाठः);
            
            // a[आधारः +: विस्तारः] => bits [आधारः + विस्तारः - 1 : आधारः]
            निम्नपाठः = आधारव्यञ्जकम्;
            उच्चपाठः = आधारव्यञ्जकम् + " + " + std::to_string(विस्तारः - 1);
            return true;
        } else if (ऋणस्थानम् != std::string::npos) {
            std::string आधारः = सीमा.substr(0, ऋणस्थानम्);
            std::string विस्तारपाठः = सीमा.substr(ऋणस्थानम् + 2);
            std::string आधारव्यञ्जकम् = तारपरीक्षणम्(आधारः, प्रकरणसूची) ? ("(" + आधारः + ".getVal() - '0')") : आधारः;
            int विस्तारः = std::stoi(विस्तारपाठः);
            
            // a[आधारः -: विस्तारः] => bits [आधारः : आधारः - विस्तारः + 1]
            उच्चपाठः = आधारव्यञ्जकम्;
            निम्नपाठः = आधारव्यञ्जकम् + " - " + std::to_string(विस्तारः - 1);
            return true;
        }
    }
    return false;
}

int तारविस्तारप्राप्तिः(const std::string& चरनाम, कुञ्जीमूल्यरूपम्& प्रकरणसूची) {
    std::string शुद्धनाम = चरनाम;
    उद्धरणचिह्ननिष्कासनम्(शुद्धनाम);
    size_t pos = शुद्धनाम.find("[");
    if (pos != std::string::npos) शुद्धनाम = शुद्धनाम.substr(0, pos);
    
    for (const auto& वस्तु : प्रकरणसूची) {
        if (const auto* पिण्ड = std::get_if<शब्दपिण्डनक्शा>(&वस्तु)) {
            for (const auto& [कु, मू] : *पिण्ड) {
                std::string k = कु;
                उद्धरणचिह्ननिष्कासनम्(k);
                if (k == शुद्धनाम && मू.स्थानधारकः) {
                    int संवृत = 1;
                    bool प्राप्तम् = false;
                    for (const auto& उप : *(मू.स्थानधारकः)) {
                        if (const auto* नक्शा = std::get_if<शब्दशब्दनक्शा>(&उप)) {
                            for (const auto& [उकु, उमू] : *नक्शा) {
                                std::string उपकुञ्जी = उकु, उपमूल्यम् = उमू;
                                उद्धरणचिह्ननिष्कासनम्(उपकुञ्जी); उद्धरणचिह्ननिष्कासनम्(उपमूल्यम्);
                                if (उपकुञ्जी.find("_अन्त्यसूचकः") != std::string::npos) {
                                    std::string उपसर्ग = उपकुञ्जी.substr(0, उपकुञ्जी.find("_अन्त्यसूचकः"));
                                    std::string आद्यकु = उपसर्ग + "_आद्यसूचकः";
                                    std::string आद्यमू = शब्दतत्त्वप्राप्तिः(*(मू.स्थानधारकः), आद्यकु);
                                    if (!आद्यमू.empty()) {
                                        संवृत *= (std::abs(std::stoi(उपमूल्यम्) - std::stoi(आद्यमू)) + 1);
                                        प्राप्तम् = true;
                                    }
                                }
                            }
                        }
                    }
                    if (प्राप्तम्) return संवृत;
                }
            }
        }
    }
    return 1;
}
