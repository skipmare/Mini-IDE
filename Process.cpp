#include "Process.h"

Process::Process(vector<Group *> groups, string inputFileName): groups(std::move(groups)) {
    ifstream inputFile(inputFileName);
    HTMLWriter output("output.html");

    vector<ENFA> enfas = {};
    for(auto group: getGroups()){
        if(group->getRegex().empty()){
            cerr << "No regex for group " + group->getName() << endl;
        }
        RE GroupRegex(group->getRegex());
        ENFA GroupNFA = GroupRegex.toENFA();
        enfas.push_back(GroupNFA);
    }

    if (!inputFile) {
        cerr << "Error: Unable to open file " << inputFileName << endl;
        return;
    }
    // Get word tokens
    string line;
    vector<vector<string>> lines;
    while (getline(inputFile, line)) {
        vector<string> words;
        istringstream stream(line);
        string word;
        while (stream >> word) {
            words.push_back(word);
        }
        lines.push_back(words);
    }
    /*
    vector<string> openbrackets = {"(","{","[",};
    vector<string> closedbrackets = {")","}","]"};
    stack<string> bracketstack;
     */
    for(auto line: lines){
        for (const auto& word: line) {
            /*
            bool isOpenBracket = find(openbrackets.begin(), openbrackets.end(), word) != openbrackets.end();
            bool isClosedBracket = find(closedbrackets.begin(), closedbrackets.end(), word) != closedbrackets.end();
            if(isOpenBracket){
                bracketstack.push(word);
            }
            else if(isClosedBracket){
                if(bracketstack.top() == "(" && word == ")"){
                    bracketstack.pop();
                }
            }
            */
            bool isAccepted = false;
            Group* g = nullptr;
            for(int index = 0; index < enfas.size(); index++) {
                g = getGroups()[index];
                //isAccepted is false by default
                //check if word is accepted
                if (enfas[index].accepts(word) == 1) {
                    isAccepted = true;
                    break;
                }
            }
            if(g) {
                if (isAccepted) {
                    cout << "Accepted " << word << endl;
                    output.writeStyledText(word, g->getColor(), g->getFontWeight());
                    cout << "Printed " << word << " in style" << endl;
                } else {
                    cout << "Not accepted " << word << endl;
                    output.writePlainText(word);
                    cout << "Printer " << word << " plain" << endl;
                }
            }
            else{
                cerr << "No group found" << endl;
            }
            output.saveFile();
        }
        output.addNewline();
    }
    inputFile.close();
}

const vector<Group *> &Process::getGroups() const {
    return groups;
}

void Process::setGroups(const vector<Group *> &groups) {
    this->groups = groups;
}

const string &Process::getRegex() const {
    return regex;
}

void Process::setRegex(const string &regex) {
    Process::regex = regex;
}
