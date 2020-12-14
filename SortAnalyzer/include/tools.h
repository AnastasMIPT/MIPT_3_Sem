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
    virtual ~AbstractTool () = default;
};

class Eraser : public AbstractTool {


public:

    Eraser () = default;
    void startApplying () override {}
    void apply (Canvas* canvas, double x, double y) override {}
    void finishApplying () override {}
};

class Pencil : public Eraser {

public:

    void startApplying () override {}
    void apply (Canvas* canvas, double x, double y) override {}
    void finishApplying () override {}

};

#endif //TOOLS_H