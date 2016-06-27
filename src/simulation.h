#ifndef SIMULATION_H
#define SIMULATION_H

#include <memory>
#include <QOpenGLBuffer>
#include <QVector4D>
#include <chrono>

#include "computeshader.h"

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;
using Time = std::chrono::duration<float>;

class Simulation {
public:
    Simulation();
    Simulation(int maxParticleCount,
            float domain_size_x, float domain_size_y, float domain_size_z);
    std::shared_ptr<QOpenGLBuffer> getPositionsBuffer();
    int getParticleCount();
    void simulate(Time time);
    // TODO add time point
    void addFluidCuboid(float maxPartShare,
            float pos_x, float pos_y, float pos_z,
            float size_x, float size_y, float size_z);
    void addFluidCube(float maxPartShare,
            float pos_x, float pos_y, float pos_z,
            float size);
    void init();
    float getMinDensity();
private:
    float domain_size_x = 0.0f;
    float domain_size_y = 0.0f;
    float domain_size_z = 0.0f;

    float minDensity = std::numeric_limits<float>::max();

    int maxParticleCount = 0;

    std::shared_ptr<QOpenGLBuffer> positionsBuffer = nullptr;
    QOpenGLBuffer velocitiesBuffer;
    QOpenGLBuffer partIndexBuffer;
    std::vector<QVector4D> startPositions;
    std::vector<QVector4D> startVelocities;
    std::vector<std::pair<GLint, GLint>> partIndex;
    ComputeShader voxelizeShader;
    void sync();
    std::string str(int i);
    std::string str(float f);
    template<typename T>
    void debugPrintBuffer(std::string name, std::shared_ptr<QOpenGLBuffer> buffer, int vec_size);
    template<typename T>
    void debugPrintBuffer(std::string name, QOpenGLBuffer buffer, int vec_size);
};

#endif // SIMULATION_H
