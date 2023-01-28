#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>


class Exercise;
class Week;
class Day;
class Program;

typedef enum {
    eUNIT_KG = 0,
    eUNIT_LBS = 1
} UNIT;

class Exercise {
public:
    Exercise() : m_name("Default Exercise"), m_units(eUNIT_KG), m_sets(0), m_reps(0), m_weight(0) {};
    Exercise(std::string name, UNIT unit, float sets, float reps, float weight): m_name(name), m_units(unit), m_sets(sets), m_reps(reps), m_weight(weight) {}
    ~Exercise() {};

    std::string getName() {return m_name;}
    UNIT getUnits() {return m_units;}
    float getSets() {return m_sets;}
    float getReps() {return m_reps;}
    float getWeight() {return m_weight;}
    
    void setName(std::string name) {m_name = name;}
    void setUnits(UNIT units) { m_units = units; }
    void setSets(float value) { m_sets = value;}
    void setReps(float value) { m_reps = value;}
    void setWeight(float value) { m_weight = value;}

    void printExercise();

private:
    std::string m_name;
    UNIT m_units;
    float m_sets;
    float m_reps;
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

Program* generateProgram(Athlete* athlete, const char* pathToJson, std::vector<float> percentages);

void Assign_Intensity(Exercise* exercise, float percentage);

int main(int argc, char** argv){
    boost::property_tree::ptree pt;
    boost::property_tree::read_json("Files/test.json",pt);

    std::string week1SquatWeight = pt.get<std::string>("Week 1");
    std::cout << week1SquatWeight;

    
    return 0;
}

void Exercise::printExercise(){
    const char* unit;
    const char* name = getName().c_str();
    if(m_units)
        unit = "lbs";
    else
        unit = "kg";
    printf("%s:\t %.0f x %.0f @ %.1f%s\n", name, getSets(), getReps(), getWeight(), unit);
}

void Day::printDay(){
    
    printf("Day: %d\n", getIdx());
    for(Exercise* ex : m_exercises){
        printf("\t\t\t");
        ex->printExercise();
    }
}

void Week::printWeek(){
    printf("Week: %d\n", getIdx());
    for(Day* day : m_trainingDays){
        printf("\t\t");
        day->printDay();
    }
}

void Program::printProgram(){
    const char* name = getName().c_str();
    printf("%s Program: \n", name);
    for(Week* week : m_weeks){
        printf("\t");
        week->printWeek();
    }
}

void Assign_Intensity(Exercise* exercise, float percentage){
    exercise->setWeight(percentage * exercise->getWeight());
}

Program* generateProgram(Athlete* athlete, const char* pathToJson, std::vector<float> percentages){
    std::vector<Week*> weeks_vec = generateWeeks(pathToJson);
    for(Week* week : weeks_vec){
        std::vector<Day*> days_vec = generateDays(week, pathToJson);
    }

    for(Day* days: days_vec){
        std::vector<Exercise*> exercises_vect = generateExercises(week, day, pathToJson);
    }

    Program* generatedProgram = new Program();
    generatedProgram->setName("Generic Program");
    
}
