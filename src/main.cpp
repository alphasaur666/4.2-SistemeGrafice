#include "MyScene.h"

int main(int argc, char* argv[])
{
	MyScene* scene = new MyScene(argc, argv, "Proiect Grafica", static_cast<const int>(600), static_cast<const int>(400));

	scene->Run();

	delete scene;
	return 0;
}
