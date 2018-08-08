#include "../lib/glew/glew.h"
#include "common.h"
#include "state.h"

bool init() {
	// init glew
	if ( glewInit() ) {
		return false;
	}

	// init states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	// create default shader
	State::defaultShader = Shader::create(readString("data/voxelize.vert"), readString("data/voxelize.frag"), readString("data/voxelize.geom"));
 	if (!State::defaultShader) return false;

	return true;
}
