//
// Created by zjs on 18-5-8.
//

#ifndef ZJS_SCRIPTENGINE_H
#define ZJS_SCRIPTENGINE_H

#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <lua.hpp>

/*
 * 腳本解釋引擎
 */
class ScriptEngine {
private:
    lua_State *L;
public:
    ScriptEngine() {
        L = luaL_newstate();
        luaL_openlibs(L);

    }

    ~ScriptEngine() {
        if (L != NULL) {
            lua_close(L);
        }
    }

    /**
     * 调用lua脚本 进行编码，返回编码后的数据
     * @param script
     * @param pData
     * @return
     */
     std::stringstream  encode(std::string script, char *pData,int* pSize) {
        int error = luaL_loadbuffer(L, script.c_str(), script.length(), "endecode") || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));    // 从栈顶取出错误信息打印。
            return std::stringstream();
        }
        lua_getglobal(L, "ziroom_encode");
        lua_pushstring(L, pData);
        error = lua_pcall(L, 1, 1, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));    // 从栈顶取出错误信息打印。
            pSize=0;
            return std::stringstream();
        } else {

            unsigned char * pData= lua_tostring(L, -1);
            std::stringstream data;
        }
    }


    std::string readTextFile(const char *fileName) {
        std::ifstream t(fileName);
        std::stringstream buffer;
        buffer << t.rdbuf();
        std::string contents(buffer.str());
        return contents;
    }

    void test() {

        std::string script=readTextFile("/home/zjs/CLionProjects/test/driver.lua");
        std::string jsonData=readTextFile("/home/zjs/CLionProjects/test/data.json");
        std::cout<<script;
        std::cout<<jsonData;
    }
};


#endif //ZJS_SCRIPTENGINE_H
