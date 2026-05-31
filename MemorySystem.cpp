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
    int choice;

    while (true) {
        cout << "\n===== Add Memory =====" << endl;
        cout << "1. Choose from preset memory list" << endl;
        cout << "2. Add custom memory" << endl;
        cout << "0. Back" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            addMemoryFromPreset();
        }
        else if (choice == 2) {
            addCustomMemory();
        }
        else if (choice == 0) {
            return;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
}

void MemorySystem::addMemoryFromPreset() {
    if (memory_count >= MAX_MEMORY) {
        cout << "Memory storage full!" << endl;
        return;
    }

    string preset_memories[] = {
        "Going to class",
        "Studied for an exam",
        "Worked on a group project",
        "Performed on stage",
        "Went to the library",
        "Had a meal with friends",
        "Practiced for activity",
        "Met a new friend",
        "Achieved a personal goal",
        "Spent time alone",
        "Missed a deadline",
        "Stayed up late",
        "Felt stressed",
        "Talked with friends",
        "Talked with family",
        "Talked with someone I like",
        "Exercise",
        "Prepared for a presentation",
        "Had a meaningful conversation",
        "Felt lonely or disconnected",
        "Completed an assignment",
        "Skipped a class",
        "Listened to music",
        "Played a video game",
        "Remembered a childhood memory",
        "Thought about the future"
    };

    const int PRESET_COUNT = 26;

    cout << "\n===== Preset Memory List =====" << endl;

    for (int i = 0; i < PRESET_COUNT; i++) {
        cout << i + 1 << ". " << preset_memories[i] << endl;
    }

    cout << "0. Back" << endl;

    int choice;
    cout << "Choose a memory: ";
    cin >> choice;

    if (choice == 0) {
        return;
    }

    if (choice < 1 || choice > PRESET_COUNT) {
        cout << "Invalid choice." << endl;
        return;
    }

    int importance;
    cout << "Enter importance (1-10): ";
    cin >> importance;

    int added_today = countMemoriesAddedToday();

    memories[memory_count].initialize(
        preset_memories[choice - 1],
        importance,
        current_day,
        added_today
    );

    memory_count++;

    cout << "Preset memory added successfully!" << endl;
}

void MemorySystem::addCustomMemory() {
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

    memories[memory_count].initialize(
        name,
        importance,
        current_day,
        added_today
    );

    memory_count++;

    cout << "Custom memory added successfully!" << endl;
}

void MemorySystem::loadSampleData() {
    if (memory_count > 0) {
        cout << "Sample data can only be loaded when memory storage is empty." << endl;
        return;
    }

    string sample_names[] = {
        "Studied for an exam",
        "Had a meal with friends",
        "Missed a deadline",
        "Performed on stage",
        "Remembered a childhood memory",
        "Felt lonely or disconnected",
        "Talked with family",
        "Thought about the future"
    };

    int sample_importance[] = {
        7, 6, 8, 9, 10, 8, 7, 9
    };

    const int SAMPLE_COUNT = 8;

    for (int i = 0; i < SAMPLE_COUNT; i++) {
        int added_today = countMemoriesAddedToday();

        memories[memory_count].initialize(
            sample_names[i],
            sample_importance[i],
            current_day,
            added_today
        );

        memory_count++;
    }

    // 讓部分資料產生不同狀態，方便 demo
    memories[0].review();
    memories[0].review();

    memories[3].review();
    memories[3].review();
    memories[3].review();
    memories[3].review();
    memories[3].review();

    memories[4].suppress();
    memories[4].suppress();

    memories[5].suppress();

    cout << "Sample data loaded successfully." << endl;
}

void MemorySystem::showStatistics() {
    int working = 0;
    int long_term = 0;
    int deep = 0;

    int active = 0;
    int faded = 0;

    int suppression_none = 0;
    int suppression_mild = 0;
    int suppression_moderate = 0;
    int suppression_severe = 0;

    for (int i = 0; i < memory_count; i++) {
        int layer = memories[i].getLayer();
        int state = memories[i].getState();
        int suppression = memories[i].getSuppressionLevel();

        if (layer == 0) {
            working++;
        }
        else if (layer == 1) {
            long_term++;
        }
        else if (layer == 2) {
            deep++;
        }

        if (state == 0) {
            active++;
        }
        else if (state == 1) {
            faded++;
        }

        if (suppression == 0) {
            suppression_none++;
        }
        else if (suppression >= 1 && suppression <= 2) {
            suppression_mild++;
        }
        else if (suppression >= 3 && suppression <= 4) {
            suppression_moderate++;
        }
        else {
            suppression_severe++;
        }
    }

    cout << "\n===== Memory Statistics =====" << endl;
    cout << "Current Day: " << current_day << endl;
    cout << "Total Memories: " << memory_count << endl;

    cout << "\nLayer:" << endl;
    cout << "Working: " << working << endl;
    cout << "Long-term: " << long_term << endl;
    cout << "Deep: " << deep << endl;

    cout << "\nState:" << endl;
    cout << "Active: " << active << endl;
    cout << "Faded: " << faded << endl;

    cout << "\nSuppression:" << endl;
    cout << "None: " << suppression_none << endl;
    cout << "Mild: " << suppression_mild << endl;
    cout << "Moderate: " << suppression_moderate << endl;
    cout << "Severe: " << suppression_severe << endl;
}

void MemorySystem::memoryBrowser() {
    int choice;

    while (true) {
        cout << "\n=====================================" << endl;
        cout << "          Memory Browser             " << endl;
        cout << "=====================================" << endl;
        cout << "Find memories by recommendation, filters, or search." << endl;
        cout << endl;
        cout << "1. Recommended List" << endl;
        cout << "2. View Memories" << endl;
        cout << "3. Search by Cue" << endl;
        cout << "0. Back" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Enter choice: ";

        if (choice == 1) {
            recommendedListMenu();
        }
        else if (choice == 2) {
            viewMenu();
        }
        else if (choice == 3) {
            searchMenu();
        }
        else if (choice == 0) {
            return;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
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

        cout << "\nActions:" << endl;
        cout << "1. Review - strengthen and gradually integrate this memory" << endl;
        cout << "2. Suppress - reduce conscious access but increase unconscious resurfacing" << endl;
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
        cout << "\n=====================================" << endl;
        cout << "        DreamCore Memory System        " << endl;
        cout << "=======================================" << endl;
        cout << "Day: " << current_day << endl;
        cout << endl;
        cout << "1. Add Memory" << endl;
        cout << "2. Memory Browser" << endl;
        cout << "3. Sleep" << endl;
        cout << "4. Load Sample Data" << endl;
        cout << "5. Show Statistics" << endl;
        cout << "0. Exit" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) addMemory();
        else if (choice == 2) memoryBrowser();
        else if (choice == 3) sleepAndNextDay();
        else if (choice == 4) loadSampleData();
        else if (choice == 5) showStatistics();
        else if (choice == 0) {
            cout << "Exiting DreamCore..." << endl;
            break;
        }
        else cout << "Invalid choice!" << endl;
    }
}