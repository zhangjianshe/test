//
// Created by zjs on 18-5-9.
//

#ifndef ZJS_MESSAGE_H
#define ZJS_MESSAGE_H

#include <string>
#include <list>
#include <map>
#include <vector>
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
    vector<KeyValue> data;
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

    string getData(string key) const {
        for (int i = 0; i <data.size() ; ++i) {
            KeyValue kv=data[i];
            if(kv.getKey()==key)
            {
                return kv.getValue();
            }
        }
        return string("");
    }

    void setData(string key,string value) {
        bool  find= false;
        for (int i = 0; i <data.size() ; ++i) {
            KeyValue kv=data[i];
            if(kv.getKey()==key)
            {
                kv.setValue(value);
                find=true;
                break;
            }
        }
        KeyValue kv;
        kv.setKey(key);
        kv.setValue(value);
        data.push_back(kv);
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
        str.append("\"attribute\":\"").append(attribute).append("\",");
        str.append("\"data:\"[");
        int first = 0;
        for (int i=0;i<data.size();i++) {
            if (first > 0) {
                str.append(",");
            }
            KeyValue kv=data[i];
            str.append("{\"k\":\"").append(kv.getKey()).append("\",\"v\":\"").append(kv.getValue()).append("\"}");
            first++;
        }
        str.append("]");
        str.append("}");
        return str;
    }
};

#endif //ZJS_MESSAGE_H
