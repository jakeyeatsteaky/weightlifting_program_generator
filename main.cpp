#include <stdio.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <fstream>
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
    eExercise_Type_Front = 4
    
} Exercise_Type;

typedef enum {
    eProgression_Protocol_Regular = 0,
    eProgression_Protocol_Aggressive = 1,
    eProgression_Protocol_User_Input = 2
} Progression_Protocol;

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

int main(int argc, char** argv){
    const char* pathToJson = "Files/test.json";
    boost::property_tree::ptree pt;
    boost::property_tree::read_json("Files/test.json",pt);
    Athlete* athlete = new Athlete("Jake", 200, 145, 120, 140);
    std::vector<Exercise*> baseTemplate = generateBaseTemplate(pathToJson);
    Assign_Intensities(baseTemplate, athlete);
    int weeks = 4;
    int daysPerWeek = 3;
    Program* program = generateProgram(baseTemplate, weeks, athlete, daysPerWeek);
    readCoutBufferOpen(program, "output.txt");
    return 0;
}

void Exercise::printExercise(){
    const char* unit;
    const char* name = getName().c_str();
    if(m_units)
        unit = "lbs";
    else
        unit = "kg";
    if(getExerciseType() == eExercise_Type_Unassigned)
        std::cout << "\t" << getName() << ": " << getSets() << " x " << getReps() << " @ " << getPercentage() << "%\n";
    else   
        std::cout << "\t" << getName() << ": " << getSets() << " x " << getReps() << " @ " << getWeight()  << unit << " (" << getPercentage() << "%)\n";
}

void Day::printDay(){
    
    std::cout << "Day: " << getIdx() << std::endl;
    for(Exercise* ex : m_exercises){
        std::cout << "\t\t";
        ex->printExercise();
    }
}

void Week::printWeek(){
    std::cout << "Week: " << getIdx() << std::endl;
    for(Day* day : m_trainingDays){
        std::cout << "\t\t";
        day->printDay();
    }
}

void Program::printProgram(){
    const char* name = getName().c_str();
    std::cout << name << " Program: " << std::endl;
    for(Week* week : m_weeks){
        std::cout << "\t";
        week->printWeek();
    }
}

void readCoutBufferOpen(Program* program, const char* pathToOutputFile){
    std::ofstream outfile;
    outfile.open(pathToOutputFile);
    std::streambuf *coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(outfile.rdbuf());
    program->printProgram();
    std::cout.rdbuf(coutbuf);
    outfile.close();
}

void Assign_Intensities(std::vector<Exercise*>& exercises, Athlete* athlete){
   for(Exercise* ex : exercises){
    switch(ex->getExerciseType()){
        case eExercise_Type_Clean:
            ex->setWeight(athlete->getCNJ() * ex->getPercentage());
            break;
        case eExercise_Type_Snatch:
            ex->setWeight(athlete->getSnatch() * ex->getPercentage());
            break;
        case eExercise_Type_Jerk:
            ex->setWeight(athlete->getCNJ() * ex->getPercentage());
            break;
        case eExercise_Type_Front:
            ex->setWeight(athlete->getFront() * ex->getPercentage());
            break;
        case eExercise_Type_Squat:
            ex->setWeight(athlete->getSquat() * ex->getPercentage());
            break;
        default:
            break;
    }
   } 
}

Program* generateProgram(std::vector<Exercise*>& baseTemplate, int weeks, Athlete* athlete, int daysPerWeek){
    // Populate Days
    std::vector<Day*> days {};
    int dayIdx = 1;
    for(int i = 0; i < daysPerWeek*4; i+=4){
        std::vector<Exercise*> dailyExercises = {baseTemplate[0+i], baseTemplate[1+i], baseTemplate[2+i], baseTemplate[3+i]};
        Day* day = new Day(dailyExercises, dayIdx);
        days.push_back(day);
        dayIdx++;
    }

    std::vector<Week*> programWeeks = generateWeeklyProgression(days, eProgression_Protocol_Regular, weeks);

    Program* program = new Program("Some Program", programWeeks);
    return program;
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

    return exercises;

} 

