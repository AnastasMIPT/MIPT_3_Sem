#ifndef CONFIG_H
#define CONFIG_H
#include "MyOpenGL.h"
#include "MySFML.h"
#include "window_size.h"

using GSystem = SFML;


using GEngine = Engine<GSystem>;

template<typename T>
extern T Engine<T>::system (WindowWidth, WindowHeight, "TextReader");

#endif // CONFIG_H