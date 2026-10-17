#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <stack>
#include <regex>
#include <vector>
#include <variant>
#include <queue>
#include <memory>
#include "json2map.h"
#include <algorithm> // Required for std::remove
using namespace std;


void मानचित्रपरिवर्तनम् (std::string सञ्चिकानाम, std::ifstream& सञ्चिका, कुञ्जीमूल्यरूपम्& प्रकरणसूची) {
    int पङ्क्तिसङ्ख्या=0;
    कुञ्जीमूल्यरूपम्* द्विरुक्तप्रकरणसूची = &प्रकरणसूची;
    
    std::stack<int> स्तूपः = std::stack<int>();
    if (!सञ्चिका.is_open()) {
        std::cerr<<"Cannot open input file\n";
        exit(1);
    }
    
    std::string पङ्क्तिः;
    std::string कुञ्जी;
    std::smatch मेलनम्;
    std::regex regex_2("^\\s*$");
    std::regex regex_1  ("^\\s*\""); //~=
    std::regex regex_3("^\\s*(\"(?:[^\"\\\\]|\\\\.)*\")");
    std::regex regex_4("^\\s*:\\s*"); 
    std::regex regex_5;
    std::regex regex_6("^\\s*,");
    std::regex regex_7("^\\s*([0-9\\-]+)");
    std::regex regex_8("^\\s*\\[");
    std::regex regex_9("^\\s*\\]");
    std::regex regex_10("^\\s*$");
    std::regex regex_11("^\\s*,");
    std::regex regex_12("^\\s*\\{");
    std::regex regex_13("^\\s*\\}");
    int क्रमः =0;
    std::getline(सञ्चिका, पङ्क्तिः);
    पङ्क्तिसङ्ख्या=0;
    bool सञ्चिकानिवृतिपरीक्षा = false;
    while (!सञ्चिका.eof() && !सञ्चिकानिवृतिपरीक्षा) {
        while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {

            std::getline(सञ्चिका, पङ्क्तिः);
            पङ्क्तिसङ्ख्या++;
            if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
        }
        if (std::regex_search(पङ्क्तिः,  regex_13)) {
            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_13, "");
            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
            if (!स्तूपः.empty()) {
                क्रमः = स्तूपः.top();
                
                स्तूपः.pop();
                while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                    std::getline(सञ्चिका, पङ्क्तिः);
                    पङ्क्तिसङ्ख्या++;
                    if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                }                
            } else {
                cerr << "Error in JSON construction";
                exit(1);
            }
            द्विरुक्तप्रकरणसूची = सूचकपर्यन्तसञ्चरणम् ( स्तूपः, प्रकरणसूची);
            
  
        } else if (std::regex_search(पङ्क्तिः,regex_2)) {
        } else if (std::regex_search(पङ्क्तिः, मेलनम्, regex_3)) {
            कुञ्जी = मेलनम्[1];
            regex_5 = std::regex(कुञ्जी);
                
            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_5, "");

            while (std::regex_search(पङ्क्तिः, regex_2)) {
                std::getline(सञ्चिका, पङ्क्तिः);
                पङ्क्तिसङ्ख्या++;
            }
            if (!std::regex_search(पङ्क्तिः, regex_4)) {
                cerr << "Error in JSON in seperation of key and values\n" << पङ्क्तिः << endl;
                exit(1);

            } else {
                पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_4, "");
            }
            
            while (std::regex_search(पङ्क्तिः, regex_2)&& !सञ्चिकानिवृतिपरीक्षा) {
                std::getline(सञ्चिका, पङ्क्तिः);
                पङ्क्तिसङ्ख्या++;
                if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
            }
            if (std::regex_search(पङ्क्तिः, regex_8)) {
                पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_8,"");   
                
                while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                    std::getline(सञ्चिका, पङ्क्तिः);
                    पङ्क्तिसङ्ख्या++;
                    if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                }
                if (std::regex_search(पङ्क्तिः, regex_3)) {
                    शब्दसूची अस्थायी;
                    while(!std::regex_search(पङ्क्तिः, regex_9)) {
                        if (std::regex_search(पङ्क्तिः, मेलनम्, regex_3)) {
                            std::string अस्थायी_1 = मेलनम्[1];
                            अस्थायी.push_back(अस्थायी_1);
                            regex_5 = std::regex(अस्थायी_1);
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_5, "");
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
                        } else {
                            cerr << "Error in string array";
                            exit(1);
                        }
                        while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                            std::getline(सञ्चिका, पङ्क्तिः);
                            पङ्क्तिसङ्ख्या++;
                            if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                        }
                        if (std::regex_search(पङ्क्तिः, regex_11)) {
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_11, "");                            
                        }
                        while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                            std::getline(सञ्चिका, पङ्क्तिः);
                            पङ्क्तिसङ्ख्या++;
                            if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                        }
                    }
                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_9, "");
                    शब्दसूचिनक्शा नक्शा;
                    नक्शा[कुञ्जी] = अस्थायी;
                    द्विरुक्तप्रकरणसूची->push_back(नक्शा);
                } else if (std::regex_search(पङ्क्तिः, regex_7)) {
                    अङ्कसूची अस्थायी;
                    while(!std::regex_search(पङ्क्तिः, regex_9)) {
                        if (std::regex_search(पङ्क्तिः, मेलनम्, regex_7)) {
                            std::string अस्थायी_2 = मेलनम्[1];
                            int अस्थायी_1 = std::stoi(अस्थायी_2);
                            अस्थायी.push_back(अस्थायी_1);
                            regex_5 = std::regex(अस्थायी_2);
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_5, "");
                        } else {
                            cerr << "Error in integer array";
                            exit(1);
                        }
                        while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                            std::getline(सञ्चिका, पङ्क्तिः);
                            पङ्क्तिसङ्ख्या++;
                            if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                        }
                        if (std::regex_search(पङ्क्तिः, regex_11)) {
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_11, "");
                        }
                    }
                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_9, "");
                    अङ्कसूचिनक्शा नक्शा;
                    नक्शा[कुञ्जी] = अस्थायी;
                    द्विरुक्तप्रकरणसूची->push_back(नक्शा);
                } else if (std::regex_search(पङ्क्तिः, regex_9)) {
                    //Empty array check
                    // 1. Record the empty array under the key
                    शब्दसूचिनक्शा नक्शा;
                    शब्दसूची रिक्तसूची;
                    नक्शा[कुञ्जी] = रिक्तसूची;
                    द्विरुक्तप्रकरणसूची->push_back(नक्शा);

                    // 2. Remove ']' and comma ','
                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_9, "");
                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
                    
                    // 3. Advance to the next non-empty line
                    while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                        std::getline(सञ्चिका, पङ्क्तिः);
                        पङ्क्तिसङ्ख्या++;
                        if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                    }
                } else if (std::regex_search(पङ्क्तिः, regex_8)) {
                    //Nested Array detected
                     अन्तर्हितसूची बहुआयामसूची;
                    while (!std::regex_search(पङ्क्तिः, regex_9) && !सञ्चिकानिवृतिपरीक्षा) {
                        // Look for each inner row starting with '['
                        if (std::regex_search(पङ्क्तिः, regex_8)) {
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_8, "");
                            
                            शब्दसूची पंक्ति_शब्द;
                            अङ्कसूची पंक्ति_अङ्क;
                            bool अङ्कप्रकारः = false;
                            while (!std::regex_search(पङ्क्तिः, regex_9) && !सञ्चिकानिवृतिपरीक्षा) {
                                while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                                    std::getline(सञ्चिका, पङ्क्तिः);
                                    पङ्क्तिसङ्ख्या++;
                                    if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                                }
                                if (std::regex_search(पङ्क्तिः, regex_9)) break;
                                // Inner nested bracket (3D/4D): skip bracket markers
                                if (std::regex_search(पङ्क्तिः, regex_8)) {
                                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_8, "");
                                }
                                // String element inside row
                                else if (std::regex_search(पङ्क्तिः, मेलनम्, regex_3)) {
                                    पंक्ति_शब्द.push_back(मेलनम्[1]);
                                    पङ्क्तिः = पङ्क्तिः.substr(मेलनम्.position(0) + मेलनम्.length(0));
                                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
                                }
                                // Integer element inside row
                                else if (std::regex_search(पङ्क्तिः, मेलनम्, regex_7)) {
                                    अङ्कप्रकारः = true;
                                    पंक्ति_अङ्क.push_back(std::stoi(मेलनम्[1]));
                                    पङ्क्तिः = पङ्क्तिः.substr(मेलनम्.position(0) + मेलनम्.length(0));
                                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
                                }
                                // Strip commas
                                else if (std::regex_search(पङ्क्तिः, regex_6)) {
                                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
                                }
                                else {
                                    std::getline(सञ्चिका, पङ्क्तिः);
                                    पङ्क्तिसङ्ख्या++;
                                    if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                                }
                            }
                            // Inner row finished: strip inner ']' and comma
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_9, "");
                            पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
                            if (अङ्कप्रकारः && !पंक्ति_अङ्क.empty()) {
                                बहुआयामसूची.push_back(पंक्ति_अङ्क);
                            } else {
                                बहुआयामसूची.push_back(पंक्ति_शब्द);
                            }
                        }
                        while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                            std::getline(सञ्चिका, पङ्क्तिः);
                            पङ्क्तिसङ्ख्या++;
                            if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                        }
                    }
                    // Outer array finished: strip outer ']' and comma
                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_9, "");
                    पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
                    // Save into द्विरुक्तप्रकरणसूची
                    शब्दान्तर्हितसूचीनक्शा नक्शा;
                    नक्शा[कुञ्जी] = बहुआयामसूची;
                    द्विरुक्तप्रकरणसूची->push_back(नक्शा);
                    // Advance to next non-empty line
                    while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                        std::getline(सञ्चिका, पङ्क्तिः);
                        पङ्क्तिसङ्ख्या++;
                        if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                    }
                    
                } else {
                    cerr << "Error in array datatype in JSON value";
                    exit(1);
                }
            } else if (std::regex_search(पङ्क्तिः, मेलनम्, regex_3)) {
                std::string मूल्यम् = मेलनम्[1];


                शब्दशब्दनक्शा नक्शा;
                नक्शा[कुञ्जी] = मूल्यम्;
                द्विरुक्तप्रकरणसूची->push_back(नक्शा);
                //regex_5 = std::regex(मूल्यम्);
                //पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_5, "");
                पङ्क्तिः = पङ्क्तिः.substr(मेलनम्.position(0) + मेलनम्.length(0));
                पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");

            } else if (std::regex_search(पङ्क्तिः, मेलनम्, regex_7)) {
                
                शब्दाङ्कनक्शा नक्शा;
                int मूल्यम् = std::stoi(मेलनम्[1]);
                नक्शा[कुञ्जी] = मूल्यम् ;
                द्विरुक्तप्रकरणसूची->push_back(नक्शा); 
                regex_5 = std::regex(std::to_string(मूल्यम्));
                पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_5, "");
                पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_6, "");
            } else if (std::regex_search(पङ्क्तिः, regex_12)) {
                पिण्डः प्रथमपिण्डः;
                प्रथमपिण्डः.स्थानधारकः=std::make_shared<कुञ्जीमूल्यरूपम्>();
                शब्दपिण्डनक्शा नक्शा;
                नक्शा[कुञ्जी] = प्रथमपिण्डः;
                द्विरुक्तप्रकरणसूची->push_back(नक्शा);
                स्तूपः.push(क्रमः);
                क्रमः = -1;
                द्विरुक्तप्रकरणसूची = प्रथमपिण्डः.स्थानधारकः.get(); 
                पङ्क्तिः = std::regex_replace(पङ्क्तिः, regex_12, "");
                while (std::regex_search(पङ्क्तिः, regex_2) && !सञ्चिकानिवृतिपरीक्षा) {
                    std::getline(सञ्चिका, पङ्क्तिः);
                    पङ्क्तिसङ्ख्या++;
                    if (सञ्चिका.eof()) सञ्चिकानिवृतिपरीक्षा = true;
                }

            } else {
                cout << पङ्क्तिः << endl << पङ्क्तिसङ्ख्या <<endl;
                cerr << "Error in JSON value";
                exit(1);
            }
        } else {
            cerr << "Error in key value";
            exit(1);
        }
        क्रमः++;
    }
}
                

