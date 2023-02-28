#include "generator.hpp"
#include <cassert>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

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
    for(Exercise* ex : baseTemplate){
        delete ex;
    }
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

void createPropertyTree(const char* pathToJson){
    boost::property_tree::ptree pt;
    boost::property_tree::read_json("Files/test.json",pt);
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
