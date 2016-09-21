//glfw setting replay

#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1) {
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}
		for (int i = i0; i <= i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);
		}
}
void drawCircle(const int& i0, const int& j0, const float& red, const float& green, const float& blue) {
	int r = 50;
	for (int i = i0 - r; i < i0 + r; i++) {
		for (int j = j0 - r; j < j0 + r; j++) {
			int n = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
			int n2 = (i - i0)*(i - i0) + (j - j0)*(j - j0) - (r-1)*(r-1) +2*r -1;
			if (n < 0 && n2>0)
				drawPixel(i, j, 0.0f, 0.0f, 0.0f);
		}
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													/*	for (int i = 0; i<width*height; i++) {
													pixels[i * 3 + 0] = 1.0f; // red
													pixels[i * 3 + 1] = 1.0f; // green
													pixels[i * 3 + 2] = 1.0f; // blue
													}*/

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	//색칠된 사각형
	drawLine(100, 50, 200, 50, 0.0f, 0.0f, 0.0f);
	drawLine(100, 100, 200, 100, 0.0f, 0.0f, 0.0f);
	drawLine(100, 50, 100, 100, 0.0f, 0.0f, 0.0f);
	drawLine(200, 50, 200, 100, 0.0f, 0.0f, 0.0f);
	for (int i = 50; i < 100; i++) {
		drawLine(100, i, 200, i, 0.0f, 0.0f, 0.0f);
	}
	//삼각형
	drawLine(300, 200, 400, 200, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 2; i++){
		drawLine(300, 200 + i, 350, 300 + i, 0.0f, 0.0f, 0.0f);
		drawLine(350, 300 + i, 400, 200 + i, 0.0f, 0.0f, 0.0f);
	}
	//오각형
		drawLine(500, 200, 550, 200, 0.0f, 0.0f, 0.0f);
		drawLine(480, 250, 525, 290, 0.0f, 0.0f, 0.0f);
		drawLine(525, 290, 570, 250, 0.0f, 0.0f, 0.0f);
	
		drawLine(480, 250, 500, 200, 0.0f, 0.0f, 0.0f);
		drawLine(480, 251, 500, 201, 0.0f, 0.0f, 0.0f);

		drawLine(550, 200, 570, 250, 0.0f, 0.0f, 0.0f);
		drawLine(550, 201, 570, 251, 0.0f, 0.0f, 0.0f);

	//진한 선
		drawLine(100, 200, 200, 300, 0.0f, 0.0f, 0.0f);
		drawLine(100, 201, 199, 300, 0.0f, 0.0f, 0.0f);
		drawLine(101, 200, 200, 299, 0.0f, 0.0f, 0.0f);

	//색칠안된 사각형
	drawLine(400, 50, 500, 50, 0.0f, 0.0f, 0.0f);
	drawLine(400, 100, 500, 100, 0.0f, 0.0f, 0.0f);
	drawLine(400, 50, 400, 100, 0.0f, 0.0f, 0.0f);
	drawLine(500, 50, 500, 100, 0.0f, 0.0f, 0.0f);

	//테두리 진한 원
	drawCircle(300, 75, 0.0f, 0.0f, 0.0f);
	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
