//
//  TheaterSimulator.cpp
//  ThreadTutorial
//
//  Created by guodong on 4/2/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#include "TheaterSimulator.h"
using namespace std;

// 一共有10个检票口
vector<Gate> gates(10);

void ViewersArrival()
{
    default_random_engine random_engine{};
    normal_distribution<double> normal_distr(31,8);
    
    auto norm = bind(normal_distr,random_engine);
    vector<int> random_values(64);
    
    for (int  i=0; i<700; i++)
    {
        random_values[round(norm())];
    }
    
    int secs = 100;
    uniform_int_distribution<int> index{0,9};
    
    for (auto i : random_values)
    {
        cout << i << endl;
        for (auto j=1; j<=i; j++)
        {
            // 将观众添加到某个gate的队列中
            //(gates[index(random_engine)]).add(Viewer());
        }
    }
}

void RunTheaterSimulator()
{
    
}