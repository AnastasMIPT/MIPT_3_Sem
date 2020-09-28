
#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H


#ifdef DEBUG
    #define DEB_INFO printf ("DEBUG_INFO:  Called from FILE: %s from FUNCTION: %s   LINE: %d\n", __FILE__, __func__, __LINE__);
#else 
    #define DEB_INFO ;
#endif

#endif // DEBUG_INFO_H