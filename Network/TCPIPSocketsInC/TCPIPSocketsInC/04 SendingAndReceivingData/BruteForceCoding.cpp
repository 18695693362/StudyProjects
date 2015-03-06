//
//  BruteForceCoding.cpp
//  TCPIPSocketsInC
//
//  Created by guodong on 3/6/15.
//  Copyright (c) 2015 guodong. All rights reserved.
//
#include <stdint.h>

#include "BruteForceCoding.h"

#define BUFFSIZE 100
#define CHAR_BIT sizeof(char)
#define MESSAGELENGTH 100

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
    for (int i=0; i<size; i++)
    {
        dst[offset++] = (uint8_t)(val >> ((size-1)-i)*CHAR_BIT);
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
    const uint32_t val32    = 100010001;
    const uint64_t val64    = 1000000000001L;
    
    int offset = 0;
    offset = EncodeIntBigEndian(msg, val8, offset, sizeof(uint8_t));
    offset = EncodeIntBigEndian(msg, val16, offset, sizeof(uint16_t));
    offset = EncodeIntBigEndian(msg, val32, offset, sizeof(uint32_t));
    offset = EncodeIntBigEndian(msg, val64, offset, sizeof(uint64_t));
    
    printf("Encoded message:\n%s\n",BytesToDecString(msg, msg_len));
    uint64_t value = DecodeIntBigEndian(msg, 0,sizeof(uint8_t));
    printf("Decoded 1-byte integer = %u\n", (unsigned char)value);
    value = DecodeIntBigEndian(msg, sizeof(uint8_t), sizeof(uint16_t));
    printf("Decoded 2-byte integer = %u\n", (unsigned int)value);
    value = DecodeIntBigEndian(msg, sizeof(uint8_t)+sizeof(uint16_t)+sizeof(uint32_t),sizeof(uint64_t));
    printf("Decoded 8-byte integer = %llu\n", value);
}

void Test04_TestCodingAndEncoding(bool is_run)
{
    if (!is_run) {
        return;
    }
    
    RunCodingAndEncoding();
}