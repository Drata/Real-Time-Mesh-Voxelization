#include "model.h"

void Model::animate(bool animate)
{
	isAnimate = animate;
}

int Model::getFps() const
{
	return fps;
}

void Model::setFps(int fps)
{
	this->fps = fps;
}

float Model::getCurrentFrame() const
{
	return frame;
}

void Model::setCurrentFrame(float frame)
{
	this->frame = frame;
}

void Model::calculateAnimMatrices(float frame, const std::vector<Bone>& bones)
{
	// clears animation matrix vector
	animationMatVec->clear();

	// calculates matrix for all bones
	for (int i = 0; i < bones.size(); i++) {
		int parent = bones.at(i).getParentIndex();
		glm::mat4 currentMat;
		
		if (parent > -1) {
			currentMat = animationMatVec->at(parent) * bones.at(i).calculateAnimMatrix(frame);
		}
		else {
			currentMat = bones.at(i).calculateAnimMatrix(frame);
		}

		animationMatVec->push_back(currentMat);
	}

	// multiplies each matrix for inversed pose matrix
	for (int i = 0; i < animationMatVec->size(); i++) {
		animationMatVec->at(i) *= bones.at(i).getInvPoseMatrix();
	}
}

void Model::update(float deltaTime)
{
	if (isAnimate) {
		// sets actual frame
		frame += fps * deltaTime;

		// resets animation
		if (frame > m_mesh->getLastFrame()) {
			frame = 0;
		}
		else if (frame < 0) {
			frame = m_mesh->getLastFrame();
		}
	}

	// calculates animation matrix
	calculateAnimMatrices(frame, m_mesh->getBones());
}
