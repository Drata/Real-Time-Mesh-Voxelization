// #ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#endif

#include "../lib/glew/glew.h"
#include "../lib/glfw3/glfw3.h"
#include "engine.h"
#include <iostream>

#define FULLSCREEN false

GLFWwindow* window;

struct BoxData {
	float rotationSpeed;

	BoxData(float rotationSpeed = 32) : rotationSpeed(rotationSpeed) {}

	static void update(std::shared_ptr<Entity> entity, float deltaTime) {
		std::shared_ptr<BoxData> data = std::static_pointer_cast<BoxData>(entity->getUserData());
		entity->setEuler(glm::vec3(0, entity->getEuler().y + data->rotationSpeed * deltaTime, 0));
	}
};

void updateCamera(std::shared_ptr<Entity> entity, float dt) {
	std::shared_ptr<Camera> cam = std::static_pointer_cast<Camera>(entity);

	if (glfwGetKey(window, GLFW_KEY_W)) {
		cam->move(glm::vec3(0.0f, 0.0f, -1.0f) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		cam->move(glm::vec3(-1.0f, 0.0f, 0.0f) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		cam->move(glm::vec3(0.0f, 0.0f, 1.0f) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		cam->move(glm::vec3(1.0f, 0.0f, 0.0f) * dt);
	}

	glm::ivec4 vp = cam->getViewport() / 2;
	glm::vec2 vpcenter = { vp.z, vp.w };

	double x = 0, y = 0;

	glfwGetCursorPos(window, &x, &y);
	glm::vec2 mouse(x, y);
	mouse = (vpcenter - mouse) / vpcenter;

	glm::quat quadX = glm::rotate(glm::quat(), mouse.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat quadY = glm::rotate(glm::quat(), mouse.y, glm::vec3(1.0f, 0.0f, 0.0f));
	//cam->setQuat(quadX * quadY);
}

int main(int, char**) {
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "could not initalize glfw" << std::endl;
		return -1;
	}
	atexit(glfwTerminate);

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(800, 600, "U-gine", FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!window) {
		std::cout << "could not create glfw window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	// init engine
	if (!init()) {
		std::cout << "could not initialize engine" << std::endl;
		return -1;
	}

	// create world
	World world;

	// loads dwarf mesh
	std::shared_ptr<Mesh> dwarfMesh = Mesh::load("data/dwarf.msh.xml");
	std::shared_ptr<Model> dwarfModel = std::make_shared<Model>(dwarfMesh);

	// adds tottem
	dwarfModel->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
	dwarfModel->animate(true);
	dwarfModel->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	dwarfModel->setFps(16);
	dwarfMesh->getMaterial(0).setLightning(false);
	dwarfMesh->getMaterial(1).setLightning(false);
	dwarfMesh->getMaterial(0).setDepthWrite(true);
	dwarfMesh->getMaterial(1).setDepthWrite(true);
	world.addEntity(dwarfModel);

	// adds ambient
	world.setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));

	// create camera
	std::shared_ptr<Camera> cam = std::make_shared<Camera>();
	cam->setEuler(glm::vec3(0.0f, 0.0f, 0.0f));
	cam->setPosition(glm::vec3(0.0f, 2.0f, 8.0f));
	cam->setClearColor(glm::vec3(0.0f, 0.0f, 0.0f));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// sets update callback
	cam->setUpdateCallback(updateCamera);

	world.addEntity(cam);

	float lastTime = static_cast<float>(glfwGetTime());
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// update delta time
		float newTime = static_cast<float>(glfwGetTime());
		float deltaTime = newTime - lastTime;
		lastTime = newTime;

		// get updated screen size
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);

		// update camera projection & viewport
		cam->setProjection(glm::perspective<float>(glm::radians(45.0f), static_cast<float>(screenWidth) / screenHeight, 0.001f, 100));
		cam->setViewport(glm::ivec4(0, 0, screenWidth, screenHeight));

		// update & draw world
		world.update(deltaTime);
		world.draw();

		// update swap chain & process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}