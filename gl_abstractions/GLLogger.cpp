#include "GLLogger.hpp"


void GLClearError() {

	while (glGetError() != GL_NO_ERROR);	//clear all the error flags

}

bool GLLogError(const char* function, const char* file, int line) {

	while (GLenum error = glGetError()) {
		std::cout << "[Error]:\t " << error << "\n" <<
			function << " " << file << ": " << "On line number: " << line << std::endl;
		return false;
	}
	return true;
}