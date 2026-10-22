#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // (Read all recorded initial begin block functions)
    vector<string> घटकसूची;
    ifstream घटकसञ्चिका("module_name.txt");
    if (!घटकसञ्चिका.is_open()) {
        cerr << "Error: cannot open module_name.txt\n";
        return 1;
    }
    string घटकनाम;
    while (getline(घटकसञ्चिका, घटकनाम)) {
        while (!घटकनाम.empty() && (घटकनाम.back() == '\r' || घटकनाम.back() == ' ' || घटकनाम.back() == '\t')) {
            घटकनाम.pop_back();
        }
        if (!घटकनाम.empty()) {
            घटकसूची.push_back(घटकनाम);
        }
    }
    घटकसञ्चिका.close();
    if (घटकसूची.empty()) {
        cerr << "Error: module_name.txt is empty\n";
        return 1;
    }
    // 2. Read all functions
    vector<string> फलनसूची;
    ifstream फलनसञ्चिका("all_functions.txt");
    if (!फलनसञ्चिका.is_open()) {
        cerr << "Error: cannot open all_functions.txt\n";
        return 1;
    }

    string पङ्क्तिः;
    while (getline(फलनसञ्चिका, पङ्क्तिः)) {
        // Remove trailing spaces and carriage return (\r\n)
        while (!पङ्क्तिः.empty() && (पङ्क्तिः.back() == '\r' || पङ्क्तिः.back() == ' ' || पङ्क्तिः.back() == '\t')) {
            पङ्क्तिः.pop_back();
        }
        if (!पङ्क्तिः.empty()) {
            फलनसूची.push_back(पङ्क्तिः);
        }
    }
    फलनसञ्चिका.close();

    if (फलनसूची.empty()) {
        cerr << "Error: all_functions.txt is empty\n";
        return 1;
    } 



    // -------------------------------------------------------------
    // चरणम् २: main.cpp सञ्चिकानिर्माणम्
    // (Generate top-level simulation harness)
    // -------------------------------------------------------------
    ofstream मूलसञ्चिका("main.cpp");
    if (!मूलसञ्चिका.is_open()) {
        cerr << "Error: cannot open main.cpp\n";
        return 1;
    }
    for (const auto& घटक : घटकसूची) {
        मूलसञ्चिका << "#include \"" << घटक << ".cpp\"\n";
    }
    मूलसञ्चिका << "#include \"primitive_cpp/definitions.h\"\n";
    मूलसञ्चिका << "#include <iostream>\n\n";
    मूलसञ्चिका << "using namespace std;\n\n";
    मूलसञ्चिका << "int main() {\n";
    for (const auto& घटक : घटकसूची) {
        मूलसञ्चिका << "\t" << घटक << " inst_" << घटक << ";\n";
    }
    मूलसञ्चिका << "\tint वर्तमानकालः = 0;\n";

    मूलसञ्चिका << "\twhile (1) {\n";
    // 2. Call each function
    for (const auto& फलननाम : फलनसूची) {
        for (const auto& घटक : घटकसूची) {
            if (फलननाम.rfind(घटक, 0) == 0) {
                मूलसञ्चिका << "\t\tinst_" << घटक << "." << फलननाम << "();\n";
                break;
            }
        }
    }
    मूलसञ्चिका << "\t\tवर्तमानकालः++;\n";
    मूलसञ्चिका << "\t}\n";
    मूलसञ्चिका << "\treturn 0;\n";
    मूलसञ्चिका << "}\n";
    मूलसञ्चिका.close();

    return 0;
}
