#include "util.hpp"
#pragma once

class Exercise {
public:
    Exercise() : m_name("Default Exercise"), m_units(eUNIT_KG), m_sets(0), m_reps(0), m_percentage(0), m_exerciseType(eExercise_Type_Unassigned), m_weight(0) {};
    Exercise(std::string name, UNIT unit, float sets, float reps, float percentage): m_name(name), m_units(unit), m_sets(sets), m_reps(reps), m_percentage(percentage), m_exerciseType(eExercise_Type_Unassigned), m_weight(0) {}
    Exercise(std::string name,float sets, float reps, float percentage): m_name(name), m_units(eUNIT_KG), m_sets(sets), m_reps(reps), m_percentage(percentage), m_exerciseType(eExercise_Type_Unassigned), m_weight(0) {}


    ~Exercise() {};

    std::string getName() {return m_name;}
    UNIT getUnits() {return m_units;}
    float getSets() {return m_sets;}
    float getReps() {return m_reps;}
    float getPercentage() {return m_percentage;}
    Exercise_Type getExerciseType() {return m_exerciseType;}
    float getWeight() {return m_weight;}
    
    void setName(std::string name) {m_name = name;}
    void setUnits(UNIT units) { m_units = units; }
    void setSets(float value) { m_sets = value;}
    void setReps(float value) { m_reps = value;}
    void setPercentage(float value) { m_percentage = value;}
    void setExerciseType(Exercise_Type exerciseType) { m_exerciseType = exerciseType;}
    void setWeight(float weight) { m_weight = weight;}

    void printExercise();

private:
    std::string m_name;
    UNIT m_units;
    Exercise_Type m_exerciseType;
    float m_sets;
    float m_reps;
    float m_percentage;
    float m_weight;
};

class Day {
public:
    Day() : m_exercises(std::vector<Exercise*>{new Exercise()}), m_idx(0){} 
    Day(Exercise* exercise, int idx): m_exercises(std::vector<Exercise*>{exercise}), m_idx(idx) {}
    Day(std::vector<Exercise*> exercises, int idx): m_exercises(exercises), m_idx(idx) {}

    std::vector<Exercise*> getExercises(){return m_exercises;};
    int getIdx() {return m_idx;}
    void setExercises(std::vector<Exercise*> exercises){m_exercises = exercises;}
    void setIdx(int idx){m_idx = idx;}
    void printDay();

private:
    std::vector<Exercise*> m_exercises;
    int m_idx;
};

class Week {
public:
    Week(): m_trainingDays(std::vector<Day*>{new Day()}), m_idx(0) {};
    Week(Day* day, int idx): m_trainingDays(std::vector<Day*>{day}), m_idx(idx) {};
    Week(std::vector<Day*> days, int idx): m_trainingDays(days), m_idx(idx) {};
    int getIdx() {return m_idx;}
    std::vector<Day*> getDays() {return m_trainingDays;};

    void setDays(std::vector<Day*> days){m_trainingDays = days;}
    void setIdx(int idx){m_idx = idx;}
    void printWeek();


private:
    std::vector<Day*> m_trainingDays;
    int m_idx;
};

class Program {
public:
    Program() : m_name("Default Program"), m_weeks(std::vector<Week*>{new Week()}) {};
    Program(std::string name, std::vector<Week*> weeks) : m_name(name), m_weeks(weeks) {};

    std::string getName() { return m_name; }
    std::vector<Week*> getWeeks() { return m_weeks; }

    void setName(std::string name) {m_name = name;}
    void setWeeks(std::vector<Week*> weeks) { m_weeks = weeks; }
    void printProgram();
private:
    std::string m_name; 
    std::vector<Week*> m_weeks;
};

class Athlete {
public:
    Athlete(): m_name("Default Athlete"), m_bestSquat(0), m_bestFront(0), m_bestSnatch(0), m_bestCNJ(0) {}
    Athlete(std::string name, float squat, float front, float snatch, float cnj): m_name(name), m_bestSquat(squat), m_bestFront(front), m_bestSnatch(snatch), m_bestCNJ(cnj) {}

    std::string getName(){return m_name;}
    float getSquat(){return m_bestSquat;}
    float getFront(){return m_bestFront;}
    float getSnatch(){return m_bestSnatch;}
    float getCNJ(){return m_bestCNJ;}

    void setName(std::string name) {m_name = name;}
    void setSquat(float squat) {m_bestSquat = squat;}
    void setFront(float front) {m_bestFront = front;}
    void setSnatch(float snatch) {m_bestSnatch = snatch;}
    void setCNJ(float cnj) {m_bestCNJ = cnj;}
    
private:
    std::string m_name;
    float m_bestSquat;
    float m_bestFront;
    float m_bestSnatch;
    float m_bestCNJ;
};


void destroyProgram(Program* program, Athlete* athlete);