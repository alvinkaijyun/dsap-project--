#include "MemorySystem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

MemorySystem::MemorySystem() {
    memory_count = 0;
    current_day = 1;
}

int MemorySystem::countMemoriesAddedToday() {
    int count = 0;

    for (int i = 0; i < memory_count; i++) {
        if (memories[i].getDayCreated() == current_day) {
            count++;
        }
    }

    return count;
}

void MemorySystem::addMemory() {
    if (memory_count >= MAX_MEMORY) {
        cout << "Memory storage full!" << endl;
        return;
    }

    string name;
    int importance;

    cout << "Enter memory name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter importance (1-10): ";
    cin >> importance;

    int added_today = countMemoriesAddedToday();

    memories[memory_count].initialize(name, importance, current_day, added_today);
    memory_count++;

    cout << "Memory added successfully!" << endl;
}

void MemorySystem::memoryBrowser() {
    int choice;

    while (true) {
        cout << "\n===== Memory Browser =====" << endl;
        cout << "1. Recommended List" << endl;
        cout << "2. View" << endl;
        cout << "3. Search" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) recommendedListMenu();
        else if (choice == 2) viewMenu();
        else if (choice == 3) searchMenu();
        else if (choice == 0) return;
        else cout << "Invalid choice!" << endl;
    }
}

void MemorySystem::recommendedListMenu() {
    if (current_day < 3) {
        cout << "Recommended list starts from Day 3." << endl;
        return;
    }

    int indices[MAX_MEMORY];
    int count = buildRecommendedList(indices);

    if (count == 0) {
        cout << "No recommended memories today." << endl;
        return;
    }

    cout << "\n===== Recommended List =====" << endl;
    displayMemoryList(indices, count);
}

int MemorySystem::buildUrgentList(int order[]) {
    int count = 0;

    for (int i = 0; i < memory_count; i++) {
        order[count] = i;
        count++;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (memories[order[j]].urgentScore() > memories[order[i]].urgentScore()) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    return count;
}

int MemorySystem::buildRecommendedList(int result[]) {
    int urgent[MAX_MEMORY];
    int urgent_count = buildUrgentList(urgent);

    int count = 0;
    int limit = urgent_count;
    if (limit > 5) limit = 5;

    for (int i = 0; i < limit; i++) {
        result[count] = urgent[i];
        count++;
    }

    int inner_index = -1;
    double best_inner_score = -1;

    for (int i = 0; i < memory_count; i++) {
        if (memories[i].canBeInnerVoiceCandidate() && memories[i].passesInnerVoiceChance()) {
            double score = memories[i].innerVoiceScore();

            if (score > best_inner_score) {
                best_inner_score = score;
                inner_index = i;
            }
        }
    }

    if (inner_index != -1) {
        memories[inner_index].innerVoiceEffect();

        bool already_in_list = false;
        for (int i = 0; i < count; i++) {
            if (result[i] == inner_index) already_in_list = true;
        }

        if (!already_in_list) {
            result[count] = inner_index;
            count++;
        }

        cout << "[INNER VOICE] A memory resurfaced and became easier to dream about." << endl;
    }
    else {
        cout << "[INNER VOICE] No deep, suppressed, or faded memory is resurfacing today." << endl;
    }

    return count;
}

void MemorySystem::viewMenu() {
    int choice;

    while (true) {
        cout << "\n===== View Memories =====" << endl;
        cout << "1. View All" << endl;
        cout << "2. View by Layer" << endl;
        cout << "3. View by State" << endl;
        cout << "4. View by Suppression" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) viewAll();
        else if (choice == 2) viewByLayer();
        else if (choice == 3) viewByState();
        else if (choice == 4) viewBySuppression();
        else if (choice == 0) return;
        else cout << "Invalid choice!" << endl;
    }
}

void MemorySystem::viewAll() {
    int indices[MAX_MEMORY];
    int count = 0;

    for (int i = 0; i < memory_count; i++) {
        indices[count++] = i;
    }

    cout << "\n===== View All Memories =====" << endl;
    displayMemoryList(indices, count);
}

void MemorySystem::viewByLayer() {
    int choice;

    cout << "\n===== View by Layer =====" << endl;
    cout << "1. Working" << endl;
    cout << "2. Long-term" << endl;
    cout << "3. Deep" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 0) return;
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice." << endl;
        return;
    }

    int target_layer = choice - 1;
    int indices[MAX_MEMORY];
    int count = 0;

    for (int i = 0; i < memory_count; i++) {
        if (memories[i].getLayer() == target_layer) {
            indices[count++] = i;
        }
    }

    displayMemoryList(indices, count);
}

void MemorySystem::viewByState() {
    int choice;

    cout << "\n===== View by State =====" << endl;
    cout << "1. Active" << endl;
    cout << "2. Faded" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 0) return;
    if (choice < 1 || choice > 2) {
        cout << "Invalid choice." << endl;
        return;
    }

    int target_state = choice - 1;
    int indices[MAX_MEMORY];
    int count = 0;

    for (int i = 0; i < memory_count; i++) {
        if (memories[i].getState() == target_state) {
            indices[count++] = i;
        }
    }

    displayMemoryList(indices, count);
}

