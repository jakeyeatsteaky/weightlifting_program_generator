#include <stdio.h>
#include <iostream>
#include <vector>
#include <cassert>
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

typedef enum {
    eExercise_Type_Unassigned = -1,
    eExercise_Type_Squat = 0,
    eExercise_Type_Snatch = 1,
    eExercise_Type_Clean = 2,
    eExercise_Type_Jerk = 3,
    eExercise_Type_Power = 4
    
} EXERCISE_TYPE;

class Exercise {
public:
    Exercise() : m_name("Default Exercise"), m_units(eUNIT_KG), m_sets(0), m_reps(0), m_percentage(0) {};
    Exercise(std::string name, UNIT unit, float sets, float reps, float percentage): m_name(name), m_units(unit), m_sets(sets), m_reps(reps), m_percentage(percentage) {}
    Exercise(std::string name,float sets, float reps, float percentage): m_name(name), m_units(eUNIT_KG), m_sets(sets), m_reps(reps), m_percentage(percentage), m_exerciseType(eExercise_Type_Unassigned) {}


    ~Exercise() {};

    std::string getName() {return m_name;}
    UNIT getUnits() {return m_units;}
    float getSets() {return m_sets;}
    float getReps() {return m_reps;}
    float getPercentage() {return m_percentage;}
    EXERCISE_TYPE getExerciseType() {return m_exerciseType;}
    
    void setName(std::string name) {m_name = name;}
    void setUnits(UNIT units) { m_units = units; }
    void setSets(float value) { m_sets = value;}
    void setReps(float value) { m_reps = value;}
    void setPercentage(float value) { m_percentage = value;}
    void setExerciseType(EXERCISE_TYPE exerciseType) { m_exerciseType = exerciseType;}

    void printExercise();

private:
    std::string m_name;
    UNIT m_units;
    float m_sets;
    float m_reps;
    float m_percentage;
    EXERCISE_TYPE m_exerciseType;
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

void testExerciseTypes(std::vector<std::string> names, std::vector<int> exercisetypes);
Program* generateProgram(std::vector<Exercise*> baseTemplate, int weeks, Athlete* athlete, int daysPerWeek);
EXERCISE_TYPE identifyExerciseType(std::string name);
std::vector<Exercise*> generateBaseTemplate(const char* pathToJson);
void Assign_Intensity(Exercise* exercise, float percentage);

int main(int argc, char** argv){
    const char* pathToJson = "Files/test.json";
    boost::property_tree::ptree pt;
    boost::property_tree::read_json("Files/test.json",pt);
    
    std::vector<Exercise*> baseTemplate = generateBaseTemplate(pathToJson);
    int weeks = 4;
    int daysPerWeek = 3;
    Athlete* athlete = new Athlete("Jake", 200, 145, 120, 140);
    Program* program = generateProgram(baseTemplate, weeks, athlete, daysPerWeek);
    
    std::vector<std::string> exerciseNames = {
        "Squat",
        "Snatch",
        "Clean",
        "Power Clean",
        "Power Jerk",
        "Jerk",
        "blahblah Snatch",
        "taco",
        "Front Squat",
        "Hang Snatch Below the Knee",
        "Chicken"
    };

    std::vector<int> exercise_types = {0, 1, 2, 4, 4, 3, 1, -1, 0, 1, -1};
    testExerciseTypes(exerciseNames, exercise_types);
    return 0;
}

void Exercise::printExercise(){
    const char* unit;
    const char* name = getName().c_str();
    if(m_units)
        unit = "lbs";
    else
        unit = "kg";
    std::cout << getName() << ": " << getSets() << " x " << getReps() << " @ " << getPercentage() << "%\n";
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
    //exercise->setWeight(percentage * exercise->getWeight());
}

Program* generateProgram(Athlete* athlete, const char* pathToJson, std::vector<float> percentages, UNIT units){
//    std::vector<Exercise*> exercises = generateExercises(const char* pathToJson, )
    return new Program();
}

std::vector<Exercise*> generateBaseTemplate(const char* pathToJson){
    std::vector<Exercise*> exercises {};
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(pathToJson, pt);
    std::vector<std::string> day_names {};
    std::vector<std::string> exercise_names {};
    std::vector<std::pair<std::string, std::string>> values {};
    for(const auto child : pt){
        day_names.push_back(child.first);
    }

    for(int days = 0; days < day_names.size(); days++){
        boost::property_tree::ptree dayTree = pt.get_child(day_names[days]);

        for(const auto& child : dayTree){
            exercise_names.push_back(child.first);
        }

        for(int i = 0; i < exercise_names.size(); i++){
            boost::property_tree::ptree exTree = pt.get_child(day_names[days]+ "." + exercise_names[i]);
            for(const auto& child : exTree){
                values.push_back(std::pair<std::string, std::string>(child.first, child.second.data()));
            }
            std::string name = exercise_names[i];
            float sets = std::stof(values[0].second);
            float reps = std::stof(values[1].second);
            float percentage = std::stof(values[2].second);

            Exercise* exercise = new Exercise(name, sets, reps, percentage);
            exercise->setExerciseType(identifyExerciseType(name));
            exercises.push_back(exercise);
            values.clear();
        }
        exercise_names.clear();
    }

    for(const auto& ex : exercises) {
        ex->printExercise();
    }
    return exercises;

} 

Program* generateProgram(std::vector<Exercise*> baseTemplate, int weeks, Athlete* athlete, int daysPerWeek){
    
}

EXERCISE_TYPE identifyExerciseType(std::string name){
    for(int i = 0; i < name.size(); i++){
        switch(name[i]){
            case 'P':
                if(name[i+1] == 'o')
                    return eExercise_Type_Power;
            case 'S':
                if(name[i+1] == 'q')
                    return eExercise_Type_Squat;
                else if(name[i+1] == 'n')
                    return eExercise_Type_Snatch;
                else    
                    continue;
            case 'C':
                if(name[i+1] == 'l')
                    return eExercise_Type_Clean;
            case 'J':
                if(name[i+1] == 'e')
                    return eExercise_Type_Jerk;
            default:
                continue;    
        }
    }
    return eExercise_Type_Unassigned;
}

void testExerciseTypes(std::vector<std::string> names, std::vector<int> exercisetypes) {
    int count = 0;
    for(std::string n : names){
        EXERCISE_TYPE type = identifyExerciseType(n);
        assert(type == exercisetypes[count]);
        count++;
    }

}