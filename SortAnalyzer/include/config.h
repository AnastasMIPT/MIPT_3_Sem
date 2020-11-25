#ifndef CONFIG_H
#define CONFIG_H
#include "MyOpenGL.h"
#include "MySFML.h"
using GSystem = OpenGL;


using GEngine = Engine<GSystem>;

template<typename T >
extern T Engine<T>::system (600, 675, "TextReader");

#endif // CONFIG_H