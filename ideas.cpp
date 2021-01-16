#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

void listIdeas(std::string pth) {
    std::ifstream ideas (pth, std::ios::in);
    if(ideas.is_open()) {
        std::string line;
        int i = 0;
        while(std::getline(ideas, line)){
            if(i > 0)
                std::cout << i++ << ". " << line << "\n";
            else
                i++;
        }
        ideas.close();
    }

}

void createNewIdea(std::string pth) {
    std::ofstream ideas (pth, std::ios::out | std::ios::app);
    if(ideas.is_open()) {
        std::string line;
        std::cout << "Idea: ";
        std::getline(std::cin, line);
        ideas << "\n" << line;
        ideas.close();
    }
}

void completeIdea(int index, std::string pth) { 
    std::ifstream ideas (pth, std::ios::in);
    std::ostringstream text;
    if(ideas.is_open()) {
        std::string line;
        int i = 0;
        while(std::getline(ideas, line)){
            if(i > 0) {
                if(i != index)
                    text << "\n" << line;
                else
                    text << "\n[COMPLETE] " << line;
            }
            i++;
        }
        ideas.close();
    }
    std::ofstream ideas_out (pth, std::ios::out | std::ios::trunc);
    if(ideas_out.is_open()) {
        std::string str = text.str();
        ideas_out << str;
        ideas_out.close();
    }
    listIdeas(pth);
}

void deleteIdea(int index, std::string pth) {
    std::ifstream ideas (pth, std::ios::in);
    std::ostringstream text;
    if(ideas.is_open()) {
        std::string line;
        int i = 0;
        while(std::getline(ideas, line)){
            if(i > 0) {
                if(i != index)
                    text << "\n" << line;
            }
            i++;
        }
        ideas.close();
    }
    std::ofstream ideas_out (pth, std::ios::out | std::ios::trunc);
    if(ideas_out.is_open()) {
        std::string str = text.str();
        ideas_out << str;
        ideas_out.close();
    }
    listIdeas(pth);
}

void displayHelp() {
    std::cout << "IDEAS -- BY SIMON RENBLAD -- IDEAS" << std::endl;
    std::cout << "ideas: display all ideas" << std::endl;
    std::cout << "ideas new: create a new ideas" << std::endl;
    std::cout << "ideas complete {index}: mark as complete" << std::endl;
    std::cout << "ideas delete {index}: remove idea from list" << std::endl;
}

int main(int argc, char *argv[]) {
    std::string pth = "C:\\Users\\simon\\Documents\\GitHub\\ideas\\ideas.txt"
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(std::string(argv[i]));
    if(argc == 1)
        listIdeas(pth);
    else if(args[0] == "new")
        createNewIdea(pth);
    else if(args[0] == "complete")
        completeIdea(std::stoi(args[1]), pth);
    else if(args[0] == "delete")
        deleteIdea(std::stoi(args[1]), pth);
    else
        displayHelp();
    return 0;
}
