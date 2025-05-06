// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double exam_scores {};
    int exam_count {};
    double final_scores {};
    double hw_scores {};
    int hw_count {};
    double lw_yes {};
    double lw_no {};
    double lw_count {};
    double reading_yes {};
    double reading_no {};
    double reading_count {};
    double engagement_yes {};
    double engagement_no {};
    double engagement_count {};

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            exam_scores += score;
            exam_count++;
            // TODO(student): process exam score
        } else if (category == "final-exam") {
            final_scores = score;
            // TODO(student): process final score
        } else if (category == "hw") {
            hw_scores += score;
            hw_count++;
            // TODO(student): process hw score
        } else if (category == "lw") {
            if(score >= 50) {
                lw_yes++;
            }
            else {
                lw_no++;
            }
            lw_count++;
            // TODO(student): process lw score
        } else if (category == "reading") {
            if(score == 0 || score < 0) {
                reading_no++;
            }
            else {
                reading_yes++;
            }
            reading_count++;
            // TODO(student): process reading score
        } else if (category == "engagement") {
            if(score == 0 || score < 0) {
                engagement_no++;
            }
            else {
                engagement_yes++;
            }
            engagement_count++;
            // TODO(student): process engagement score
        }else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    double exam_average = 0;
    double hw_average = 0;
    double lw_average = 0;
    double reading = 0;
    double engagement = 0;
    // TODO(student): compute component averages and assign to the above variables
    // exam_average = ???; // etc.
    if (exam_count != 0) {
        exam_average = ((exam_scores + final_scores) / (exam_count + 1));
        if(exam_count == 1) {
            exam_average = ((exam_scores + final_scores) / 3);
        }
    }
    if(exam_average < final_scores) {
        exam_average = final_scores;
    }
    if(exam_average > 100) { 
        exam_average = 100;
    }

    if (hw_count != 0) {
        hw_average = (hw_scores / hw_count);
    }
    if(hw_average > 100) { 
        hw_average = 100;
    }

    if (lw_count != 0) {
        lw_average = (lw_yes / lw_count) * 100;
    }

    if(reading_count != 0){
        reading = (reading_yes / reading_count) * 100;
    }
    reading += 15;
    if(reading > 100) {
        reading = 100;
    }

    if(engagement_count != 0) {
        engagement = (engagement_yes / engagement_count) * 100;
    }
    engagement += 15;
    if(engagement > 100) { 
        engagement = 100;
    }

    // TODO(student): compute weighted total of components
    double weighted_total {};
    weighted_total += exam_average * 0.4;
    weighted_total += hw_average * 0.4;
    weighted_total += lw_average * 0.1;
    weighted_total += reading * 0.05;
    weighted_total += engagement * 0.05;


    // TODO(student): compute final letter grade
    char final_letter_grade {'X'};
    if(weighted_total >= 89.5) {
        final_letter_grade = 'A';
    }
    if(weighted_total < 89.5 && weighted_total >= 79.5) {
        final_letter_grade = 'B';
    }
    if(weighted_total < 79.5 && weighted_total >= 69.5) {
        final_letter_grade = 'C';
    }
    if(weighted_total < 69.5 && weighted_total >= 59.5) {
        final_letter_grade = 'D';
    }
    if(weighted_total <= 59.5) {
        final_letter_grade = 'F';
    }

    // Do not modify print_results since this will not help
    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them
// Even minor changes might cause you to fail test cases for the wrong reasons

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "        exam average: " << exam_average << endl;
    cout << "          hw average: " << hw_average << endl;
    cout << "          lw average: " << lw_average << endl;
    cout << "     reading average: " << reading << endl;
    cout << "  engagement average: " << engagement << endl;
    cout << "  -------------------" << endl;

    cout << "      weighted total: " << weighted_total << endl;

    cout << "  final letter grade: " << final_letter_grade << endl;
}
