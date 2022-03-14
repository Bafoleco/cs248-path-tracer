#include "examples/TestScenes.h"



void anim1() {
    int num = 0;
    std::string base = "anim1/frame_";
    double centerY = 0.4;
    for(double lr = 0.4; lr > 0; lr -= 0.01) {
        TestScenes::classicScene(lr, base + std::to_string(num) + ".jpg", 200, centerY - lr);
        num++;
    }
}

int main() {

//    TestScenes::classicScene();
//    TestScenes::testFresnel();
//    TestScenes::testFresnelCornell();
//    TestScenes::testSpecular();

    TestScenes::classicSceneAndFresnel(50);

//    anim1();

//    TestScenes::testSpecular(500);
//    TestScenes::testExtraSpecular(300);
//    TestScenes::bigSmall(100);


    return 0;
}