Exercise_Type identifyExerciseType(std::string name){
    for(int i = 0; i < name.size(); i++){
        switch(name[i]){
            case 'F':
                if(name[i+1] == 'r')
                    return eExercise_Type_Front;
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
        Exercise_Type type = identifyExerciseType(n);
        assert(type == exercisetypes[count]);
        count++;
    }
    //test case 1

    // std::vector<std::string> exerciseNames = {
    //     "Squat",
    //     "Snatch",
    //     "Clean",
    //     "Power Clean",
    //     "Power Jerk",
    //     "Jerk",
    //     "blahblah Snatch",
    //     "taco",
    //     "Front Squat",
    //     "Hang Snatch Below the Knee",
    //     "Chicken"
    // };

    // std::vector<int> exercise_types = {0, 1, 2, 4, 4, 3, 1, -1, 0, 1, -1};
    // testExerciseTypes(exerciseNames, exercise_types);

}

std::vector<Week*> generateWeeklyProgression(std::vector<Day*> Week1, Progression_Protocol progressionProtocol, int numberOfWeeks){
    std::vector<Week*> program {};
    int weekCount = 1;
    std::vector<Day*> temp = createWeekFromTemplate(Week1);
    Week* firstWeek = new Week(temp, weekCount);
    program.push_back(firstWeek);

    for(int weekCount = 2; weekCount <= numberOfWeeks; weekCount++){
        for(Day* day : Week1){
            for(Exercise* ex : day->getExercises()){
                applyProgressionChanges(ex, progressionProtocol);
            }
        }
        temp = createWeekFromTemplate(Week1);
        Week* newWeek = new Week(temp, weekCount);
        program.push_back(newWeek);
    }
    return program;
}

std::vector<Day*> createWeekFromTemplate(std::vector<Day*> week){
    std::vector<Day*> day {};
    for(Day* d : week){
        std::vector<Exercise*> exercises = d->getExercises();
        std::vector<Exercise*> newExercises {};
        for(Exercise* ex : exercises){
            std::string name = ex->getName();
            UNIT units = ex->getUnits();
            float sets = ex->getSets();
            float reps = ex->getReps();
            float percentage = ex->getPercentage();
            float weight = ex->getWeight();
            Exercise* newExercise = new Exercise(name, units, sets, reps, percentage);
            newExercise->setWeight(weight);
            newExercise->setExerciseType(identifyExerciseType(name));
            newExercises.push_back(newExercise);
        }
        Day* newDay = new Day(newExercises, d->getIdx());
        day.push_back(newDay);
    }

    return day;
}

void applyProgressionChanges(Exercise* exercise, Progression_Protocol progressionProtocol){
    switch(progressionProtocol){
        case eProgression_Protocol_Regular: {
            std::tuple<int,int,float> changesToApply = changesBasedOnExerciseType(exercise->getExerciseType());
            
            int newSets = exercise->getSets() - std::get<0>(changesToApply);
            int newReps = exercise->getReps() - std::get<1>(changesToApply);
            int newWeight = exercise->getWeight() * std::get<2>(changesToApply);
            exercise->setSets(newSets);
            exercise->setReps(newReps);
            exercise->setWeight(newWeight);
            break;
        }
        case eProgression_Protocol_Aggressive: {
            break; 
        }
        case eProgression_Protocol_User_Input: {
            break;
        }
        default: {
            break;
        }
    }
}

std::tuple<int,int,float> changesBasedOnExerciseType(Exercise_Type exType){
    std::tuple<int,int,float> ret;
    switch(exType){
        case eExercise_Type_Clean:
            ret = std::tuple<int,int,float>(1, 1, 1.04);
            break;
        case eExercise_Type_Squat:
            ret = std::tuple<int,int,float>(1, 2, 1.05);
            break;
        case eExercise_Type_Snatch:
            ret = std::tuple<int,int,float>(1, 1, 1.03);
            break;
        case eExercise_Type_Jerk:
            ret = std::tuple<int,int,float>(1, 1, 1.04);
            break;
        case eExercise_Type_Front:
            ret = std::tuple<int,int,float>(1, 2, 1.04);
            break;
        case eExercise_Type_Unassigned:
            ret = std::tuple<int,int,float>(1, 1, 1.04);
            break;
        default:
            break;
    }
    return ret;
}

float calculateIncrease(Progression_Protocol progressionProtocol, Exercise* exercise){
    if(progressionProtocol == eProgression_Protocol_Regular)
        return (exercise->getWeight() * 0.05f);
    else
        return 0.0f;
}