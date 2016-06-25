#ifndef PARTICLES_H
#define PARTICLES_H

#include "resourcemanager.h"
#include <QOpenGLBuffer>
#include "shaderprogram.h"
#include <QVector3D>
#include <QMatrix4x4>
#include <chrono>
#include <QOpenGLFunctions_4_3_Core>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;
using Time = std::chrono::duration<float>;

class Particles {
public:
    Particles();
    Particles(std::string filePath);
    void render(ShaderProgram* program, QMatrix4x4 vpMatrix,
            std::shared_ptr<QOpenGLFunctions_4_3_Core> funcs);

private:
    struct ParticlesData {
        ParticlesData();
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        QOpenGLBuffer vbo;
        QOpenGLBuffer ibo;

        void loadData(std::string filePath);
        void initVBO();
        void initIBO();
    };

    typedef std::shared_ptr<ParticlesData> sharedParticles;
    sharedParticles ptr;
    std::vector<QVector3D> positions;
    QOpenGLBuffer positionsBuffer;
    QVector3D basePosition;
    float scale;

    class ParticlesManager : public ResourceManager<ParticlesData, ParticlesManager> {
    friend ResourceManager<ParticlesData, ParticlesManager>;
    private:
        static sharedParticles loadResource(std::string filePath);
    };
};

#endif // PARTICLES_H