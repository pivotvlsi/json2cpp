#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string>
#include <stack>
#include <regex>
#include <filesystem>
#include <locale>
#include <codecvt> 
#include <filesystem>
#include "../json2cpp_cpp/json2verif.h"
#include "../json2map_cpp/json2map.h"
using json = nlohmann::json;
using namespace std;

struct Node {
    string path;
    json value;
};

int main() {
    कुञ्जीमूल्यरूपम् प्रकरणसूची;
    std::filesystem::path प("sam_आन्तरिककुञ्जीमूल्यरूपम्");
    if (std::filesystem::exists(प) && std::filesystem::is_directory(प)) {
        for (const auto& प्रवेशः : std::filesystem::directory_iterator("sam_आन्तरिककुञ्जीमूल्यरूपम्")) {
            if (प्रवेशः.is_regular_file()) {
                
                std::string पङ्क्तिः;
                std::ifstream सञ्चिका(प्रवेशः.path());

                if (!सञ्चिका.is_open()) {
                    std::cerr << "Failed to open input JSON file "<< प्रवेशः.path().filename() <<" file\n";
                    exit(1);
                }
                मानचित्रपरिवर्तनम् (प्रवेशः.path().filename().string(),सञ्चिका,प्रकरणसूची);  
            } else {
                std::cerr << "Error in parsing\n" ; 
            }
        }
    } else {
        std::cerr << "No parsed files\n";
    }
    std::ofstream सञ्चिका_1("temp.json");
    
    
    कुञ्जीमूल्यरूपम्* एकघटकप्रकरणसूची;
    std::string घटकनाम;
    std::string पूर्णघटकः="";
    int क्रमः = 0;
    while (क्रमः < प्रकरणसूची.size()) {
        
        घटकनाम = घटकनामस्वीकरणम् (प्रकरणसूची, क्रमः);
        एकघटकप्रकरणसूची = घटकसूचकस्वीकरणम् (प्रकरणसूची, क्रमः);
        उद्धरणचिह्ननिष्कासनम्(घटकनाम);
        
        
        कार्यक्रमनिर्माणम्(*एकघटकप्रकरणसूची,घटकनाम, पूर्णघटकः);
        प्रवेशः (पूर्णघटकः, सञ्चिका_1 , प्रकरणसूची);
        क्रमः++;
        std::ofstream निर्गमसञ्चिका(घटकनाम + ".cpp");

        निर्गमसञ्चिका << पूर्णघटकः;
        निर्गमसञ्चिका.close();

    }
    //सञ्चिका_1 << पूर्णघटकः;
    //प्रवेशः (पूर्णघटकः, सञ्चिका_1 , प्रकरणसूची);
    
    सञ्चिका_1.close();


}

