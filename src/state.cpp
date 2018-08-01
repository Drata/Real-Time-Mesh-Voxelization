#include "state.h"

std::shared_ptr<Shader>	State::defaultShader;
glm::mat4 				State::projectionMatrix;
glm::mat4 				State::viewMatrix;
glm::mat4 				State::modelMatrix;

std::vector<std::shared_ptr<Light>> State::lights;
glm::vec3 State::ambient;

bool State::animation = false;
std::shared_ptr<std::vector<glm::mat4>> State::animMatrices;