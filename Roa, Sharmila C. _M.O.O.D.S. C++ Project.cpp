#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;


struct Emotion {
    string date;
    string mood;
    int intensity;
    string reflection;
    string quote;
};


struct Node {
    Emotion data;
    Node* next;
};


struct EmotionSystem {
    vector<Emotion> history;
    queue<string> recentQueue;
    stack<string> emotionStack;
    Node* head = NULL;
};


string getQuote(string mood) {
    if (mood == "happy")
        return "Hold onto these moments, because they remind you that life, despite everything, still has beauty worth appreciating.";
    else if (mood == "sad")
        return "This feeling is temporary. Give yourself time, be gentle with your heart, and trust that brighter days are ahead.";
    else if (mood == "calm")
        return "Peace is a quiet strength. Let this calmness be your anchor in the storms of life.";
    else if (mood == "stressed")
        return "Breathe. One step at a time. You are stronger than the pressure you feel. This too shall pass.";
    else if (mood == "angry")
        return "Pause before you react. You are in control. Understand it, don't suppress it. Channel it into something constructive.";
    else
        return "Your emotions are valid.";
}


void addToList(EmotionSystem &sys, Emotion e) {
    Node* newNode = new Node();
    newNode->data = e;
    newNode->next = sys.head;
    sys.head = newNode;
}


void checkAlert(EmotionSystem &sys, string mood) {
    int count = 0;

    for (auto &e : sys.history) {
        if (e.mood == mood){
            count++;
        } 
    }

    if (count >= 3) {
        cout << "\n Gentle Reminder (" << mood << "):\n";
        if (mood == "happy") {
            cout << "It's wonderful to see you feeling happy often! Keep nurturing these moments and sharing your joy with others.\n";
        } 
        if (mood == "calm") {
            cout << "Your calmness is a great asset. Continue to find ways to maintain this tranquility, and remember to share your peaceful energy with those around you.\n";
        } 
        if (mood == "sad") {
            cout << "It seems you've been feeling sad quite often. Remember, it's okay to seek support from friends, family, or a professional. You're not alone in this.\n";
        } else if (mood == "stressed") {
            cout << "You've been experiencing stress frequently. Consider taking breaks, practicing mindfulness, or talking to someone about what's causing this stress. Your well-being is important.\n";
        } else if (mood == "angry") {
            cout << "Anger can be overwhelming when it happens often. Try to identify triggers and find healthy outlets for your emotions, such as exercise or creative activities. Remember, it's okay to ask for help if you need it.\n";
        } else {
            cout << "You've been feeling " << mood << " quite a bit. Take a moment to reflect on what's contributing to this emotion and consider ways to nurture your well-being.\n";
        }
    }
}


void recordEmotion(EmotionSystem &sys) {
    Emotion e;

    cout << "\nEnter date (e.g. 2026-05-05): ";
    cin >> e.date;

    cout << "Enter emotion (happy, sad, calm, stressed, angry): ";
    cin >> e.mood;

    cout << "Enter intensity (1-10): ";
    cin >> e.intensity;

    cin.ignore(); // clear buffer

    cout << "Write reflection: ";
    getline(cin, e.reflection);

    e.quote = getQuote(e.mood);

    sys.history.push_back(e);
    sys.recentQueue.push(e.mood);
    sys.emotionStack.push(e.mood);
    addToList(sys, e);

    cout << "\n " << e.quote << endl;

    checkAlert(sys, e.mood);

    cout << "Emotion recorded successfully!\n";
}


void viewHistory(EmotionSystem &sys) {
    cout << "\n--- Emotion History ---\n";

    for (int i = 0; i < sys.history.size(); i++) {
        Emotion e = sys.history[i];

        cout << "\nEntry " << i + 1 << endl;
        cout << "Date: " << e.date << endl;
        cout << "Emotion: " << e.mood << endl;
        cout << "Intensity: " << e.intensity << "/10" << endl;
        cout << "Reflection: " << e.reflection << endl;
        cout << "Quote: " << e.quote << endl;
    }
}


void analyzeHistory(EmotionSystem &sys) {
    int happy = 0, sad = 0, calm = 0, stressed = 0, angry = 0;
    int totalIntensity = 0;

    for (auto &e : sys.history) {
        if (e.mood == "happy") happy++;
        else if (e.mood == "sad") sad++;
        else if (e.mood == "calm") calm++;
        else if (e.mood == "stressed") stressed++;
        else if (e.mood == "angry") angry++;

        totalIntensity += e.intensity;
    }

    cout << "\n--- Emotion Analysis ---\n";
    cout << "Happy: " << happy << endl;
    cout << "Sad: " << sad << endl;
    cout << "Calm: " << calm << endl;
    cout << "Stressed: " << stressed << endl;
    cout << "Angry: " << angry << endl;

    if (!sys.history.empty())
        cout << "Average Intensity: " 
        << (float)totalIntensity / sys.history.size() << endl;
}


void summary(EmotionSystem &sys) {
    cout << "\n=== SUMMARY ===\n";
    cout << "Total entries: " << sys.history.size() << endl;

    if (!sys.emotionStack.empty())
        cout << "Latest emotion: " << sys.emotionStack.top() << endl;

    if (!sys.recentQueue.empty())
        cout << "Oldest recent emotion: " << sys.recentQueue.front() << endl;
}


void menu() {
    cout << "\n==================================================\n";
    cout << "M.O.O.D.S\n";
    cout << " Monitoring of Overall Emotional Data for Support\n";
    cout << "==================================================\n";
    cout << "1. Record Emotion\n";
    cout << "2. View History\n";
    cout << "3. Analyze History\n";
    cout << "4. Summary\n";
    cout << "5. Exit\n";
    cout << "Choose: ";
}


int main() {
    EmotionSystem sys;
    int choice;

    do {
        menu();
        cin >> choice;

        switch (choice) {
            case 1: recordEmotion(sys); break;
            case 2: viewHistory(sys); break;
            case 3: analyzeHistory(sys); break;
            case 4: summary(sys); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}