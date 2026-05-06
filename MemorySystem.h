#ifndef MEMORYSYSTEM_H
#define MEMORYSYSTEM_H

#include "Memory.h"

class MemorySystem {
private:
    static const int MAX_MEMORY = 100;

    Memory memories[MAX_MEMORY];

    int memory_count;
    int current_day;

public:
    MemorySystem();

    void run();

    int countMemoriesAddedToday();

    void addMemory();

    void memoryBrowser();
    void recommendedListMenu();
    void viewMenu();
    void viewAll();
    void viewByLayer();
    void viewByState();
    void viewBySuppression();
    void searchMenu();

    void displayMemoryList(int indices[], int count);

    void memoryDetailMenu(int index);

    int buildUrgentList(int order[]);
    int buildRecommendedList(int result[]);

    int pickDreamMemory();
    void dreamRecall();

    void sleepAndNextDay();
};

#endif