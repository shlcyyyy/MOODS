#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>

using namespace std;

struct MoodEntry {
    string date;
    string emotion;
    int intensity;
    string reflection;
};


struct Node {
    MoodEntry data;
    Node* next;
};


vector<MoodEntry> moodLog;      
queue<MoodEntry> realTimeQueue; 
Node* head = nullptr;     


string getMoodMessage(string mood) {
    if (mood == "Happy") return "Happiness is a direction, not a place. ";
    if (mood == "Sad") return "It's okay to feel sad. Brighter days will come. ";
    if (mood == "Stressed") return "Take a deep breath. One step at a time. ";
    if (mood == "Calm") return "Peace begins with a calm mind. ";
    if (mood == "Angry") return "Pause. Breathe. Respond, don’t react. ";
    return "";
}


void addToLinkedList(MoodEntry entry) {
    Node* newNode = new Node{entry, nullptr};

    if (!head) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}


void record_emotion_entry() {
    MoodEntry entry;

    cout << "\n--- Record Emotion ---\n";
    cout << "Date (YYYY-MM-DD): ";
    cin >> entry.date;

    cout << "Emotion (Happy/Sad/Stressed/Calm/Angry): ";
    cin >> entry.emotion;

    cout << "Intensity (1-10): ";
    cin >> entry.intensity;

    cin.ignore();
    cout << "Reflection: ";
    getline(cin, entry.reflection);

    // store in all structures
    moodLog.push_back(entry);
    realTimeQueue.push(entry);
    addToLinkedList(entry);

    cout << "\nSuccessfully Saved ✔ " << getMoodMessage(entry.emotion) << endl;
}


void view_emotion_history() {
    cout << "\n--- Mood History ---\n";

    if (moodLog.empty()) {
        cout << "No records found.\n";
        return;
    }

    for (int i = moodLog.size() - 1; i >= 0; i--) {
        cout << "\nDate: " << moodLog[i].date;
        cout << "\nEmotion: " << moodLog[i].emotion;
        cout << "\nIntensity: " << moodLog[i].intensity;
        cout << "\nReflection: " << moodLog[i].reflection;
        cout << "\n-------------------------\n";
    }
}


void analyze_emotions() {
    cout << "\n--- Emotion Analysis ---\n";

    if (moodLog.empty()) {
        cout << "No data available.\n";
        return;
    }

    int total = 0;
    int count = moodLog.size();

    int happy = 0, sad = 0, stressed = 0, calm = 0, angry = 0;

    for (auto &m : moodLog) {
        total += m.intensity;

        if (m.emotion == "Happy"){
            happy++;
        }
        else if (m.emotion == "Sad"){
            sad++;
        } 
        else if (m.emotion == "Stressed"){
            stressed++;
        } 
        else if (m.emotion == "Calm"){
            calm++;
        }
        else if (m.emotion == "Angry") {
            angry++;
        }
    }

    double avg = (double)total / count;

    cout << fixed << setprecision(2);
    cout << "Average Intensity: " << avg << "/10.00\n";

    if (avg < 4){
        cout << "Trend: Low Emotional Intensity \n";
    }
    else if (avg < 7){
        cout << "Trend: Moderate Emotional Balance \n";
    }
    else{
        cout << "Trend: High Emotional Activity \n";
    }

    cout << "\nEmotion Frequency:\n";
    cout << "Happy: " << happy << endl;
    cout << "Sad: " << sad << endl;
    cout << "Stressed: " << stressed << endl;
    cout << "Calm: " << calm << endl;
    cout << "Angry: " << angry << endl;

    if (stressed >= 3)
        cout << "\n⚠ ALERT: Prolonged stress detected. Consider taking a break.\n";
    if (sad >= 3)
        cout << "⚠ ALERT: Signs of emotional distress detected.\n";
}


void create_summary() {
    cout << "\n--- Summary Report ---\n";

    if (moodLog.empty()) {
        cout << "No data available.\n";
        return;
    }

    cout << "Total Entries: " << moodLog.size() << endl;
    cout << "Latest Mood: " << moodLog.back().emotion << endl;
    cout << "Latest Intensity: " << moodLog.back().intensity << endl;
}


void show_menu() {
    cout << "\n------------------------------\n";
    cout << " M.O.O.D.S SYSTEM\n";
    cout << " Monitoring of Overall Emotional Data for Support\n";
    cout << "==============================\n";
    cout << "1. Record Emotion\n";
    cout << "2. View History\n";
    cout << "3. Analyze Emotions\n";
    cout << "4. Create Summary\n";
    cout << "5. Exit\n";
    cout << "Choose: ";
}


int main() {
    int choice;

    do {
        show_menu();
        cin >> choice;

        switch (choice) {
            case 1: record_emotion_entry(); break;
            case 2: view_emotion_history(); break;
            case 3: analyze_emotions(); break;
            case 4: create_summary(); break;
            case 5: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}