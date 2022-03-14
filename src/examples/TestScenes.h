//
// Created by Bay Foley-Cox on 3/10/22.
//

#ifndef PATH_TRACER_TESTSCENES_H
#define PATH_TRACER_TESTSCENES_H


#include "../scene/Scene.h"

class TestScenes {

public:
    static void testSpecular(int num_samples);

    static void testTransmission();

    static void testFresnel();

    static void testFresnelCornell();

    static void classicScene(double lr, std::string filename, int num_samples, double yOff);

    static void classicSceneHard(std::string filename, int num_samples);

    static void helloWorld(int num_samples);

    static void bigSmall(int num_samples);

    static void testExtraSpecular(int num_samples);

    static void testFresnel2();

    static void classicSceneAndFresnel(int num_samples);
};

#endif //PATH_TRACER_TESTSCENES_H