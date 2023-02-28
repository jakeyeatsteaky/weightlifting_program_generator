#pragma once 
#include "program_elements.hpp"

void testExerciseTypes(std::vector<std::string> names, std::vector<int> exercisetypes);

Program* generateProgram(std::vector<Exercise*>& baseTemplate, int weeks, Athlete* athlete, int daysPerWeek);

Exercise_Type identifyExerciseType(std::string name);

std::vector<Exercise*> generateBaseTemplate(const char* pathToJson);

void Assign_Intensities(std::vector<Exercise*>& exercises, Athlete* athlete);

std::vector<Week*> generateWeeklyProgression(std::vector<Day*> Week1, Progression_Protocol progressionProtocol, int numberOfWeeks);

std::vector<Day*> createWeekFromTemplate(std::vector<Day*> week);

void applyProgressionChanges(Exercise* exercise, Progression_Protocol progressionProtocol);

float calculateIncrease(Progression_Protocol progressionProtocol, Exercise* exercise);

std::tuple<int,int,float> changesBasedOnExerciseType(Exercise_Type exType);

void readCoutBufferOpen(Program* program, const char* pathToOutputFile);

void createPropertyTree(const char* pathToJson);
