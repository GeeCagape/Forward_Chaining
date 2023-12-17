#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to print all facts
void printFacts(const vector<string>& factList) {
    cout << "\nFacts:" << endl;
    for (const auto& fact : factList) {
        cout << fact << endl;
    }
}

// Function to print all rules
void printRules(const vector<pair<string, string>>& ruleList) {
    cout << "\nRules:" << endl;
    for (const auto& rule : ruleList) {
        cout << "if " << rule.first << ", then " << rule.second << endl;
    }
}

// Function to check if a rule's premises are satisfied
bool isConditionSatisfied(const string& premise, const vector<string>& facts) {
    istringstream iss(premise);
    string condition;
    while (getline(iss, condition, ',')) {
        // Remove leading and trailing whitespaces
        condition.erase(0, condition.find_first_not_of(" \t"));
        condition.erase(condition.find_last_not_of(" \t") + 1);

        if (find(facts.begin(), facts.end(), condition) == facts.end()) {
            return false;
        }
    }
    return true;
}


// Function to perform forward chaining
vector<string> forwardChaining(const vector<string>& initialFacts, const vector<pair<string, string>>& rules) {
    vector<string> facts = initialFacts;

    cout << "\nNew Facts: " << endl;
    vector<string> newFacts;

    bool newlyDerived = true;
        while (newlyDerived) {
            newlyDerived = false;
            for (const auto& rule : rules) {
                const string& premise = rule.first;
                const string& conclusion = rule.second;

                if (isConditionSatisfied(premise, facts) && find(facts.begin(), facts.end(), conclusion) == facts.end()) {
                    newFacts.push_back(conclusion);
                    facts.push_back(conclusion);
                    newlyDerived = true;
                }
            }
}


    for (const auto& fact : newFacts) {
        cout << fact << endl;
    }

    return facts;
}


int main() {
    // Initialize facts and rules
    vector<string> facts;
    vector<pair<string, string>> rules;

    while (true) {
        cout << "\n-----------------------------------------" << endl;
        cout << "[1] State Facts\n[2] Create Rules\n[3] Generate and Display New Facts\n[4] Done/Exit?";
        cout << "\n-----------------------------------------" << endl;
        string choice;
        getline(cin, choice);

        // To exit
        if (choice == "4") {
            break;
        }

        // Add Facts
        else if (choice == "1") {
            int ctrFact = 1;
            cout << "\n...Adding Fact(s)..." << endl;
            while (true) {
                string factInput;
                cout << "Fact " << ctrFact << ": ";
                getline(cin, factInput);
                if (factInput.empty()) {
                    cout << "Your choice is invalid." << endl;
                    continue;
                }
                if (factInput == "4") {
                    break;
                }
                ctrFact++;
                facts.push_back(factInput);
            }
            cout << "\nYou have added Fact(s)." << endl;
            printFacts(facts);
            printRules(rules);
        }

        // Add Rules
        else if (choice == "2") {
            int ctrRule = 1;
            cout << "\n...Adding Rule(s)..." << endl;
            while (true) {
                string ruleInput;
                cout << "Rule " << ctrRule << ": ";
                getline(cin, ruleInput);
                if (ruleInput == "4") {
                    break;
                }
                if (ruleInput.find("if") != string::npos && ruleInput.find(", then") != string::npos) {
                    size_t ifPos = ruleInput.find("if");
                    size_t thenPos = ruleInput.find(", then");
                    string premise = ruleInput.substr(ifPos + 2, thenPos - ifPos - 2);
                    string conclusion = ruleInput.substr(thenPos + 7);
                    rules.emplace_back(premise, conclusion);
                    ctrRule++;
                } else {
                    cout << "Invalid format. [if {premise}, then {conclusion}" << endl;
                }
            }
            cout << "\nYou have added Rule(s)." << endl;
            printFacts(facts);
            printRules(rules);
        }

        // Generate and display new facts
        else if (choice == "3") {
            printFacts(forwardChaining(facts, rules));
        }
        else {
            cout << "Your choice is invalid." << endl;
        }
    }

    return 0;
}
