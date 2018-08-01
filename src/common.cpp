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
	glEnable(GL_BLEND);
	// create default shader
	State::defaultShader = Shader::create(readString("data/default.vert"), readString("data/default.frag"), readString("data/default.geom"));
 	if (!State::defaultShader) return false;

	return true;
}
