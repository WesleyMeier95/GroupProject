all: GroupProject.EXE

GroupProject.EXE: GroupProjectDriver.cpp
	g++ GroupProjectDriver.cpp -o GroupProject.EXE -framework GLUT -framework openGL -framework Cocoa
