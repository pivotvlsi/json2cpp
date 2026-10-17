#include <iostream>
#include <stdexcept>
#include <string> 
#include <vector>
//#include "definitions.h"

std::vector<std::string> simplify_expr (std::vector<std::string> y) {
    for (size_t i=0; i<y.size()-1; ++i) {
        for (size_t j=i; j<y.size(); j++) {
            
        }

    }
    return y;   
}

int main () {
    std::vector<std::string> a = {"AB","aB"};
    std::vector<std::string> y = simplify_expr(a);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << "\n";
    }
}