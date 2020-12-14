#ifndef TOOLS_H
#define TOOLS_H
#include "canvas.h"

namespace TOOLS {
    enum TOOL_ID {
        PENCIL,
        EREASER,
        TOOLS_COUNT
    };
};


class AbstractTool {

public:
    virtual void startApplying () = 0;
    virtual void apply (Canvas* canvas, double x, double y) = 0;
    virtual void finishApplying () = 0;
    ~AbstractTool ();
};

class Eraser : AbstractTool {

public:
    void startApplying ();
    void apply (Canvas* canvas, double x, double y);
    void finishApplying ();
};

class Pecil : Eraser {

};

#endif //TOOLS_H