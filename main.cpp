#include <stdio.h>
#include "util.hpp"
#include "program_elements.hpp"
#include "generator.hpp"
#include <fstream>

class Exercise;
class Day;
class Week;
class Program;
class Athlete; 

int main(int argc, char** argv){
    const char* pathToJson = "Files/test.json";
    createPropertyTree(pathToJson);
    
    Athlete* athlete = new Athlete("Jake", 200, 145, 120, 140);
    std::vector<Exercise*> baseTemplate = generateBaseTemplate(pathToJson);
    Assign_Intensities(baseTemplate, athlete);
    int weeks = 4;
    int daysPerWeek = 3;
    Program* program = generateProgram(baseTemplate, weeks, athlete, daysPerWeek);
    
    readCoutBufferOpen(program, "output.txt");
    destroyProgram(program, athlete);
    return 0;
}





