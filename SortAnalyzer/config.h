#ifndef CONFIG_H
#define CONFIG_H
#include "MyOpenGL.h"
using GSystem = OpenGL;


using GEngine = Engine<GSystem>;

template<typename T >
extern T Engine<T>::system (1200, 675, "TextReader");

#endif // CONFIG_H