void प्रवेशः (std::string सञ्चिकानाम, std::ofstream& सञ्चिका, कुञ्जीमूल्यरूपम्& प्रकरणसूची) {
    std::stack<int> क्रमस्तूपः = std::stack<int>();
    std::stack<int>परिमाणस्तूपः = std::stack<int>();
    कुञ्जीमूल्यरूपम्* द्विरुक्तप्रकरणसूची = &प्रकरणसूची;
    परिमाणस्तूपः.push(द्विरुक्तप्रकरणसूची->size());
    if (!सञ्चिका.is_open()) {
        std::cerr<<"Cannot open output file\n";
    }
    int क्रमः = 0;
    while (!परिमाणस्तूपः.empty()) {
        // Accessing map by index
        if (शब्दशब्दनक्शा* आन्तरिकनक्शा = std::get_if<शब्दशब्दनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                सञ्चिका << कुञ्जी << " : " << मूल्यम् << std::endl;
            }
        }else if (शब्दाङ्कनक्शा* आन्तरिकनक्शा = std::get_if<शब्दाङ्कनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                सञ्चिका << कुञ्जी << " : " << मूल्यम् << std::endl;
            }
        } else if (अङ्कसूचिनक्शा* आन्तरिकनक्शा = std::get_if<अङ्कसूचिनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                सञ्चिका << कुञ्जी << " : " << "[" ;
                for (int म = 0; म < मूल्यम्.size(); ++म) {
                    सञ्चिका << मूल्यम्[म] << " ";
                }
                सञ्चिका << "]" <<endl;
            }
        } else if (शब्दसूचिनक्शा* आन्तरिकनक्शा = std::get_if<शब्दसूचिनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                सञ्चिका << कुञ्जी << " : " << "[" ;
                for (int म = 0; म < मूल्यम्.size(); ++म) {
                    सञ्चिका << मूल्यम्[म] << " ";
                }
                सञ्चिका << "]" <<endl;
            }
        } else if (शब्दपिण्डनक्शा* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            क्रमस्तूपः.push(क्रमः);
            क्रमः = -1;
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                सञ्चिका << कुञ्जी << " :" << "{\n" ;
                द्विरुक्तप्रकरणसूची = मूल्यम्.स्थानधारकः.get();
                परिमाणस्तूपः.push(द्विरुक्तप्रकरणसूची->size());
            }

        } else if (शब्दान्तर्हितसूचीनक्शा* आन्तरिकनक्शा = std::get_if<शब्दान्तर्हितसूचीनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                सञ्चिका << कुञ्जी << " : [" << std::endl;
                for (const auto& पंक्ति : मूल्यम्) {
                    सञ्चिका << "  [ ";
                    if (std::holds_alternative<शब्दसूची>(पंक्ति)) {
                        for (const auto& s : std::get<शब्दसूची>(पंक्ति)) सञ्चिका << s << " ";
                    } else if (std::holds_alternative<अङ्कसूची>(पंक्ति)) {
                        for (const auto& n : std::get<अङ्कसूची>(पंक्ति)) सञ्चिका << n << " ";
                    }
                    सञ्चिका << "]" << std::endl;
                }
                सञ्चिका << "]" << std::endl;
            }
        
        } else {
            cerr << "New type of array; To be handled" << endl;
        }
        while (क्रमः == परिमाणस्तूपः.top()-1) {
            परिमाणस्तूपः.pop();    
            if (!क्रमस्तूपः.empty()) {
                क्रमः = क्रमस्तूपः.top();
                क्रमस्तूपः.pop();
            }            
            द्विरुक्तप्रकरणसूची = सूचकपर्यन्तसञ्चरणम् ( क्रमस्तूपः, प्रकरणसूची);
                        
            if (द्विरुक्तप्रकरणसूची == nullptr ) {
                cerr << "Error from soochakaparyanta";
            }
            if (परिमाणस्तूपः.empty()) {
                break;
            } else {
                सञ्चिका << "}" <<endl;
            }
        }
        क्रमः++;
    }
}