int start () {
    std::ofstream file_trial("trial");

    bool comma_first_var;
    int statement_order =0;
    // Parse JSON
    json j;
    json port;

    json in_out;
    vector<string> statement_arr;
    // Make an empty array
    in_out["port"] = json::array();
    in_out["wire"] = json::array();
    in_out["arrayed_wire"] = json::array();
    in_out["arrayed_wire_length"] = json::array();
    // Access values
    string module_name = j.begin().key();
    std::ofstream नामसञ्चिका("all_functions.txt");
    नामसञ्चिका.close();
    // Open design C file
    string file_name = module_name +".h";
    string constructor_def;
    string constructor_def1;
    string constructor_def2;
    string constructor_def3;
    string wire_def;
    string wire_def_init;
    std::ofstream file_o(file_name);
//FILE* pipe = popen("g++ -x c++ - -o /dev/shm/exec", "w");
//fprintf(pipe, "int main() { ... }");
//pclose(pipe);
//system("/dev/shm/exec");
    if (!file_o.is_open()) {
        std::cerr << "Failed to open file to write translated module to C";
    }
    file_o << "#include \"primitive_cpp/definitions.h\"\n";
    file_o << "#include<iostream>\n";
    file_o << "using namespace std;\n";
    file_o << "class " << module_name << "{" << endl;
    file_o << "\tpublic:\n";
    constructor_def =  "\t"+module_name +"() {\n";
    constructor_def = constructor_def + "\t\tint* i_arr;\n";
    constructor_def = constructor_def + "\t\tint* j_arr;\n";
    //Copy all the ports into anaother json for expression forming
    for (auto& [key,val] : j[module_name].items()) {
        if (j[module_name][key].contains("प्रकारः")) {
            if ( j[module_name][key]["प्रकारः"] == "तारः")  {
                port[key] = j[module_name][key];
            }
        }
    }
    // iterate over the object at j[module_name]
    for (auto& [key, val] : j[module_name].items()) {
        if (j[module_name][key].contains("प्रकारः")) {
            if ( j[module_name][key]["प्रकारः"] == "तारः") {
                
                if (j[module_name][key]["अवगाढता"].get<int>() == 0 ) {
                    
                    file_o << "\twire " << key << ";" << endl;
                    constructor_def = constructor_def + "\t\t" +key+ "=\'x\';\n";
                } else {
                    //constructor_def = "\t\twire " +key;
                    constructor_def = constructor_def + "\t\ti_arr = new int[" +std::to_string( j[module_name][key]["अवगाढता"].get<int>()+1) + "];\n";
                    constructor_def = constructor_def + "\t\tj_arr = new int[" +std::to_string( j[module_name][key]["अवगाढता"].get<int>()+1) + "];\n";
                    constructor_def1 = "";
                    file_o << "\twire "+key ;
                    constructor_def2 = "\t\t\t"+key;
                    constructor_def3 = "\t\t";
                    
                    
                    for (int अस्थायि=1; अस्थायि <= j[module_name][key]["अवगाढता"].get<int>() ; अस्थायि++) {
                        constructor_def1 = constructor_def1 + "\t\tfor(j_arr[" + std::to_string(अस्थायि) + "]=0; j_arr[" + std::to_string(अस्थायि) + "] <= i_arr[" + std::to_string(अस्थायि) + "]; j_arr[" + std::to_string(अस्थायि) + "]++ ) {\n";
                        constructor_def2 = constructor_def2 +"[j_arr[" + std::to_string(अस्थायि) +"]]";
                        constructor_def3 = constructor_def3 + "\n\t\t}\n\t\t";
                        string अस्थायि_1 = std::to_string(अस्थायि)+"_अन्त्यसूचकः";
                        file_o << "[" <<  std::stoi(j[module_name][key][अस्थायि_1].get<string>()) <<"]";
                        constructor_def = constructor_def + "\t\ti_arr[" + std::to_string(अस्थायि) + "] = " + std::to_string(std::stoi(j[module_name][key][अस्थायि_1].get<string>())) + ";\n";
                        

                    }
                    file_o << ";\n";
                    constructor_def = constructor_def + constructor_def1 + constructor_def2 + "=\'x\';\n" +constructor_def3;
                    constructor_def = constructor_def + "\tdelete[] i_arr;\n\t\tdelete[] j_arr;\n";
                    

                }
                
            } else if (j[module_name][key]["प्रकारः"] == "द्वारम्") {
                file_o << "\twire *" << key << ";" << endl;
                in_out["port"].push_back(key);
            }
           

        }
    }
    file_o << constructor_def;
    

    
    for (int i=0; i< in_out["port"].size(); i++) {
        if (!comma_first_var) {
            file_o <<",";
        }
        file_o  <<in_out["port"][i].get<std::string>()  ;
        comma_first_var = false;
    }

    
    for (int i=0; i< in_out["wire"].size(); i++) {
        
        file_o  <<"\t\t"<<in_out["wire"][i].get<std::string>() << "='x';\n"  ;
        
    }
    for (int i=0; i < in_out["arrayed_wire"].size(); i++) {
        for (int j=0; j < in_out["arrayed_wire_length"][i]; j++) {
            file_o  <<"\t\t"<<in_out["arrayed_wire"][i].get<std::string>() << "[" << j << "]='x';\n"  ;
        }
    }
    
    file_o << "\t}\n";
    file_o.close();

    for (auto& [key, val] : j[module_name].items()) {

        if (j[module_name][key].contains("प्रकारः")) {
            
            if ( j[module_name][key]["प्रकारः"] == "आद्यारम्भाङ्गम्") {
                
                int statement_order;
                if ( j[module_name][key].contains("क्रमः")) {
                    statement_order = j[module_name][key]["क्रमः"];
                    //update_initial_begin_block (j[module_name][key],statement_order,module_name,key,port);
                } else {
                    cout << "Missing order in initial loop";
                    exit(1);
                }
               
            } else if ( j[module_name][key]["प्रकारः"] == "सदाङ्गम्") {
                
                int statement_order;
                if ( j[module_name][key].contains("क्रमः")) {
                    statement_order = j[module_name][key]["क्रमः"];
                    //update_always_begin_block (j[module_name][key],statement_order,module_name,key,port);
                } else {
                    cout << "Missing order in always loop";
                    exit(1);
                }
               
            }
           

        }
    }
    // Open design C file
    file_o.open(file_name, std::ios::app);
    if (!file_o.is_open()) {
        std::cerr << "Failed to open file to write translated module to C";
    }
    file_o << "\n};\n";
    file_o.close();
    file_trial.close();
    std::ofstream मूलसञ्चिका("main.cpp", std::ios::app);
    if (!मूलसञ्चिका.is_open()) {
        std::cerr << "Failed to open file to write translated module to C";
    }
    //मूलसञ्चिका <<
    return 0;
}



string get_correct_key (json j, unsigned long statement_order) {
    string key1 = "";
    
    for (auto& [key, val] : j.items()) {
        regex re("^\\d+_");
        if (regex_search(key,re)) {
            if (j.contains(key)) {
                if (j[key].contains("क्रमः")) {
                    if (j[key]["क्रमः"] == statement_order) {
                        key1 = key;
                        break;
                    } 
                }
            }
        }
    } 

    return key1;
   
}