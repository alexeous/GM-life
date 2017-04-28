#ifndef STRUCT_H
#define STRUCT_H

#define MAX_FIELD_W 150
#define MAX_FIELD_H 150

struct gameSettings {
	int fieldW, fieldH;
};
const gameSettings defaultSettings = { 20, 20 };

struct cell {
	bool isAlive;
};

typedef cell** gameField;

#endif // STRUCT_H
