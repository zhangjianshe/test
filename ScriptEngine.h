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
#include "Message.h"

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
    void registerClass() {
        using namespace luabridge;
        getGlobalNamespace(L)
                .beginNamespace("zm")
                .beginClass<ScriptBuffer>("ScriptBuffer")
                .addConstructor < void(*)
        (void) > ()
                .addProperty<int>("length", &ScriptBuffer::getLength)
                .addFunction("append", &ScriptBuffer::append)
                .addFunction("get", &ScriptBuffer::get)
                .addFunction("set", &ScriptBuffer::set)
                .addFunction("size", &ScriptBuffer::size)
                .addFunction("resize", &ScriptBuffer::resize)
                .addFunction("writeInt16", &ScriptBuffer::writeInt16)
                .addFunction("writeInt32", &ScriptBuffer::writeInt32)
                .addFunction("writeInt8", &ScriptBuffer::writeInt8)
                .addFunction("readInt16", &ScriptBuffer::readInt16)
                .addFunction("readInt32", &ScriptBuffer::readInt32)
                .addFunction("readInt8", &ScriptBuffer::readInt8)
                .addFunction("setInt8", &ScriptBuffer::setInt8)
                .addFunction("setInt16", &ScriptBuffer::setInt16)
                .addFunction("setInt32", &ScriptBuffer::setInt32)
                .addFunction("moveTo", &ScriptBuffer::moveTo)
                .addFunction("writeString", &ScriptBuffer::writeString)

                .endClass()
                .beginClass<Message>("Message")
                .addProperty<string>("type", &Message::getType, &Message::setType)
                .addProperty<string>("sno", &Message::getSno, &Message::setSno)
                .addProperty<string>("command", &Message::getCommand, &Message::setCommand)
                .addProperty<string>("attribute", &Message::getAttribute, &Message::setAttribute)
                .addProperty<string>("mac", &Message::getMac, &Message::setMac)
                 .addProperty<std::map<string,string>>("data", &Message::getData)
                .addFunction("toJSON", &Message::toJSON)
                .endClass()
                         .beginClass<KeyValue>("KeyValue")
                         .addProperty<string>("key", &KeyValue::getKey, &KeyValue::setKey)
                         .addProperty<string>("value", &KeyValue::getValue, &KeyValue::setValue)
                         .endClass()
                .endNamespace();
    }

    ScriptEngine() {
        L = luaL_newstate();
        luaL_openlibs(L);
        registerClass();
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
    void encode(std::string script, Message *pSource, ScriptBuffer *pTarget) {
        int error = luaL_loadbuffer(L, script.c_str(), script.length(), "endecode") || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));    // 从栈顶取出错误信息打印。
        }
        lua_getglobal(L, "ziroom_encode");
        luabridge::push(L, pSource);
        luabridge::push(L, pTarget);
        error = lua_pcall(L, 2, 0, 0);
    }

};


#endif //ZJS_SCRIPTENGINE_H
