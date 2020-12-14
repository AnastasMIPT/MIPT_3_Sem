#ifndef CONFIG_H
#define CONFIG_H
#include "MyOpenGL.h"
#include "MySFML.h"
using GSystem = SFML;


using GEngine = Engine<GSystem>;


constexpr int WindowWidth = 1600;
constexpr int WindowHeight = 900;


template<typename T>
extern T Engine<T>::system (WindowWidth, WindowHeight, "TextReader");

#endif // CONFIG_H