//
// Created by zjs on 18-5-9.
//

#ifndef ZJS_KEYVALUE_H
#define ZJS_KEYVALUE_H

#include <string>

using namespace std;

class KeyValue {
private:
    string key;
    string value;
public:
    string getValue() const {
        return value;
    }

    void setValue(string v) {
        value = v;
    }

    string getKey() const {
        return value;
    }

    void setKey(string v) {
        key = v;
    }
};

#endif //ZJS_KEYVALUE_H
