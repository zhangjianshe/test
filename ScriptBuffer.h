//
// Created by zjs on 18-5-9.
//

#ifndef ZJS_SCRIPTBUFFER_H
#define ZJS_SCRIPTBUFFER_H

#include <stdio.h>
#include <cstring>
#include <string>

class ScriptBuffer {
private:
    unsigned char *pData;
    int mSize = 0;
    int current = 0;
    int tail = 0;
public:
    ScriptBuffer() {
        pData = NULL;
        resize(256);
    }

    ScriptBuffer(int size) {
        pData = NULL;
        resize(size);
    }

    ~ScriptBuffer() {
        if (pData != NULL) {
            delete pData;
            pData = NULL;
        }
    }

    int moveTo(int index) {
        if (index >= 0 && index < tail) {
            current = index;
            return current;
        }
        return -1;
    }

    unsigned char next() {
        if (current >= 0 && current < tail) {
            unsigned char b = get(current);
            if (current < tail) {
                current++;
            }
            return b;
        }
        return 0;
    }

    /*
     * 写2个字节
     */
    int readInt16() {

        int byte0 = next();
        int byte1 = next();

        printf("read %d %d", byte0, byte1);

        int b = (byte0 << 8 & 0xFF00);
        b = b | (byte1 & 0x00FF);
        return b;
    }


    /*
    * 写4个字节
    */
    int readInt32() {

        unsigned char byte0 = next();
        unsigned char byte1 = next();
        unsigned char byte2 = next();
        unsigned char byte3 = next();

        int b = (byte0 << 24) & 0xFF000000;
        b = b | ((byte1 << 16) & 0x00FF0000);
        b = b | ((byte2 << 8) & 0x0000FF00);
        b = b | (byte3 & 0xFF);
        return b;
    }

    /*
     * 写2个字符
     */
    void writeInt16(int data) {
        unsigned char byte;
        byte = (unsigned char) (data >> 8) & 0xFF;
        append(byte);
        byte = (unsigned char) data & 0xFF;
        append(byte);
    }

    void writeInt32(int data) {
        unsigned char byte;
        byte = (unsigned char) (data >> 24) && 0xFF;
        append(byte);
        byte = (unsigned char) (data >> 16) && 0xFF;
        append(byte);
        byte = (unsigned char) (data >> 8) && 0xFF;
        append(byte);
        byte = (unsigned char) data && 0xFF;
        append(byte);
    }

    void writeString(const char *str) {
        if (str != NULL) {
            unsigned const char *p = reinterpret_cast<const unsigned char *>(str);
            while (*p != 0) {
                append(*p);
                p++;
            }
        } else {
            printf("error write String with NULL");
        }

    }

    int resize(int size) {
        if (size <= 0) {
            return 0;
        }
        if (size <= mSize) {
            if (tail >= size) {
                tail = size - 1;
            }
            if (current >= size) {
                current = size - 1;
            }
            return size;
        } else {
            if (pData != 0) {
                char *pNew = new char[size];
                memcpy(pNew, pData, size);
                mSize = size;
                delete pData;
                pData = reinterpret_cast<unsigned char *>(pNew);
            } else {
                pData = new unsigned char[size];
                memset(pData, 0, mSize);
                mSize = size;
            }
        }
    }

    void set(int index, unsigned char data) {
        if (index >= 0 && index < mSize) {
            pData[index] = data;
        }
    }

    void append(unsigned char data) {
        if (tail >= mSize) {
            if (mSize == 0) {
                mSize = 128;
            }
            resize(mSize * 2);
        }
        pData[tail++] = data;
    }

    int size() {
        return mSize;
    }

    int length() {
        return tail;
    }

    unsigned char get(int index) {
        if (index >= 0 && index < mSize) {
            return pData[index];
        }
        return 0;
    }

    unsigned char *data() {
        return pData;
    }

    std::string toHex() {
        std::string r;

        for (int i = 0; i < length(); i++) {
            char temp[4];
            temp[3] = 0;
            sprintf(temp, "%02X ", get(i));
            r.append(temp);
        }
        return r;
    }

    std::string toASCII() {
        std::string r;
        for (int i = 0; i < length(); i++) {
            char temp[4];

            unsigned char c = get(i);
            if ((c >= 0x00 && c <= 0x19) || c == 0x7F) {
                temp[3] = 0;
                sprintf(temp, "%02X ", get(i));
                r.append(temp);
            } else {
                temp[1] = 0;
                sprintf(temp, "%c", c);
                r.append(temp);
            }

        }
        return r;
    }
};

#endif //ZJS_SCRIPTBUFFER_H