template <typename क>
void स्तूपानुक्रमपरिवर्तनम् (std::stack<क> स्रोतस्तूपः, std::queue<क>& लक्ष्यानुक्रमः) {
    std::stack<क> अस्थायिस्तूपः;
    // First flip: Source -> Temp (Reverses order)
    while (!स्रोतस्तूपः.empty()) {
        
        अस्थायिस्तूपः.push(std::move(स्रोतस्तूपः.top())); // Use std::move for efficiency
        स्रोतस्तूपः.pop();
    }

    // Second flip: Temp -> Queue (Restores order)
    while (!अस्थायिस्तूपः.empty()) {
        लक्ष्यानुक्रमः.push(std::move(अस्थायिस्तूपः.top()));
        अस्थायिस्तूपः.pop();
    }
}
template <typename क>
void सूच्यनुक्रमपरिवर्तनम् (std::vector<क>& सूची, std::queue<क>& लक्ष्यानुक्रमः) {
    for (const auto& item : सूची) {
        लक्ष्यानुक्रमः.push(item);
    }
}



कुञ्जीमूल्यरूपम्* सूचकपर्यन्तसञ्चरणम् (std::stack<int> स्तूपः, कुञ्जीमूल्यरूपम्& प्रकरणसूची) {
    std::queue<int> द्विरुक्तस्तूपानुक्रमः;
    कुञ्जीमूल्यरूपम्* द्विरुक्तप्रकरणसूची;
    स्तूपानुक्रमपरिवर्तनम् (स्तूपः , द्विरुक्तस्तूपानुक्रमः );
    द्विरुक्तप्रकरणसूची = &प्रकरणसूची;
    while (!द्विरुक्तस्तूपानुक्रमः.empty()) {
        int& मूल्यम्1 = द्विरुक्तस्तूपानुक्रमः.front(); 
        if(शब्दपिण्डनक्शा* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&(*द्विरुक्तप्रकरणसूची)[मूल्यम्1])) {
            for (const auto& [प्रथमकुञ्जी, मूल्यम्2] : *आन्तरिकनक्शा) {
                द्विरुक्तप्रकरणसूची = मूल्यम्2.स्थानधारकः.get();
            }      
        } else {
            return nullptr;
            //cerr << "Error while traversing";
            
        }
        द्विरुक्तस्तूपानुक्रमः.pop();
    }
    return द्विरुक्तप्रकरणसूची;
}
                
