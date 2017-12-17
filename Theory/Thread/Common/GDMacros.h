//
//  Macros.h
//  ThreadTutorial
//
//  Created by guodong on 4/2/14.
//  Copyright (c) 2014 guodong. All rights reserved.
//

#ifndef ThreadTutorial_GDMacros_h
#define ThreadTutorial_GDMacros_h

// namespace wolfand11 {}
#ifdef __cplusplus
#define NS_GD_BEGIN                     namespace wolfand11 {
#define NS_GD_END                       }
#define USING_NS_GD                     using namespace wolfand11
#else
#define NS_GD_BEGIN
#define NS_GD_END
#define USING_NS_GD
#endif

#endif
