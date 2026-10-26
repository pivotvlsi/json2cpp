
#ifndef DEFINES
#define DEFINES
#include <string>
#include <initializer_list>


using namespace std;
extern int वर्तमानकालः;
#include <cstdint>

enum wire_state : uint8_t {
    STATE_0 = 0,
    STATE_1 = 1,
    STATE_X = 2,
    STATE_Z = 3
};

class wire {
public:
    wire();
    wire (char c);
    wire (uint8_t u);
    void operator=(char a);
    void operator=(uint8_t u);
    char getVal();
    void setVal(char a);
    uint8_t getUInt() const;
    void setUInt(uint8_t u);
private:
    uint8_t val;
    static uint8_t charToUInt(char c);
    static char uintToChar(uint8_t u);
};
#include "dpi/dpi.h"
//And deifitions
class And {
public:
    And (wire &c, wire &a, wire &b);
    And();
    void eval() ;
    void create_connections(wire &c,wire &a,wire &b);
private:
   wire *z,*x,*y;

   void calculate();
   void validate();
};

//Or deifitions
class Or {
public:
    Or (wire &c, wire &a, wire &b);
    Or();
    void eval() ;
    void create_connections(wire &c,wire &a,wire &b);
private:
   wire *z,*x,*y;

   void calculate();
   void validate();
};

//Not deifitions
class Not {
public:
    Not (wire &c, wire &a);
    Not();
    void eval() ;
    void create_connections(wire &c,wire &a);
private:
   wire *z,*x;

   void calculate();
   void validate();
};

typedef struct {
    string तार्किकाङ्गम्;
    int उधारयति;
} निर्गमनिर्माणम्;

char आद्यारम्भाङ्गम्_तार्किकसमतापरीक्षणम् (string , string );
char आद्यारम्भाङ्गम्_तार्किककनिष्ठात्परीक्षणम् (string , string );
char  आद्यारम्भाङ्गम्_तार्किकज्यायान्परीक्षणम् (string , string );
char आद्यारम्भाङ्गम्_तार्किककनिष्ठसमपरीक्षणम् (string , string );
char आद्यारम्भाङ्गम्_तार्किकज्यायान्समपरीक्षणम् (string , string );
char आद्यारम्भाङ्गम्_वा (char , char );
char आद्यारम्भाङ्गम्_च (char , char );
char आद्यारम्भाङ्गम्_न (char );
string आद्यारम्भाङ्गम्_अधिकबिन्दु_वा (string , string );
string आद्यारम्भाङ्गम्_अधिकबिन्दु_च (string , string );
string आद्यारम्भाङ्गम्_अधिकबिन्दु_न (string);
string आद्यारम्भाङ्गम्_द्विबिन्दुयोजनम् (string, string);
string आद्यारम्भाङ्गम्_द्विबिन्द्वपकर्षणम् (string, string);

//class तार्किकसामान्यपरीक्षणम् {
//    private:
//    string अस्थायी;
//    public:
//    तार्किकसामान्यपरीक्षणम्(string प्रथमतर्काङ्ग, string द्वितीयतर्काङ्ग);
//    string निष्पादयतु();
//}
string दशमिकपरिवर्तकः (string) ;
char आद्यारम्भाङ्गम्_द्विनियोजनम् (initializer_list<wire*>, string);
char आद्यारम्भाङ्गम्_द्विनियोजनम् (initializer_list<wire*>, long long);
char आद्यारम्भाङ्गम्_द्विनियोजनम् (initializer_list<wire*>, wire*, int);
char आद्यारम्भाङ्गम्_द्विनियोजनम्(wire& , const wire& );
char आद्यारम्भाङ्गम्_द्विनियोजनम्_सूचकम् (initializer_list<wire*> , wire* , int , int );
char आद्यारम्भाङ्गम्_द्विनियोजनम्_लक्ष्यसूचकम् (wire* , int , int , string );
int सूचकमूल्यम्(wire* , int );
char आद्यारम्भाङ्गम्_द्विनियोजनम्_लक्ष्यसूचकम् (wire& , int , int , string );
char आद्यारम्भाङ्गम्_द्विनियोजनम्_उभयसूचकम् (wire& , int , int , wire& , int , int );

#endif