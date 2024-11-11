#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map> // Include the map header
#include "StateData.h"
using namespace std;

class Quiz {
private:
    vector<pair<string, vector<string>>> quizQuestions;

public:
    Quiz() {
        // Initialize the quiz questions
        quizQuestions = {
            {"What Political culture do you want to be around?", {"Left", "Right", "Either"}},
            {"Coastal or Non-Coastal?", {"Coastal", "Non-Coastal", "Either"}},
            {"What Cost of Living is alright for you?", {"Less than 50k", "Between 50-60k", "Between 60-70k", "More than 70k"}},
            {"What average population size is good for you?", {"Less than 1M", "1M-5M", "5M-9M", "9M-13M", "More than 13M"}},
            {"Overall average summer weather?", {"50-60", "60-70F", "70-80F", "80-90F"}},
            {"Overall average winter weather?", {"0-10F", "10-20F", "20-30F", "30-40F", "40-50F"}},
            {"Do you want Snow?", {"Little Snow", "More Snow", "Lots of Snow"}},
            {"Do you want Rain?", {"Little Rain", "More Rain", "Lots of Rain"}},
            {"What kind of Environment do you want to live in?", {"Plains", "Desert", "Mountains", "Coastal", "Swamps", "Forest"}},
            {"What kind of Natural Disaster are you ok with dealing with?", {"Tornadoes", "Hurricanes", "Earthquakes", "Wildfires", "Volcanic Eruption", "Avalanches", "Flashfloods", "Winter Storms"}},
            {"Food?", {"Barbeque", "American", "Italian", "Pork", "Steak", "Pierogi"}}
        };
    }

    // Function to display questions and get user responses
    map<string, string> getResponses() {
        map<string, string> userResponses;

        for (const auto& question : quizQuestions) {
            cout << question.first << "\n";
            for (size_t i = 0; i < question.second.size(); ++i) {
                cout << i + 1 << ". " << question.second[i] << "\n";
            }

            int userChoice;
            bool validChoice = false;
            while (!validChoice) {
                cout << "Enter your choice (1-" << question.second.size() << "): ";
                cin >> userChoice;

                if (userChoice >= 1 && userChoice <= static_cast<int>(question.second.size())) {
                    userResponses[question.first] = question.second[userChoice - 1];
                    validChoice = true;
                } else {
                    cout << "Invalid choice. Please try again.\n";
                }
            }

            // Check if there is only one possible answer left for the next question
            bool narrowDown = false;
            for (const auto& response : userResponses) {
                if (find(question.second.begin(), question.second.end(), response.second) != question.second.end()) {
                    narrowDown = true;
                    break;
                }
            }

            // If there's only one possible answer left, automatically assign it to the user's response
            if (!narrowDown) {
                userResponses[question.first] = question.second.front();
                cout << "Automatically selected: " << question.second.front() << "\n";
            }
        }

        return userResponses;
    }
};

// Function to calculate state scores based on user responses
map<string, double> calculateStateScores(const map<string, string>& userResponses, const vector<State>& allStates) {

    map<string, double> stateScores;

    for (const auto& state : allStates) {
        double totalScore = 0.0;

        if (userResponses.find("What Political culture do you want to be around?")->second == state.politicalParty) {
            totalScore += 0.11;
        }
        if (userResponses.find("Coastal or Non-Coastal?")->second == state.coastal) {
            totalScore += 0.10;
        }
        if (userResponses.find("What Cost of Living is alright for you?")->second == state.costOfLiving) {
            totalScore += 0.9;
        }
        if (userResponses.find("What average population size is good for you?")->second == state.population) {
            totalScore += 0.8;
        }
        if (userResponses.find("Overall average summer weather?")->second == state.avgSummerTemp) {
            totalScore += 0.7;
        }
        if (userResponses.find("Overall average winter weather?")->second == state.avgWinterTemp) {
            totalScore += 0.6;
        }
        if (userResponses.find("Do you want Snow?")->second == state.snowFall) {
            totalScore += 0.5;
        }
        if (userResponses.find("Do you want Rain?")->second == state.rainFall) {
            totalScore += 0.4;
        }
        if (userResponses.find("What kind of Environment do you want to live in?")->second == state.environment) {
            totalScore += 0.3;
        }
        if (userResponses.find("What kind of Natural Disaster are you ok with dealing with?")->second == state.naturalDisasters) {
            totalScore += 0.2;
        }
        if (userResponses.find("Food?")->second == state.food) {
            totalScore += 0.1;
        }
        stateScores[state.name] = totalScore;
    }
    return stateScores;
}

// Function to recommend the best state based on calculated scores
string recommendBestState(const map<string, string>& userResponses, const vector<State>& allStates) {
    auto stateScores = calculateStateScores(userResponses, allStates);

    auto bestState = max_element(stateScores.begin(), stateScores.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });
    cout << "------------------------------------------------------------------------------";
    return "\nThe best state for you is " + bestState->first + " based on your preferences!";
}

int main() {
    Quiz quiz;
    map<string, string> userResponses = quiz.getResponses();

    vector<State> allStates = getAllStates();
    cout << recommendBestState(userResponses, allStates) << endl;

    return 0;
}
