
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <regex>
#include <filesystem>
#include <locale>
#include <codecvt> 
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <variant>
#include <queue>
#include "json.hpp"
#include "../json2map_cpp/json2map.h"
using json = nlohmann::json;

using namespace std;

string get_correct_key(json,unsigned long);
void update_initial_begin_block (json, unsigned long,string,string,json );
void update_always_begin_block (json , unsigned long , string , string ,json );
unsigned long update_initial_if_block (json, string, unsigned long, unsigned long, unsigned long ,string, std::ofstream &, json &);
unsigned long update_initial_elseif_block (json, string, unsigned long, unsigned long, unsigned long, unsigned long ,string, std::ofstream &, json &);
unsigned long update_initial_elseonly_block (json, string, unsigned long, unsigned long, unsigned long, unsigned long ,string, std::ofstream &, json &);
std::string toBinary(string, int);
std::string आद्याङ्गपरिक्षाप्रकटम् (std::vector<std::string> ) ;
std::string सदारम्भवाक्यम् (std::vector<std::string> , json , std::string ) ;
std::string सदारम्भाङ्गोपाधानम् (std::string , json );
std::string सदारम्भाङ्गोपाधानम्_नियोजनम् (std::string , json, std::string );
bool onlySpaces(const std::string& ) ;
std::string आद्यारम्भाङ्गोपाधानम् (std::string , json ) ;
std::string आद्यारम्भाङ्गोपाधानम्_नियोजनम् (std::string , json, std::string ) ;
std::string दशमाननिर्गमः (std::string ) ;
bool is_operator (const std::string& );
std::unordered_map<std::string,int>  precedence_array() ;
std::string join_with(const std::vector<std::string>& , const std::string& );
std::vector<std::string> split_by_space(const std::string& );
void कार्यक्रमनिर्माणम् (कुञ्जीमूल्यरूपम्& , std::string&, std::string& );
void प्रारम्भकफलनम् (std::string& ,कुञ्जीमूल्यरूपम्&, std::string& );
void आद्यारम्भाङ्गखण्डपरिचयः (std::string&  ,कुञ्जीमूल्यरूपम्& , std::string&, std::string& );
void आद्यारम्भाङ्गफलनम् (std::string&  ,कुञ्जीमूल्यरूपम्& , std::string , std::string, std::string&, unsigned long , कुञ्जीमूल्यरूपम्& );
void आद्यारम्भाङ्गक्रमसंग्रहफलनम् (कुञ्जीमूल्यरूपम्& ,std::unordered_map<int,int>&);
void आद्याङ्गवाक्यम्(कुञ्जीमूल्यरूपम्& , std::string&, unsigned long& ,  std::string& , int, std::string&, कुञ्जीमूल्यरूपम्&,const  std::string&  );
void विलम्बफलनम्(कुञ्जीमूल्यरूपम्& , int& );
void यद्यङ्गफलनम्(कुञ्जीमूल्यरूपम्& ,std::string& , std::string , std::string , std::vector<शब्दशब्दनक्शा>& ,int& , int );
void अन्यथायद्यङ्गफलनम्(कुञ्जीमूल्यरूपम्& ,std::string& , std::string , std::string , std::vector<शब्दशब्दनक्शा>& ,int& , int );
void अन्यथाङ्गफलनम्(कुञ्जीमूल्यरूपम्& ,std::string& , std::string , std::string , std::vector<शब्दशब्दनक्शा>& ,int& , int );
void मूलघटकक्रमनिर्माणम् (कुञ्जीमूल्यरूपम्&);
std::string शब्दतत्त्वप्राप्तिः (कुञ्जीमूल्यरूपम्&, std::string);
void पश्चव्यञ्जकरूपान्तरणम् (std::string& ,std::string& );
void आद्यारम्भाङ्गपश्चव्यञ्जकरूपान्तरणम् (std::string& ,std::string&, कुञ्जीमूल्यरूपम्&, unsigned long& ,  std::string& , int, std::string&,const std::string& );
void सदारम्भाङ्गखण्डपरिचयः (कुञ्जीमूल्यरूपम्&  );
void सदारम्भाङ्गफलनम् (कुञ्जीमूल्यरूपम्& , कुञ्जीमूल्यरूपम्&, std::string );
std::vector<std::string> सदारम्भचरस्वीकरणम् ( कुञ्जीमूल्यरूपम्&);
std::string नियुक्तचरस्वीकरणम् (std::string);
void चरपुनरावृत्तिनिवारणम् (std::vector<std::string>&);
void अनिष्टवाक्यनिर्मूलनम्(कुञ्जीमूल्यरूपम्& , std::string );
bool अङ्गसूचकपरीक्षणम् (const std::string& , std::string& , int& , int& );
std::string सर्वचरग्रहणम् (std::string );
std::string आश्रितचरग्रहणम् (कुञ्जीमूल्यरूपम्& ) ;
void आश्रितचरमुद्रणम् (कुञ्जीमूल्यरूपम्& , std::string );
bool तारपरीक्षणम् (const std::string& , कुञ्जीमूल्यरूपम्& ) ;
bool पूर्णाङ्कपरीक्षणम् (const std::string& );
bool अनावृतपरीक्षणम् (const std::string&     , कुञ्जीमूल्यरूपम्& );
bool सापेक्षितसूचकपरीक्षणम् (const std::string& , std::string& , std::string& , std::string& , कुञ्जीमूल्यरूपम्& );
