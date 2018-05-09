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

#include "LuaBridge/LuaBridge.h"
#include "ScriptBuffer.h"

/*
 * 腳本解釋引擎
 */
class ScriptEngine {
private:
    lua_State *L;
public:
    /*
     * 注册ScriptBuffer class for lua to use
     */
    void registerBufferClass() {
        using namespace luabridge;
        getGlobalNamespace(L)
                .beginNamespace("zm")
                .beginClass<ScriptBuffer>("ScriptBuffer")
                .addConstructor < void(*)(void) > ()
                .addFunction("append", &ScriptBuffer::append)
                .addFunction("get", &ScriptBuffer::get)
                .addFunction("set", &ScriptBuffer::set)
                .addFunction("size", &ScriptBuffer::size)
                .addFunction("length", &ScriptBuffer::length)
                .addFunction("resize", &ScriptBuffer::resize)
                .addFunction("writeInt16", &ScriptBuffer::writeInt16)
                .addFunction("writeInt32", &ScriptBuffer::writeInt32)
                .addFunction("readInt16", &ScriptBuffer::readInt16)
                .addFunction("readInt32", &ScriptBuffer::readInt32)
                .addFunction("moveTo", &ScriptBuffer::moveTo)
                .addFunction("writeString", &ScriptBuffer::writeString)
                .endClass()
                .endNamespace();
    }

    ScriptEngine() {
        L = luaL_newstate();
        luaL_openlibs(L);
        registerBufferClass();
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
    void encode(std::string script, const char *pBuffer, int bufferSize, ScriptBuffer *pTarget) {
        int error = luaL_loadbuffer(L, script.c_str(), script.length(), "endecode") || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));    // 从栈顶取出错误信息打印。
        }
        lua_getglobal(L, "ziroom_encode");
        luabridge::push(L, pBuffer);
        luabridge::push(L, pTarget);
        error = lua_pcall(L, 2, 0, 0);
    }


    std::string readTextFile(const char *fileName) {
        std::ifstream t(fileName);
        std::stringstream buffer;
        buffer << t.rdbuf();
        std::string contents(buffer.str());
        return contents;
    }

    void test() {
        std::string script = readTextFile("/home/zjs/CLionProjects/test/driver.lua");
        std::string jsonData = readTextFile("/home/zjs/CLionProjects/test/data.json");

        int size = 0;
        ScriptBuffer target;
        encode(script, jsonData.data(), jsonData.length(), &target);
        printf("\nresult from call %d\n", target.length());
        printf("hex data:%s\n", target.toHex().c_str());
        printf("ASCII:%s", target.toASCII().c_str());
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
};


#endif //ZJS_SCRIPTENGINE_H
