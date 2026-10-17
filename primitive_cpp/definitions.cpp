#include <iostream>
#include <stdexcept>
#include <string> 
#include "definitions.h"
using namespace std;

wire::wire() {
    wire::setVal('z');
}
void wire::operator=(char a) {
    wire::setVal(a);
}
char wire::getVal() {
        return val;
}
void wire::setVal(char a) {
        wire::validate(a);
        wire::val = a;
}

void wire::validate (char a) {
    switch(a) {
        case '0': return;
        case '1': return;
        case 'x': return;
        case 'z': return;
        default:  cout << "error in wire"; exit(1);
    }

}

//And deifitions

And::And (wire &c, wire &a, wire &b) {
    z = &c;
    x = &a;
    y = &b;
}
And::And() : z(nullptr), x(nullptr), y(nullptr) {

}
void And::eval() {
   And::calculate();
}
void And::create_connections(wire &c,wire &a,wire &b)   {
    z=&c;
    x=&a;
    y=&b;
}
void And::calculate() {
    And::validate();
    char a,b;
    a = And::x->getVal();
    b= And::y->getVal();
    if ( a=='1' && b == '1') {
       *z = '1';
    } else if ( (a=='0' && b == '1') || (a=='1' && b == '0') || (a=='0' && b == 'x') || (a=='x' && b == '0') || (a=='0' && b=='0')) {
       *z = '0';
    } else if (a=='z' || b=='z') {
       *z = 'z';
    } else {
       *z='x';
    }
    //cout << a <<" " <<b << " "<<And::z.getVal(); 
} 
void And::validate() {
    if (!(x && y && z)) {
        cout << "Error in AND gate" << endl;
        exit(1);
    }
}

//OR deifitions
Or::Or (wire &c, wire &a, wire &b) {
    z = &c;
    x = &a;
    y = &b;
}
Or::Or() : z(nullptr), x(nullptr), y(nullptr) {

}
void Or::eval() {
   Or::calculate();
}
void Or::create_connections(wire &c,wire &a,wire &b)   {
    z=&c;
    x=&a;
    y=&b;
}
void Or::calculate() {
    Or::validate();
    char a,b;
    a = Or::x->getVal();
    b= Or::y->getVal();
    if ( a=='0' && b == '0') {
       *z = '0';
    } else if ( (a=='0' && b == '1') || (a=='1' && b == '0') || (a=='1' && b == 'x') || (a=='x' && b == '1') || (a=='1' && b=='1')) {
       *z = '1';
    } else if (a=='z' || b=='z') {
       *z = 'z';
    } else {
       *z='x';
    }
    //cout << a <<" " <<b << " "<<And::z.getVal(); 
} 
void Or::validate() {
    if (!(x && y && z)) {
        cout << "Error in OR gate" << endl;
        exit(1);
    }
}

//Not deifitions
Not::Not (wire &c, wire &a) {
    z = &c;
    x = &a;

}
Not::Not() : z(nullptr), x(nullptr) {

}
void Not::eval() {
   Not::calculate();
}
void Not::create_connections(wire &c,wire &a)   {
    z=&c;
    x=&a;
}
void Not::calculate() {
    Not::validate();
    char a;
    a = Not::x->getVal();
    if ( a=='0') {
       *z = '1';
    } else if ( a=='1') {
       *z = '0';
    } else if (a=='z' ) {
       *z = 'z';
    } else {
       *z='x';
    }
    //cout << a <<" " <<b << " "<<And::z.getVal(); 
} 
void Not::validate() {
    if (!(x &&  z)) {
        cout << "Error in NOT gate" << endl;
        exit(1);
    } 

}

string दशमिकपरिवर्तकः (string पद) {
    bool has_x = false;
    int dec = 0;

    for (char c : पद) {
        if ( c == '1')
            dec = dec * 2 + (c - '0');
        else if (c=='0') {

        } else if (c == 'x' || c == 'X' || c=='z' || c=='Z') {
            has_x = true;
            //std::cout << "Warning: Binary contains 'x' (unknown bits)\n";
            break;
        } else {
            has_x = true;
            break;
            //std::cerr << "Invalid character: " << c << "\n";
            //return 1;
        }
    }

    if (has_x) {
        return std::string(1, 'X');
    } else {
        return std::to_string(dec);
    }
}


