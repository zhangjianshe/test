//
// Created by zjs on 18-5-9.
//

#ifndef ZJS_MESSAGE_H
#define ZJS_MESSAGE_H

#include <string>
#include <list>
#include <map>
#include "KeyValue.h"

using namespace std;

/*
 * {
  "type": "DEVICE_CONTROL_RESP",
  "sno": "999210",
  "did": "14223",
  "command": "set_bright_resp",
  "attribute": "light.bright",
  "data": [{
    "k": "code",
    "v": "0"
  }]
}
 */
class Message {

private:
    string type;
    string sno;
    string mac;
    string command;
    string attribute;
    map<string,string> data;
public:
    string getType() const {
        return type;
    }

    void setType(string t) {
        type = t;
    }

    string getSno() const {
        return sno;
    }

    void setSno(string t) {
        sno = t;
    }


    string getMac() const {
        return mac;
    }

    void setMac(string t) {
        mac = t;
    }

    string getCommand() const {
        return command;
    }

    void setCommand(string t) {
        command = t;
    }

    string getAttribute() const {
        return attribute;
    }

    std::map<string,string> getData() const {
        return data;
    }
    void setAttribute(string t) {
        attribute = t;
    }
    string toJSON() {
        string str;
        str.append("{");
        str.append("\"type\":\"").append(type).append("\"");
        str.append("\"mac\":\"").append(mac).append("\",");
        str.append("\"sno\":\"").append(sno).append("\",");
        str.append("\"command\":\"").append(command).append("\",");
        str.append("\"attribute\":\"").append(attribute).append("\"");
        str.append("}");
        return str;
    }
};

#endif //ZJS_MESSAGE_H
