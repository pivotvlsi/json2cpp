

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

using namespace std;

using शब्दाङ्कनक्शा = std::unordered_map<std::string, int>;
using शब्दशब्दनक्शा = std::unordered_map<std::string, std::string>;
using अङ्कसूची = std::vector<int>;
using शब्दसूची = std::vector<std::string>;
using अङ्कसूचिनक्शा = std::unordered_map<std::string,अङ्कसूची>;
using शब्दसूचिनक्शा = std::unordered_map<std::string,शब्दसूची>;
using अन्तर्हितसूची = std::vector<std::variant<अङ्कसूची,शब्दसूची>>;
using शब्दान्तर्हितसूचीनक्शा = std::unordered_map<std::string,अन्तर्हितसूची>;

struct पिण्डः;

using शब्दपिण्डनक्शा = std::unordered_map<std::string,पिण्डः>;
using बहुरूप = std::variant<शब्दाङ्कनक्शा, शब्दशब्दनक्शा, अङ्कसूचिनक्शा, शब्दसूचिनक्शा, शब्दपिण्डनक्शा, शब्दान्तर्हितसूचीनक्शा>;
using कुञ्जीमूल्यरूपम् = std::vector<std::variant<शब्दाङ्कनक्शा, शब्दशब्दनक्शा, अङ्कसूचिनक्शा, शब्दसूचिनक्शा, शब्दपिण्डनक्शा, शब्दान्तर्हितसूचीनक्शा>>;
#ifndef JSON2MAP
#define JSON2MAP
struct पिण्डः {
    std::shared_ptr<कुञ्जीमूल्यरूपम्> स्थानधारकः;
};
#endif
template <typename क>
void स्तूपानुक्रमपरिवर्तनम् (std::stack<क> , std::queue<क>& );
कुञ्जीमूल्यरूपम्* सूचकपर्यन्तसञ्चरणम् (std::stack<int> , कुञ्जीमूल्यरूपम्&  );
void मानचित्रपरिवर्तनम् (std::string , std::ifstream& , कुञ्जीमूल्यरूपम्& );
void प्रवेशः (std::string , std::ofstream& , कुञ्जीमूल्यरूपम्& );
std::string घटकनामस्वीकरणम् (कुञ्जीमूल्यरूपम् ,  int );
कुञ्जीमूल्यरूपम्* घटकसूचकस्वीकरणम् (कुञ्जीमूल्यरूपम् ,  int );
template <typename क>
void सूच्यनुक्रमपरिवर्तनम् (std::vector<क>& , std::queue<क>& );
std::string शब्दतत्त्वप्राप्तिः (कुञ्जीमूल्यरूपम्& , std::vector<std::string> ) ;
int अङ्कतत्त्वप्राप्तिः (कुञ्जीमूल्यरूपम्& , std::vector<std::string> ) ;
bool कुञ्जीपरीक्षा (कुञ्जीमूल्यरूपम्& , std::vector<std::string> ) ;
void उद्धरणचिह्ननिष्कासनम्(std::string& );