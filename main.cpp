#include <iostream>
#include <sstream>
#include <string>
#include "ScriptEngine.h"
using namespace std;

string temp()
{
    string temp("str\0is a byte charts",21);
    return temp;
}

int main() {


    ScriptEngine engine;
    engine.test();
    return 0;
}