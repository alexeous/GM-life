#ifndef STRUCT_H
#define STRUCT_H

struct gameSettings {
	int fieldW, fieldH;
	int windowW, windowH;
};

struct cell {
	bool isAlive;
};

typedef cell** gameField;

#endif // STRUCT_H
