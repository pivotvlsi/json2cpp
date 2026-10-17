
#ifndef DEFINES
#define DEFINES
#include <string>
#include <initializer_list>

using namespace std;
class wire {
public:
    wire();
    wire (char c);
    void operator=(char a);
    char getVal();
    void setVal(char a);
private:
    char val;

    void validate (char a);
};

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
#endif
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



