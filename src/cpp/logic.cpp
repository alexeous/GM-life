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
		field[i][0].isAlive = field[i][w+1].isAlive = false;	// заполняем клетки по бокам поля
		for(int j = 1; j <= w; j++)
            if(rand() % 100 < settings.population)
                firstBorn(field, i, j);
            else field[i][j].isAlive = false;
	}
	for(int j = 0; j < w+2; j++) {
		field[0][j].isAlive = field[h+1][j].isAlive = false;	// заполняем клетки сверху и снизу поля
	}
	cleardevice();
}


#define ADD_ALIVE_NEIGHBOR(nh, nw) \
    if(field[(nh)][(nw)].isAlive) { \
        if(neighbors_out != NULL) neighbors_out[neighbors] = field[(nh)][(nw)]; \
        neighbors++; \
    }

int neighborsAlive(gameField field, const int h, const int w, cell *neighbors_out) {
    int neighbors = 0;
    ADD_ALIVE_NEIGHBOR(h - 1, w - 1);   //
    ADD_ALIVE_NEIGHBOR(h - 1,   w  );   //
    ADD_ALIVE_NEIGHBOR(h - 1, w + 1);   //
    ADD_ALIVE_NEIGHBOR(  h  , w - 1);   // Проверяем все
    ADD_ALIVE_NEIGHBOR(  h  , w + 1);   // соседние клетки
    ADD_ALIVE_NEIGHBOR(h + 1, w - 1);   //
    ADD_ALIVE_NEIGHBOR(h + 1,   w  );   //
    ADD_ALIVE_NEIGHBOR(h + 1, w + 1);   //
    return neighbors;
}

// Копирует поле из src в dest
void copyField(const gameSettings settings, gameField &dest, const gameField src) {
    for(int i = 1; i <= settings.fieldH; i++) {
        size_t size = sizeof(cell) * (settings.fieldW + 2); // вычисляем, сколько байт скопировать
        memcpy(dest[i], src[i], size);  // копируем сразу целую строку
    }
}

void firstBorn(gameField &field, const int h, const int w) {
    for (int i = 0; i < 9; i++) {
        field[h][w].socialGene[i] = rand() % 2;
    }
    field[h][w].isAlive = true;
    field[h][w].health = 1;
}

void bornCell(gameField oldField, gameField &newField, const int h, const int w) {
    newField[h][w].isAlive = true;
    newField[h][w].health = 1;
    
    cell parents[8];
    int parentCount = neighborsAlive(oldField, h, w, parents);
    
    int parentIndex = rand() % parentCount;
    memcpy(newField[h][w].socialGene, parents[parentIndex].socialGene, sizeof(bool)*8);
}

void harmCell(gameField &field, const int h, const int w) {
    if(--field[h][w].health <= 0)
        field[h][w].isAlive = false;
}

bool wouldMigrateTo(const gameSettings settings, gameField field, int h, int w, int toH, int toW) {
    if(toH < 1 || toH > settings.fieldH ||
       toW < 1 || toW > settings.fieldW ||
       field[toH][toW].isAlive)
        return false;
    int neighbors = neighborsAlive(field, toH, toW) - 1;     // минус сама клетка, входящая в число соседей
    return field[h][w].socialGene[neighbors];
}

#define CONSIDER_MIGRATE_TO(toH, toW) \
    if(wouldMigrateTo(settings, field, h, w, (toH), (toW))) \
        comfortCells.push_back(&field[(toH)][(toW)]);

void migrateCell(const gameSettings settings, gameField &field, const int h, const int w) 
{
    std::vector<cell*> comfortCells;
    
    CONSIDER_MIGRATE_TO(h - 1, w - 1);
    CONSIDER_MIGRATE_TO(h - 1,   w  );
    CONSIDER_MIGRATE_TO(h - 1, w + 1);
    CONSIDER_MIGRATE_TO(  h  , w - 1);
    CONSIDER_MIGRATE_TO(  h  , w + 1);
    CONSIDER_MIGRATE_TO(h + 1, w - 1);
    CONSIDER_MIGRATE_TO(h + 1,   w  );
    CONSIDER_MIGRATE_TO(h + 1, w + 1);

    if(!comfortCells.empty()) {
        cell *destination = comfortCells[rand() % comfortCells.size()];
        *destination = field[h][w];
        field[h][w].isAlive = false;
    }
}

void logic(const gameSettings settings, gameField &oldField) {
    gameField newField;
    if(settings.socialGene) {
        for(int i = 1; i <= settings.fieldH; i++)
            for(int j = 1; j <= settings.fieldW; j++) {
                // Перед тем, как будет рассчитано новое поколение,
                // клетки мигрируют в комфортные условия
                if (oldField[i][j].isAlive)
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
                if(neighbors < 2 || neighbors > 3) harmCell(newField, i, j);
            }
        }
	}
	copyField(settings, oldField, newField);
}
