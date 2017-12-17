//
//  BruteForceCoding.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 3/6/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <stdint.h>
#include <string>
#include <iostream>
#include "BruteForceCoding.h"
#include "GUtility.h"

#define BUFFSIZE 100
#define MESSAGELENGTH 100

using namespace std;

static char str_buff[BUFFSIZE];

char* BytesToDecString(uint8_t* byte_arr, int arr_len)
{
    char* p_strbuff = str_buff;
    size_t buff_space_left = BUFFSIZE;
    for (int i=0; i<arr_len&&buff_space_left>0; i++)
    {
        int strl = snprintf(p_strbuff, buff_space_left, "%u ", byte_arr[i]);
        buff_space_left -= strl;
        p_strbuff += strl;
    }
    return str_buff;
}

int EncodeIntBigEndian(uint8_t dst[], uint64_t val, int offset, int size)
{
    if (size<0 || size>8)
    {
        GUtility::DieWithUserMessage("EncodeIntBigEndian() size error");
    }
    for (int i=0; i<size; i++)
    {
        dst[offset++] = (uint8_t) (val >> ((size - 1) - i) * CHAR_BIT);
    }
    return offset;
}

uint64_t DecodeIntBigEndian(uint8_t val[], int offset, int size)
{
    uint64_t rtn = 0;
    for (int i=0; i<size; i++)
    {
        rtn = (rtn << CHAR_BIT) | val[offset+i];
    }
    return rtn;
}

void RunCodingAndEncoding()
{
    int msg_len = sizeof(uint8_t)+sizeof(uint16_t)+sizeof(uint32_t)+sizeof(uint64_t);
    uint8_t msg[msg_len];
    
    const uint8_t val8      = 101;
    const uint16_t val16    = 10001;
    const uint32_t val32    = 100000001;
    const uint64_t val64    = 1000000000001L;
    printf("raw 1-byte integer = %u\n", (unsigned char)val8);
    printf("raw 2-byte integer = %u\n", (unsigned int)val16);
    printf("raw 4-byte integer = %u\n", (unsigned int)val32);
    printf("raw 8-byte integer = %llu\n", val64);
    
    int offset = 0;
    offset = EncodeIntBigEndian(msg, val8,  offset, sizeof(uint8_t));
    offset = EncodeIntBigEndian(msg, val16, offset, sizeof(uint16_t));
    offset = EncodeIntBigEndian(msg, val32, offset, sizeof(uint32_t));
    offset = EncodeIntBigEndian(msg, val64, offset, sizeof(uint64_t));
    
    printf("Encoded message:\n%s\n",BytesToDecString(msg, msg_len));
    uint64_t value = DecodeIntBigEndian(msg, 0,sizeof(uint8_t));
    //printf("Decoded 1-byte integer = %u\n", (unsigned char)value);
    cout << "Decoded 1-byte integer = " << value << endl;
    value = DecodeIntBigEndian(msg, sizeof(uint8_t), sizeof(uint16_t));
    //printf("Decoded 2-byte integer = %u\n", (unsigned int)value);
    cout << "Decoded 2-byte integer = " << value << endl;
    value = DecodeIntBigEndian(msg, sizeof(uint8_t)+sizeof(uint16_t)+sizeof(uint32_t),sizeof(uint64_t));
    //printf("Decoded 8-byte integer = %llu\n", value);
    cout << "Decoded 8-byte integer = " << value << endl;
}

void Test04_TestCodingAndEncoding(bool is_run)
{
    if (!is_run) {
        return;
    }
    
    RunCodingAndEncoding();
}