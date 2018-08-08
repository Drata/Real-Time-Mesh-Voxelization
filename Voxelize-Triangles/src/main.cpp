#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "../include/util.h"
#include "../include/Shader.h"
#include "../include/Buffer.h"
#include "../include/common.h"
#include "../include/State.h"
#include "../include/Mesh.h"
#include "../include/Entity.h"
#include "../include/Model.h"
#include "../include/Camera.h"
#include "../include/World.h"
#include <vector>

#define FULLSCREEN false

std::vector<Vertex> vertices = {
	// coords
	Vertex(0,  1, 0),
	Vertex(-1, -1, 0),
 	Vertex(1, -1, 0)
};

World world;

std::vector<uint16_t> indices = {0, 1, 2};

int main(int, char**) {
	if ( glfwInit() != GLFW_TRUE ) {
		std::cout << "could not initalize glfw" << std::endl;
		return -1;
	}
	atexit(glfwTerminate);

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Voxelize Triangles", FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!window) {
		std::cout << "could not create glfw window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!init()) {
		std::cout << "could not initialize glew" << std::endl;
	}

	// read shaders and store it in State
	std::string vertexShader = readString("data/shader.vert");
	std::string fragmentShader = readString("data/shader.frag");
	std::string geometryShader = readString("data/voxelize.geom");
	if (vertexShader == "" || fragmentShader == "" || geometryShader == "") {
		std::cout << "could not load shaders" << std::endl;
		return -1;
	}

	const char* vertexShaderC = vertexShader.c_str();
	const char* fragmentShaderC = fragmentShader.c_str();
	const char* geometryShaderC = geometryShader.c_str();

	State::defaultShader = Shader::create(vertexShaderC, fragmentShaderC, geometryShaderC);

	if (State::defaultShader == nullptr) {
		std::cout << "Couldn't create shader." << std::endl;
		return -1;
	}

	//Create camera
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();

	//Setes properties of the camera
	camera->setPosition(glm::vec3(0, 0, 6));
	camera->setClearColor(glm::vec3(0, 0, 0));

	//Adds the camera to the world
	world.addEntity(camera);

	//Adds models to the world
	std::shared_ptr<Buffer> buffer = Buffer::create(vertices, indices);

	std::shared_ptr<Mesh> triMesh = std::make_shared<Mesh>();
	triMesh->addBuffer(buffer);

	glm::vec3 scale(1.0f, 1.0f, 1.0f);
	glm::vec3 rotation(0.0f, 0.0f, 0.0f);

	for (int x = -3; x <= 3; x += 3) {
		for (int z = 0; z >= -6; z -= 3) {
			std::shared_ptr<Model> triangle = std::make_shared<Model>(triMesh);
			triangle->setScale(scale);
			triangle->setRotation(rotation);
			triangle->setPosition(glm::vec3((float)x, 0.0f, (float)z));

			world.addEntity(triangle);
		}
	}

	glm::vec3 axis(0.0f, 1.0f, 0.0f);
	glm::quat quaternion = glm::angleAxis(glm::radians(32.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	//Main loop
	float lastTime = static_cast<float>(glfwGetTime());
	while ( !glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) ) {
		// update delta time
		float newTime = static_cast<float>(glfwGetTime());
		float deltaTime = newTime - lastTime;
		lastTime = newTime;

		// get updated screen size
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);

		camera->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));

		//Calculate mvp matrix
		glm::mat4 projection = glm::perspective((float) glm::radians(60.0f), (float) screenWidth / (float)screenHeight, (float) 0.1f, (float) 1000.0f);
		camera->setProjection(projection);

		//Updates world's objects
		for (int i = 0; i < world.getNumEntities(); i++) {
			std::shared_ptr<Entity> entity = world.getEntity(i);

			//Checks if it's a model.
			std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(entity);

			if (model != nullptr) {

				//Gets current rotation.
				glm::quat rotationQuaternion = model->getRotationQuat();

				//Creates new quaternion.
				model->setRotation(glm::slerp(rotationQuaternion, quaternion * rotationQuaternion, deltaTime));
			}
		}

		//Draws 
		world.update(deltaTime);
		world.draw();

		// update swap chain & process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}