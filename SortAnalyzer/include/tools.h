#ifndef TOOLS_H
#define TOOLS_H
#include "canvas.h"

namespace TOOLS {
    enum TOOL_ID {
        PENCIL,
        EREASER,
        BOX_BLUR,
        COLOR_FILTER,
        TOOLS_COUNT
    };
};

    
class AbstractTool {

public:
    virtual void startApplying (Canvas* canvas, double x, double y) = 0;
    virtual void apply (Canvas* canvas, double x, double y) = 0;
    virtual void finishApplying (Canvas* canvas, double x, double y) = 0;
    virtual ~AbstractTool () = default;
};


class Eraser : public AbstractTool {


public:

    Eraser () = default;
    void startApplying (Canvas* canvas, double x, double y) override {
        printf ("Я ластик, я начал применяться\n");
    }
    void apply (Canvas* canvas, double x, double y) override {
        printf ("Применяюсь по координатам x = %lf, y = %lf\n", x, y);
    }
    void finishApplying (Canvas* canvas, double x, double y) override {
        printf ("Я ластик, я закончил применяться\n");
    }
};

class Pencil : public AbstractTool {
    Point2d last_apply_coords = {-1, -1};

public:

    void startApplying (Canvas* canvas, double x, double y) override;
    void apply (Canvas* canvas, double x, double y) override;
    void finishApplying (Canvas* canvas, double x, double y) override;

};




#endif //TOOLS_H