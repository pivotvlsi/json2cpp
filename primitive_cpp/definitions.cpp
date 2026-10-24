#include <iostream>
#include <stdexcept>
#include <string> 
#include "definitions.h"
using namespace std;
int वर्तमानकालः = 0;

uint8_t wire::charToUInt(char c) {
    switch (c) {
        case '0': return STATE_0;
        case '1': return STATE_1;
        case 'x': case 'X': return STATE_X;
        case 'z': case 'Z': return STATE_Z;
        default: return STATE_X;
    }
}

char wire::uintToChar(uint8_t u) {
    switch (u) {
        case STATE_0: return '0';
        case STATE_1: return '1';
        case STATE_X: return 'x';
        case STATE_Z: return 'z';
        default: return 'x';
    }
}

wire::wire() : val(STATE_Z) {}
wire::wire(char c) : val(charToUInt(c)) {}
wire::wire(uint8_t u) : val(u & 3) {}
void wire::operator=(char a) {
    val = charToUInt(a);
}
void wire::operator=(uint8_t u) {
    val = u & 3;
}
char wire::getVal() {
    return uintToChar(val);
}
void wire::setVal(char a) {
    val = charToUInt(a);
}
uint8_t wire::getUInt() const {
    return val;
}
void wire::setUInt(uint8_t u) {
    val = u & 3;
}

//And deifinitions

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

char आद्यारम्भाङ्गम्_च (char a, char b) {
    if (a == '0' || b == '0') return '0';
    if (a == '1' && b == '1') return '1';
    return 'x';
}

char आद्यारम्भाङ्गम्_वा (char a, char b) {
    if (a == '1' || b == '1') return '1';
    if (a == '0' && b == '0') return '0';
    return 'x';
}

char आद्यारम्भाङ्गम्_न (char a) {
    if (a == '0') return '1';
    if (a == '1') return '0';
    return 'x';
}
