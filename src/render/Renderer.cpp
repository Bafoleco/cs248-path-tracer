//
// Created by Bay Foley-Cox on 3/7/22.
//

#include "Renderer.h"
#include "../util.h"
#include "PathIntegrator.h"
#include <opencv2/opencv.hpp>
#include <thread>

void renderThread(cv::Mat* image, Scene* scene, int num_rows, int num_cols, int thread_num,
                  int num_threads, int num_samples) {

    Camera camera = scene->getCamera();

    for (int i = 0; i < num_rows; i++) {
        if (thread_num == 0 && i % 10 == 0) {
            printf("completed: %f\n", (double) i / num_rows);
        }
        if (i % num_threads == thread_num) {
            for (int j = 0; j < num_cols; j++) {
                Color color(0, 0, 0);
                for(int s = 0; s < num_samples; s++) {
                    //TODO jitter ray
                    Ray r(camera.getPos(), camera.getPixelDir(j + rand_double(), i + rand_double()));
                    color += PathIntegrator::sample(scene, r);
                }
                cv::Vec3b rgb = rgbFromColor(color / num_samples);
                image->at<cv::Vec3b>(i,j) = rgb;
            }
        }
    }

}

void Renderer::render(int num_threads, int num_samples, bool display, std::string filename) {

    auto start = std::chrono::high_resolution_clock::now();
    Camera camera = scene->getCamera();

    int num_cols = camera.getNumCols();
    int num_rows = camera.getNumRows();
    cv::Mat image(num_rows, num_cols, CV_8UC3);

    std::vector<std::thread*> threads;
    for (int i = 0; i < num_threads; i++) {
        auto* thread = new std::thread(renderThread, &image, scene, num_rows, num_cols, i, num_threads, num_samples);
        threads.push_back(thread);
    }

    for (int i = 0; i < num_threads; i++) {
        threads[i]->join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::seconds>(end - start);
    std::cout << duration.count() << std::endl;


    printf("writing to file: %s\n", filename.c_str());
    imwrite(filename, image);

    if (display) {
        namedWindow("render output",cv::WINDOW_AUTOSIZE);
        cv::imshow("render output", image);
        cv::waitKey(0);
        cv::destroyWindow("render output");
    }
}

Renderer::Renderer(Scene *scene) : scene(scene) {}
