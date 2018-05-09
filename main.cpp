#include <iostream>
#include <sstream>
#include <string>
#include "ScriptEngine.h"
using namespace std;

std::string readTextFile(const char *fileName) {
    std::ifstream t(fileName);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string contents(buffer.str());
    return contents;
}



void pln(const char *pData) {
    std::cout << pData << std::endl;
}


void printLuaStack(lua_State *lua) {

    pln("========= content of stack from top to bottom: ===========");

    int stackSize = lua_gettop(lua);                    // 获得栈中元素个数
    for (int i = stackSize; i > 0; --i) {
        printf("%d [%d]\t", i, -1 - (stackSize - i));
        int t = lua_type(lua, i);                       // 判断当前元素类型
        switch (t) {
            case LUA_TNUMBER:
                printf("%s: \t%.2f\n", lua_typename(lua, t), lua_tonumber(lua, i));     // 打印类型名称和值
                break;
            case LUA_TBOOLEAN:
                printf("%s: \t%d\n", lua_typename(lua, t), lua_toboolean(lua, i));
                break;
            case LUA_TSTRING:
                printf("%s: \t%s\n", lua_typename(lua, t), lua_tostring(lua, i));
                break;
            default:
                // LUA_TTABLE
                // LUA_TTHREAD
                // LUA_TFUNCTION
                // LUA_TLIGHTUSERDATA
                // LUA_TUSERDATA
                // LUA_TNIL
                printf("%s\n", lua_typename(lua, t));                                   // 不好打印的类型，暂时仅打印类型名称
                break;
        }
    }
    printf("stack szie:%d\n", stackSize);
}

int main() {


    ScriptEngine engine;

    std::string script = readTextFile("/home/zjs/CLionProjects/test/driver.lua");
    std::string jsonData = readTextFile("/home/zjs/CLionProjects/test/data.json");

    ScriptBuffer target;
    Message msg;
    msg.setData("age","123");
    msg.setType("zjs is le");
    engine.encode(script, &msg, &target);

    printf("source:%s\n", msg.toJSON().c_str());
    printf("target:%s\n", target.toHex().c_str());


    return 0;
}


