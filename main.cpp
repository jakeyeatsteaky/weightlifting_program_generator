#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
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



void Assign_Intensity(Exercise* exercise, float percentage);

int main(int argc, char** argv){
    Exercise* exercise1 = new Exercise ("Squat", eUNIT_KG, 5, 10, 100);
    Assign_Intensity(exercise1, 0.80f);
    Exercise* exercise2 = new Exercise ("Dead", eUNIT_KG, 5, 10, 100);
    Exercise* exercise3 = new Exercise ("Snatch", eUNIT_KG, 5, 10, 100);
    Exercise* exercise4 = new Exercise ("Clean", eUNIT_KG, 5, 10, 100);
    std::vector<Exercise*> exercises_vec {};
    exercises_vec.push_back(exercise1);
    exercises_vec.push_back(exercise2);
    Day* day1 = new Day(exercises_vec, 1);

    exercises_vec.push_back(exercise3);
    Day* day2 = new Day(exercises_vec, 2);

    exercises_vec.push_back(exercise4);
    Day* day3 = new Day(exercises_vec, 3);

    std::vector<Day*> days_vec {};
    days_vec.push_back(day1);
    days_vec.push_back(day2);
    days_vec.push_back(day3);

    Week* week3 = new Week(days_vec, 1);
    Week* week2 = new Week(days_vec, 2);
    Week* week1 = new Week(days_vec, 3);
    std::vector<Week*> weeks_vec {};
    weeks_vec.push_back(week3);
    weeks_vec.push_back(week1);
    weeks_vec.push_back(week2);

    Program* program1 = new Program("Jacked by Jake", weeks_vec);
    program1->printProgram();
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