void MemorySystem::viewBySuppression() {
    int choice;

    cout << "\n===== View by Suppression =====" << endl;
    cout << "1. None" << endl;
    cout << "2. Mild" << endl;
    cout << "3. Moderate" << endl;
    cout << "4. Severe" << endl;
    cout << "0. Back" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 0) return;
    if (choice < 1 || choice > 4) {
        cout << "Invalid choice." << endl;
        return;
    }

    int indices[MAX_MEMORY];
    int count = 0;

    for (int i = 0; i < memory_count; i++) {
        int level = memories[i].getSuppressionLevel();

        if (choice == 1 && level == 0) indices[count++] = i;
        else if (choice == 2 && level >= 1 && level <= 2) indices[count++] = i;
        else if (choice == 3 && level >= 3 && level <= 4) indices[count++] = i;
        else if (choice == 4 && level >= 5) indices[count++] = i;
    }

    displayMemoryList(indices, count);
}

void MemorySystem::searchMenu() {
    if (memory_count == 0) {
        cout << "No memories stored." << endl;
        return;
    }

    string keyword;

    cout << "Enter search keyword: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyword);

    int indices[MAX_MEMORY];
    int count = 0;

    for (int i = 0; i < memory_count; i++) {
        if (memories[i].nameContains(keyword)) {
            indices[count++] = i;
        }
    }

    cout << "\n===== Search Results =====" << endl;
    displayMemoryList(indices, count);
}

void MemorySystem::displayMemoryList(int indices[], int count) {
    if (count == 0) {
        cout << "No memories found." << endl;
        return;
    }

    while (true) {
        cout << "\n===== Memory List =====" << endl;

        for (int i = 0; i < count; i++) {
            cout << i + 1 << ") ";
            memories[indices[i]].print(indices[i]);
        }

        int choice;
        cout << "Choose one memory to view detail (0 to back): ";
        cin >> choice;

        if (choice == 0) return;

        if (choice < 1 || choice > count) {
            cout << "Invalid choice." << endl;
        }
        else {
            memoryDetailMenu(indices[choice - 1]);
        }
    }
}

void MemorySystem::memoryDetailMenu(int index) {
    int choice;

    while (true) {
        memories[index].printDetail(index);

        cout << "\n1. Review" << endl;
        cout << "2. Suppress" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            bool reduced = memories[index].review();

            if (reduced) {
                cout << "Suppression level decreased." << endl;
            }

            cout << "Memory reviewed successfully." << endl;
        }
        else if (choice == 2) {
            memories[index].suppress();
            cout << "Suppression level increased." << endl;
        }
        else if (choice == 0) {
            return;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
}

int MemorySystem::pickDreamMemory() {
    double total = 0;

    for (int i = 0; i < memory_count; i++) {
        total += memories[i].dreamScore(current_day);
    }

    if (total <= 0) return -1;

    double r = ((double)rand() / RAND_MAX) * total;
    double current = 0;

    for (int i = 0; i < memory_count; i++) {
        current += memories[i].dreamScore(current_day);

        if (r <= current) return i;
    }

    return memory_count - 1;
}

void MemorySystem::dreamRecall() {
    if (current_day < 3) {
        cout << "Dream recall starts from Day 3." << endl;
        return;
    }

    if (memory_count == 0) {
        cout << "No memories to dream about." << endl;
        return;
    }

    cout << "\n===== Dream Recall =====" << endl;

    int dream_times = 3;
    if (memory_count < 3) dream_times = memory_count;

    for (int i = 0; i < dream_times; i++) {
        int index = pickDreamMemory();

        if (index == -1) {
            cout << "The dream is empty." << endl;
            return;
        }

        memories[index].dreamEffect(current_day);

        cout << "Dreamed of: ";
        memories[index].print(index);
    }
}

void MemorySystem::sleepAndNextDay() {
    cout << "\n===== Sleep Phase =====" << endl;

    dreamRecall();

    for (int i = 0; i < memory_count; i++) {
        memories[i].applyDailyDecay();
    }

    current_day++;

    cout << "Sleep ended. A new day begins... Day " << current_day << endl;
}

void MemorySystem::run() {
    srand(time(0));

    int choice;

    while (true) {
        cout << "\n===== DreamCore Memory System =====" << endl;
        cout << "Current Day: " << current_day << endl;
        cout << "1. Add Memory" << endl;
        cout << "2. Memory Browser" << endl;
        cout << "3. Sleep" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) addMemory();
        else if (choice == 2) memoryBrowser();
        else if (choice == 3) sleepAndNextDay();
        else if (choice == 0) {
            cout << "Exiting DreamCore..." << endl;
            break;
        }
        else cout << "Invalid choice!" << endl;
    }
}