std::string शब्दतत्त्वप्राप्तिः (कुञ्जीमूल्यरूपम्& प्रकरणसूची, std::vector<std::string> कुञ्जीसूचिः) {

    std::queue<std::string> कुञ्ज्यनुक्रमः;
    सूच्यनुक्रमपरिवर्तनम् (कुञ्जीसूचिः , कुञ्ज्यनुक्रमः);
    int क्रमः = 0;
    कुञ्जीमूल्यरूपम्* द्विरुक्तप्रकरणसूची = &प्रकरणसूची;
    while ((क्रमः < द्विरुक्तप्रकरणसूची->size()) && (कुञ्ज्यनुक्रमः.size() >1)) {
        if(शब्दपिण्डनक्शा* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    द्विरुक्तप्रकरणसूची = मूल्यम्.स्थानधारकः.get();
                    क्रमः = 0;
                    कुञ्ज्यनुक्रमः.pop();
                } else {
                    क्रमः++;
                }                
            }      
        } else {
            क्रमः++;
        }
    }
    while ( क्रमः < द्विरुक्तप्रकरणसूची->size() ) {
        if(शब्दशब्दनक्शा* आन्तरिकनक्शा = std::get_if<शब्दशब्दनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    return मूल्यम्;
                }
            }
        } else {
            क्रमः++;
        }
    }
    return "";
}

