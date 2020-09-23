#ifndef DEBUG_ASSERT_H
#define DEBUG_ASSERT_H


#ifdef DEBUG_ASSERT
#define Assert(arg) assert (arg)
#else 
#define Assert(arg)  
#endif


#endif // DEBUG_ASSERT_H
