#ifndef STRUCT_H
#define STRUCT_H

struct gameSettings {
	int fieldW, fieldH;
};

struct cell {
	bool isAlive;
};

typedef cell** gameField;

#endif // STRUCT_H
