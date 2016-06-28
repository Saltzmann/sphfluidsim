#ifndef COMPUTESHADER_H
#define COMPUTESHADER_H

#include <memory>
#include <utility>
#include <QOpenGLShaderProgram>

class ComputeShader {
public:
    ComputeShader();
    ComputeShader(std::string computeShaderFilePath,
            std::string workItemsUniformName,
            std::vector<std::pair<std::string, std::string>> sourceVariables);
    void bind();
    void release();
    void setWorkItems(int items);
private:
    std::string loadShader(std::string fileName,
            std::vector<std::pair<std::string, std::string>> sourceVariables);
    std::unique_ptr<QOpenGLShaderProgram> shaderProgram;
    int getLocation(std::string uniformName);
    int workItemsUniform;
};

#endif // COMPUTESHADER_H
