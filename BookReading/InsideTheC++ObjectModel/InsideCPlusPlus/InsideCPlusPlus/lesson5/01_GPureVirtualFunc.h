//
//  GPureVirtualFunc_1.hpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/12/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#ifndef GPureVirtualFunc_1_hpp
#define GPureVirtualFunc_1_hpp

#include <iostream>

class GAbstract_base
{
public:
    GAbstract_base(char* mumble_value=0);
    virtual ~GAbstract_base() = 0;
    virtual void interface() const = 0;
    virtual const char* mumble() const { return _mumble; }
    
protected:
    char* _mumble;
};

class GDerived:public GAbstract_base
{
public:
    GDerived();
    virtual void interface() const;
};


#pragma mark - improve GAbstract_base version

class GAbstract_baseEx
{
public:
    GAbstract_baseEx(char* mumble_value=0);
    virtual ~GAbstract_baseEx() = 0;
    virtual void interface() = 0;
    const char* mumble() const { return _mumble; }
    
protected:
    char* _mumble;
};


#endif /* GPureVirtualFunc_1_hpp */