int अङ्कतत्त्वप्राप्तिः (कुञ्जीमूल्यरूपम्& प्रकरणसूची, std::vector<std::string> कुञ्जीसूचिः) {

    std::queue<std::string> कुञ्ज्यनुक्रमः;
    सूच्यनुक्रमपरिवर्तनम् (कुञ्जीसूचिः , कुञ्ज्यनुक्रमः);
    int क्रमः = 0;
    कुञ्जीमूल्यरूपम्* द्विरुक्तप्रकरणसूची = &प्रकरणसूची;
    while ((क्रमः < द्विरुक्तप्रकरणसूची->size()) && (कुञ्ज्यनुक्रमः.size() >1)) {
        if(शब्दपिण्डनक्शा* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    द्विरुक्तप्रकरणसूची = मूल्यम्.स्थानधारकः.get();
                    क्रमः = 0;
                    कुञ्ज्यनुक्रमः.pop();
                } else {
                    क्रमः++;
                }                
            }      
        } else {
            क्रमः++;
        }
    }
    while ( क्रमः < द्विरुक्तप्रकरणसूची->size() ) {
        if(शब्दाङ्कनक्शा* आन्तरिकनक्शा = std::get_if<शब्दाङ्कनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    return मूल्यम्;
                }
            }
        } else {
            क्रमः++;
        }
    }
    return -1;
}

