#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 640, "Lab1.2", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	glewInit();


	float vertices[] = {
		-0.50f,  0.00f, 0.0f, //0
		-0.75f, -0.50f, 0.0f, //1
		-0.25f, -0.50f, 0.0f, //2

		 0.25f, -0.50f, 0.0f, //3
		 0.75f, -0.50f, 0.0f, //4
		 0.50f,  0.00f, 0.0f  //5
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		3, 4, 5
	};

	GLuint verticesBuffer = NULL;
	glGenBuffers(1, &verticesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao = NULL;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);

	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vertex_position;"
		"uniform mat4 translation;"
		"uniform mat4 scale;"
		"uniform mat4 rotation;"
		"void main() {"
		"    gl_Position = translation * scale * rotation * vec4(vertex_position, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"    frag_colour = vec4(0.0, 1.0, 1.0, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	//checkShaderStatus(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	//checkShaderStatus(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);

	glBindAttribLocation(shader_programme, 0, "vertex_position");

	glLinkProgram(shader_programme);

	int translation_loc = glGetUniformLocation(shader_programme, "translation");
	assert(translation_loc > -1);
	int rotation_loc = glGetUniformLocation(shader_programme, "rotation");
	assert(rotation_loc > -1);
	int scale_loc = glGetUniformLocation(shader_programme, "scale");
	assert(scale_loc > -1);

	float translation[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float rotation[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float rotation2[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float scale[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	float rotate_x = 1.0f, rotate_y = 1.0f, rotate_z = 1.0f;

	while (!glfwWindowShouldClose(window)) {

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
			translation[12] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
			translation[12] -= 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
			translation[13] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
			translation[13] -= 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_PERIOD)) {
			translation[14] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_COMMA)) {
			translation[14] -= 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_EQUAL)) {
			scale[0] += 0.001f;
			scale[5] += 0.001f;
			scale[10] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_MINUS)) {
			scale[0] -= 0.001f;
			scale[5] -= 0.001f;
			scale[10] -= 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)) {
			scale[0] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_B)) {
			scale[5] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_C)) {
			scale[10] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)) {
			scale[0] -= 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E)) {
			scale[5] -= 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_F)) {
			scale[10] += 0.001f;
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_X)) {
			float x_angle = acos(rotation[5]);

			if (x_angle >= 3.12) {
				rotate_x = -1.0f;
			}
			else if (x_angle <= 0) {
				rotate_x = 1.0f;
			}

			rotation[5] = cos(0.00281359 * rotate_x + x_angle);
			rotation[7] = sin(0.00281359 * rotate_x + x_angle);
			rotation[9] = -sin(0.00281359 * rotate_x + x_angle);
			rotation[10] = cos(0.00281359 * rotate_x + x_angle);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Y)) {
			float y_angle = acos(rotation[0]);

			if (y_angle >= 3.12) {
				rotate_y = -1.0f;
			}
			else if (y_angle <= 0) {
				rotate_y = 1.0f;
			}

			rotation[0] = cos(0.00281359 * rotate_y + y_angle);
			rotation[8] = sin(0.00281359 * rotate_y + y_angle);
			rotation[3] = -sin(0.00281359 * rotate_y + y_angle);
			rotation[10] = cos(0.00281359 * rotate_y + y_angle);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Z)) {
			float z_angle = acos(rotation[5]);

			if (z_angle >= 3.12) {
				rotate_z = -1.0f;
			}
			else if (z_angle <= 0) {
				rotate_z = 1.0f;
			}

			rotation[0] = cos(0.00281359 * rotate_z + z_angle);
			rotation[1] = sin(0.00281359 * rotate_z + z_angle);
			rotation[4] = -sin(0.00281359 * rotate_z + z_angle);
			rotation[5] = cos(0.00281359 * rotate_z + z_angle);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_O)) {
			if (fabs(scale[0]) <= 0.0f || fabs(scale[0]) > 1.0f)
			{
				scale[0] += 0.001f;
				scale[5] += 0.001f;
				scale[10] += 0.001f;

			}
			else
			{
				scale[0] -= 0.001f;
				scale[5] -= 0.001f;
				scale[10] -= 0.001f;

			}

			float x_angle = acos(rotation[5]);

			if (x_angle >= 3.12) {
				rotate_x = -1.0f;
			}
			else if (x_angle <= 0) {
				rotate_x = 1.0f;
			}

			rotation[5] = cos(0.00281359 * rotate_x + x_angle);
			rotation[7] = sin(0.00281359 * rotate_x + x_angle);
			rotation[9] = -sin(0.00281359 * rotate_x + x_angle);
			rotation[10] = cos(0.00281359 * rotate_x + x_angle);
		}
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_M)) {
			float z_angle = acos(rotation[5]);

			if (z_angle >= 3.12) {
				rotate_z = -1.0f;
			}
			else if (z_angle <= 0) {
				rotate_z = 1.0f;
			}

			rotation[0] = cos(0.00281359 * rotate_z + z_angle);
			rotation[1] = sin(0.00281359 * rotate_z + z_angle);
			rotation[4] = -sin(0.00281359 * rotate_z + z_angle);
			rotation[5] = cos(0.00281359 * rotate_z + z_angle);

			rotation2[0] = cos(0.00281359 * rotate_z + z_angle);
			rotation2[1] = sin(0.00281359 * rotate_z + z_angle);
			rotation2[4] = -sin(0.00281359 * rotate_z + z_angle);
			rotation2[5] = cos(0.00281359 * rotate_z + z_angle);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader_programme);
		glBindVertexArray(vao);

		glUniformMatrix4fv(translation_loc, 1, false, translation);
		glUniformMatrix4fv(rotation_loc, 1, false, rotation);
		glUniformMatrix4fv(scale_loc, 1, false, scale);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUniformMatrix4fv(rotation_loc, 1, false, rotation2);
		glDrawArrays(GL_TRIANGLES, 3, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}