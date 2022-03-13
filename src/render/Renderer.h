//
// Created by Bay Foley-Cox on 3/7/22.
//

#ifndef PATH_TRACER_RENDERER_H
#define PATH_TRACER_RENDERER_H


#include "../scene/Scene.h"

class Renderer {
public:
    Renderer(Scene *scene);

    void render(int num_threads, int num_samples, bool display, std::string filename);
private:
    Scene* scene;

};


#endif //PATH_TRACER_RENDERER_H