bool कुञ्जीपरीक्षा (कुञ्जीमूल्यरूपम्& प्रकरणसूची, std::vector<std::string> कुञ्जीसूचिः) {

    std::queue<std::string> कुञ्ज्यनुक्रमः;
    सूच्यनुक्रमपरिवर्तनम् (कुञ्जीसूचिः , कुञ्ज्यनुक्रमः);
    int क्रमः = 0;
    कुञ्जीमूल्यरूपम्* द्विरुक्तप्रकरणसूची = &प्रकरणसूची;
    while ((क्रमः < द्विरुक्तप्रकरणसूची->size()) && (कुञ्ज्यनुक्रमः.size() >1)) {
        if(शब्दपिण्डनक्शा* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    द्विरुक्तप्रकरणसूची = मूल्यम्.स्थानधारकः.get();
                    क्रमः = 0;
                    कुञ्ज्यनुक्रमः.pop();
                } else {
                    क्रमः++;
                }                
            }      
        } else {
            क्रमः++;
        }
    }
    while ( क्रमः < द्विरुक्तप्रकरणसूची->size() ) {
        if(शब्दाङ्कनक्शा* आन्तरिकनक्शा = std::get_if<शब्दाङ्कनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    return true;
                }
            }
        } else if(शब्दशब्दनक्शा* आन्तरिकनक्शा = std::get_if<शब्दशब्दनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    return true;
                }
            }
        } else if(अङ्कसूचिनक्शा* आन्तरिकनक्शा = std::get_if<अङ्कसूचिनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    return true;
                }
            }
        } else if(शब्दसूचिनक्शा* आन्तरिकनक्शा = std::get_if<शब्दसूचिनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    return true;
                }
            }
        } else if(शब्दपिण्डनक्शा* आन्तरिकनक्शा = std::get_if<शब्दपिण्डनक्शा>(&(*द्विरुक्तप्रकरणसूची)[क्रमः])) {
            for (const auto& [कुञ्जी, मूल्यम्] : *आन्तरिकनक्शा) {
                if (कुञ्जी ==कुञ्ज्यनुक्रमः.front()) {
                    return true;
                }
            }
        } else {
            क्रमः++;
        }
    }
    return false;
}


void उद्धरणचिह्ननिष्कासनम्(std::string& न) {
    न.erase(std::remove(न.begin(), न.end(), '\"'), न.end());
}
//int main() {
//    कुञ्जीमूल्यरूपम् प्रकरणसूची;
//    std::ifstream सञ्चिका("sam_आन्तरिककुञ्जीमूल्यरूपम्/abc_tb.json");
//    मानचित्रपरिवर्तनम् ("sam_आन्तरिककुञ्जीमूल्यरूपम्/abc_tb.json",सञ्चिका,प्रकरणसूची);
//    सञ्चिका.close();
//    std::ofstream सञ्चिका_1("temp.json");
//    प्रवेशः ("temp.json",सञ्चिका_1,प्रकरणसूची);
//    सञ्चिका_1.close();
//
//    return 0;
//}