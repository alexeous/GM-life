#include "const.h"
#include "logic.h"
#include "graphics.h"
#include <ctime>
#include <vector>
#include <stdlib.h>

void startGame(const gameSettings settings, gameField &field) {
	int w = settings.fieldW;
	int h = settings.fieldH;
	for(int i = 0; i < h+2; i++) {
		field[i][0].isAlive = false;    // заполняем краевые клетки слева
        field[i][w+1].isAlive = false;	// и справа поля
		for(int j = 1; j <= w; j++) {
            int chanceToBorn = rand() % 100;
            if(chanceToBorn < settings.population)
                firstBorn(settings, field[i][j]);
            else 
                field[i][j].isAlive = false;
            field[i][j].needRefresh = true;
		}
	}
	for(int j = 0; j < w+2; j++) {
		field[0][j].isAlive = false;    // заполняем краевые клетки сверху
        field[h+1][j].isAlive = false;	// и снизу поля
	}
	cleardevice();
}


int neighborsAlive(const gameField field, const int h, const int w, cell *neighbors_out) {
    int neighbors = 0;

    for(int i = 0; i < 8; i++) {
        int nbH = h + neighborsOffsets[i].h;
        int nbW = w + neighborsOffsets[i].w;
        if(field[nbH][nbW].isAlive) {
            if(neighbors_out != NULL)
                neighbors_out[neighbors] = field[nbH][nbW];
            neighbors++;
        }
    }
    return neighbors;
}

// Копирует поле из src в dest
void copyField(const gameSettings settings, gameField &dest, const gameField src) {
    for(int i = 1; i <= settings.fieldH; i++) {
        size_t size = sizeof(cell) * (settings.fieldW + 2); // вычисляем, сколько байт скопировать
        memcpy(dest[i], src[i], size);  // копируем сразу целую строку
    }
}

void firstBorn(const gameSettings settings, cell &newcell) {
    newcell.socialGene = rand() % 9;
    newcell.isAlive = true;
    newcell.age = 0;

    if(settings.survivalGene)
        newcell.health = newcell.maxHealth = (rand() % MAX_HEALTH) + 1;
    else newcell.health = newcell.maxHealth = 1;

    if(settings.lazyGene && rand() % 2 == 1) newcell.isLazy = true;
    else newcell.isLazy = false;
}

void bornCell(const gameField oldField, gameField &newField, const int h, const int w) {
    cell &newcell = newField[h][w];
    newcell.isAlive = true;
    newcell.age = 0;
    newcell.needRefresh = true;

    cell parents[8];
    int parentCount = neighborsAlive(oldField, h, w, parents);

    int parentIndex = rand() % parentCount;
    newcell.socialGene = parents[parentIndex].socialGene;

    parentIndex = rand() % parentCount;
    newcell.maxHealth = parents[parentIndex].maxHealth;
    newcell.health = newcell.maxHealth;

    parentIndex = rand() % parentCount;
    newcell.isLazy = parents[parentIndex].isLazy;
}

void harmCell(cell &c) {
    if(c.health > 0) 
        c.health--;
    if(c.health <= 0)
        c.isAlive = false;
    c.needRefresh = true;
}

void cellAging(cell &c) {
	if(c.isAlive){
		if(c.age < MAX_AGE) c.age++;
		else {
            c.isAlive = false;
            c.needRefresh = true;
        }
	}
}

bool wouldMigrateTo(const gameSettings settings, gameField field, int h, int w, int toH, int toW) {
    if(toH < 1 || toH > settings.fieldH ||
       toW < 1 || toW > settings.fieldW ||
       field[toH][toW].isAlive)
        return false;
    int neighbors = neighborsAlive(field, toH, toW) - 1;     // минус сама клетка, входящая в число соседей
    return field[h][w].socialGene == neighbors;
}

void migrateCell(const gameSettings settings, gameField &field, const int h, const int w) {
    std::vector<cell*> comfortCells;

    for(int i = 0; i < 8; i++) {
        int toH = h + neighborsOffsets[i].h;
        int toW = w + neighborsOffsets[i].w;
        if(wouldMigrateTo(settings, field, h, w, toH, toW))
            comfortCells.push_back(&field[toH][toW]);
    }
    if(!comfortCells.empty()) {
        cell *destination = comfortCells[rand() % comfortCells.size()];
        *destination = field[h][w];
        destination->needRefresh = true;
        field[h][w].isAlive = false;
        field[h][w].needRefresh = true;
    }
}

void logic(const gameSettings settings, gameField &oldField) {
    gameField newField;
    if(settings.socialGene) {
        for(int i = 1; i <= settings.fieldH; i++)
            for(int j = 1; j <= settings.fieldW; j++) {
                // Перед тем, как будет рассчитано новое поколение,
                // клетки мигрируют в комфортные условия
                bool doMigrate = true;
				if (oldField[i][j].isLazy) 
					doMigrate = rand() % 10 < 3;
                if (oldField[i][j].isAlive && doMigrate)
                    migrateCell(settings, oldField, i, j);
            }
    }
	copyField(settings, newField, oldField);
    for(int i = 1; i <= settings.fieldH; i++) {
        for(int j = 1; j <= settings.fieldW; j++) {
            int neighbors = neighborsAlive(oldField, i, j);
            if (oldField[i][j].isAlive == false) { // Рождается, если 3 живых соседа, иначе остаётся мертвой:
                if(neighbors == 3) bornCell(oldField, newField, i, j);
            } else {    // Теряет здоровье, когда меньше 2 или больше 3 соседей:
                if(neighbors < 2 || neighbors > 3) harmCell(newField[i][j]);
            }
            if(settings.aging) cellAging(newField[i][j]);
        }
	}
	copyField(settings, oldField, newField);
}
