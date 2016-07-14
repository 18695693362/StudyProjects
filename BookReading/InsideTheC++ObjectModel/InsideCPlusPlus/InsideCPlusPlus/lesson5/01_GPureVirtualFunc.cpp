//
//  GPureVirtualFunc.cpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/12/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#include "01_GPureVirtualFunc.h"
using namespace std;

GAbstract_base::GAbstract_base(char* mumble_value)
:_mumble(mumble_value)
{
}

GAbstract_base::~GAbstract_base()
{
}


GDerived::GDerived()
{
}

void GDerived::interface() const
{
}

#pragma mark - improve GAbstract_base version

GAbstract_baseEx::~GAbstract_baseEx()
{
}







