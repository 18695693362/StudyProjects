//
//  GHelper.hpp
//  InsideCPlusPlus
//
//  Created by Guo Dong on 7/9/16.
//  Copyright © 2016 Guo Dong. All rights reserved.
//

#ifndef GHelper_hpp
#define GHelper_hpp

#include <iostream>
#include <string>
#include <array>
#include <utility>
#include <iomanip>
#include <sstream>
#include <chrono>
class GCodeTimer
{
public:
    static GCodeTimer& GetInstance();
    typedef std::chrono::high_resolution_clock Clock;
    typedef Clock::time_point TimePoint;
    
    GCodeTimer(const char* name="UnKnown")
    :pre_record_time_(Clock::now())
    ,name_(name)
    {}
    
    void Record(const char* info);
    void Reset();

private:
    std::string name_;
    TimePoint pre_record_time_;
};

class GHelper
{
public:
    static void PrintLocalTime();
    
    template<typename R, typename T, typename... Args>
    static std::string MemberFuncToString(R (T::*func)(Args...))
    {
        union PtrUnion
        {
            R(T::*f)(Args...);
            std::array<unsigned char, sizeof(func)> buf;
        };
        PtrUnion u;
        u.f = func;
        
        std::ostringstream os;
        
        os << std::hex << std::setfill('0');
        for (auto c : u.buf)
            os << std::setw(2) << (unsigned)c;
        
        return os.str();
    }
};

#endif /* GHelper_hpp */
