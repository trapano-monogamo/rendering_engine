#include "my_utils.hpp"

void unbind_all()
{
	 glUseProgram(0);
	 glBindVertexArray(0);
	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
