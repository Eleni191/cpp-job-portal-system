#include <iostream>
#include<string>
#include <fstream>

using namespace std;
//employer section
class employer{
  private:
    string username;
    string password;
    public:
      string firstName;
      string lastName;
      //new employer
    void question() {
        int n;
        cout<<"1.New Employer(Register)"<<endl;
        cout<<"2.Existing Employer(login)"<<endl;
        cin>>n;
        if (n==1) {
            registerEmployer();
        }
        else if (n==2) {
            loginEmployer();
        }
    }
    void registerEmployer(){
        cin.ignore();
      cout<<"Enter Your First Name:"; getline(cin, firstName);
      cout<<"Enter Your last name"; getline(cin, lastName);
      cout<<"Create User-name"; getline(cin, username);
      cout<<"Create Password"; getline(cin, password);

        ofstream outer("employer.txt",ios::app);
      outer<<username<<" "<<password<<endl;
      outer.close();
      cout<<"registration successful"<<endl;
        loginEmployer();
    }
    bool loginEmployer() {
        string u, p, usern, pass;
        cout << "=== Employer login page ===" << endl;
        cout << "Username: ";   cin >> usern;
        cout << "Password: ";   cin >> pass;

        ifstream File("employer.txt");

        // Check if file exists
        if (!File) {
            cout << "Error: Database file not found!" << endl;
            return false;
        }

        while (File >> u >> p) {
            if (u == usern && p == pass) {
                File.close();
                cout << "Login successful!" << endl;
                employerDashboard();
                return true;
            }
        }

        File.close();
        cout << "Login failed: Invalid username or password" << endl;
        return false;
    }
    void employerDashboard() {
        int n;
        cout<<"\n--- EMPLOYER DASHBOARD ---"<<endl;
        cout<<"1.post job"<<endl;
        cout << "2. Read Applications (Review/Eliminate/Interview)" << endl;
        cout << "3. View Selected Applicants for Interview" << endl;
        cout << "4. Review Interview Answers and Hire" << endl;
        cout << "5. Log Out" << endl;
        cin>>n;
        if (n==1)  postJob();
        else if (n==2)   readApp();
        else if (n==3)  viewapplicants();
        else if (n==4) reviewInterviews();
        else if (n==5){ cout<<"log out successfully!";  }
        else {cout<<"invalid option";}
    }

    void postJob(){
        string field, title, company,description;
        double salary;

        cout<<"---post a job---"<<endl;
        cout<<"choose main field"<<endl;
        cout<<"1.Health"<<endl;
        cout<<"2.Technology"<<endl;
        cout<<"3.Design"<<endl;
        cout<<"4.Marketing"<<endl;

        int op;
        cin>>op;
        if(op==1){field="health";}
        else if(op==2){field="tech";}
        else if(op==3){field="design";}
        else{field="marketing";}
        cin.ignore();

        cout<<"enter job title";  getline(cin,title);
        cout<<"enter company name";  getline(cin, company);
        cout<<"enter job description"; getline(cin, description);
        cout<<"enter salary";   cin>>salary;

        ofstream out("jobs.txt", ios::app);
        out << field << "," << title << "," << company << "," << description << "," << salary << endl;
        out.close();
         cout<<"job posted successfully!";
    }

    void readApp() {
        int n;
        cout << "Choose job fields to view applications:" << endl;
        cout << "1. Health"<<endl;
        cout<<"2. Tech"<<endl;
        cout<<"3. Marketing"<<endl;
        cout<<"4. Design" << endl;
        cin >> n;
        cin.ignore();

        string chosenField;
        if(n == 1) chosenField = "health";
        else if(n == 2) chosenField = "tech";
        else if(n == 3) chosenField = "marketing";
        else if(n == 4) chosenField = "design";
        else {
            cout << "Invalid choice" << endl;
            return;
        }

        ifstream app("application.txt");
        string field, position,fn, ln, address, cv;
        bool found = false;
        if(!app) {
            cout << "Error: Could not open application file or no one has applied yet!" << endl;
            return;
        }

        cout << "\n-- Applications for " << chosenField << " --" << endl;
        while (app >> ws &&
               getline(app, field, ',') &&
               getline(app, position, ',') &&
               getline(app, fn, ',') &&
               getline(app, ln, ',') &&
               getline(app, address, ',') &&
               getline(app, cv)) {

            if (field == chosenField) {
                cout << "Applied Position: " << position << endl;
                cout << "Applicant Name: " << fn << " " << ln << endl;
                cout << "Address: " << address << endl;
                cout << "CV (Limited to 500 chars): " << cv << endl;
                cout << "-----------------------------------" << endl;

                char choice;
                cout<<"Do you want to eliminate this applicant? (Y/N)";
                cin>>choice;
                if (choice == 'y' || choice == 'Y') {
                    eliminateApplicant(fn,ln);
                }
                else {
                    char c;
                    cout << "Select for interview? (y/n): ";
                    cin >> c;
                    if (c == 'y' || c == 'Y') {
                        selectForInterview(field, fn, ln, position);
                    }
                }
                cin.ignore();
                found = true;
            }
               }

        if (!found) {
            cout << "No applications found for the " << chosenField << " field." << endl;
        }
        app.close();

    }
    void eliminateApplicant(string fName, string lName) {
        ifstream in("application.txt");
        ofstream temp("temp_app.txt");
        string f, p, fn, ln, a, c;

        while (in >> ws && getline(in, f, ',') && getline(in, p, ',') &&
               getline(in, fn, ',') && getline(in, ln, ',') &&
               getline(in, a, ',') && getline(in, c)) {
            if (!(fn == fName && ln == lName)) {
                temp << f << "," << p << "," << fn << "," << ln << "," << a << "," << c << endl;
            }
               }
        in.close(); temp.close();
        remove("application.txt");
        rename("temp_app.txt", "application.txt");
        cout << "Applicant removed from database." << endl;
    }
    void selectForInterview(string fld, string fn, string ln, string title) {
        ofstream out("interviews.txt", ios::app);
        out << fld << "," << fn << "," << ln << "," << title << endl;
        out.close();
        cout << fn << " has been moved to the interview list!" << endl;
    }
    void viewapplicants() {
        ifstream in("interviews.txt");
        if (!in) {
            cout<<"no applicants have been accepted for interview";
            return;
        }
        string field,fname,lname,title;
        int c=0;
        while (in>>ws&&
            getline(in, field, ',') &&
            getline(in,fname,',')&&
            getline(in,lname, ',')&&
            getline(in,title)) {
            c++;
            cout<<c<<"."<<fname<<" "<<lname<<" position:"<<title<<endl;
        }
        //in.close();

        char h;
        cout<<"do you want to review interview answers? y/n";
        cin>>h;
        if (h=='y') {
            reviewInterviews();
        }
in.close();
        }
    void reviewInterviews() {
        int n;
        string targetField;
        cout << "Which field are you reviewing?\n1. Health\n2. Tech\n3. Marketing\n4. Design" << endl;
        cin >> n;
        if (n == 1) targetField = "health";
        else if (n == 2) targetField = "tech";
        else if (n == 3) targetField = "marketing";
        else if (n == 4) targetField = "design";
        else return;

        ifstream in("interview_answers.txt");
        if (!in) {
            cout << "No interview answers available." << endl;
            return;
        }
        string field,fn, ln, q1, q2, q3, q4;
        bool found=false;
        while (in >> ws &&
               getline(in, field, ',')&&
               getline(in, fn, ',')&&
               getline(in, ln, ',') &&
               getline(in, q1, ',') &&
               getline(in, q2, ',') &&
               getline(in, q3, ',') &&
               getline(in, q4)) {
            if (field == targetField) {
                found= true;
                cout << "\nReviewing: " <<endl;
                cout<<fn << " " << ln<<" [" << field << "]";
                cout << "\nQ1: " << q1 <<endl;
                cout<<"\nQ2: " << q2 <<endl;
                cout<<"\nQ3: " << q3 << endl;
                cout<<"\nQ4: " << q4 << endl;
                cout << "Hire this person? (Y/N): ";
                char choice; cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    ofstream out("hired.txt", ios::app);
                    out <<field<<","<< fn << "," << ln << ",HIRED" << endl;
                    out.close();
                    cout << "Status updated to HIRED." << endl;
                }
            }
        }
        if (!found) cout << "No answers found for the " << targetField << " field." << endl;
        in.close();
    }

};

class employee {
private:
    string username;
    string password;

public:
    string firstName;
    string lastName;
    string address;
    char cv[500];
    string description;
    double expectedSalary;
    string jobFields;

    void choice() {
        int n;
        cout<<"welcome to the employee page"<<endl;
        cout<<"1.new employee(register)"<<endl;
        cout<<"2.existing employee(login)"<<endl;
        cin>>n;
        if (n==1) {
            registerEmployee();
        }
        else if (n==2) {
            loginEmployee();
        }
    }
    void registerEmployee() {
        cout << "Enter first name: ";
        cin >> firstName;
        cout << "Enter last name: ";
        cin >> lastName;
        cout << "Create username: ";
        cin >> username;
        cout << "Create password: ";
        cin >> password;

        ofstream outFile("emp.txt", ios::app);
        outFile << username << " " << password << " " << firstName << " " << lastName << endl;
        outFile.close();

        cout << "Registration successful!" << endl;
        loginEmployee();
    }
//existing employee login page
    bool loginEmployee() {
        string u, p,fn,ln, username1, pass1;
        cout << "\n=== Employee login page ===" << endl;
        cout << "Username: ";
        cin >> username1;
        cout << "Password: ";
        cin >> pass1;

        ifstream inFile("emp.txt");
        while (inFile >> u >> p>>fn>>ln)
    {
            if (u == username1 && p == pass1) {
                inFile.close();
                cout << "Login successful!" << endl;
              employeeDashboard();
                return true;
            }
        }
        inFile.close();
        cout << "Login failed: Invalid username and password" << endl;
        return false;
    }
    void employeeDashboard() {
        int n;
        cout << "1. View Jobs and apply"<<endl;
        cout<<"2. Check Interview Status"<<endl;
        cout<<"3.check employment status"<<endl;
        cout<<"4. Log Out" << endl;
        cin >> n;
        if (n == 1) viewjob();
        else if (n == 2) checkinterviewStatus();
        else if (n ==3)  checkemploymentStatus();
        else if (n==4){ cout<<"log out successfull!";}
        else {cout<<"invalid option";}

    }

   void viewjob() {
        int n;
        cout << "choose job fields" << endl;
        cout << "1.health" << endl;
        cout << "2.tech" << endl;
        cout << "3.marketing" << endl;
        cout << "4.design" << endl;
        cin >> n;

        cin.ignore();

        string chosenField;
        if(n==1){
            chosenField="health";
        }
        else if(n==2){
            chosenField="tech";
        }
        else if(n==3){
            chosenField="marketing";
        }
        else if(n==4){
            chosenField="design";
        }
        else{
            cout<<"invalid choice";
            return;
        }

        ifstream in("jobs.txt");

        if(!in) {
            cout << "No jobs available yet!" << endl;
            return;
        }

        string field, title, company, description, salaryStr;
        bool found = false;

        cout << "--available jobs--" << endl;


        while (getline (in >>ws, field,',')) {
            if (getline(in, title, ',') &&
               getline(in, company, ',') &&
               getline(in, description, ',') &&
               getline(in, salaryStr)){
                if (field == chosenField) {
                    cout << "Title: " << title << endl;
                    cout << "Company: " << company << endl;
                    cout << "Description: " << description << endl;
                    cout << "Salary: " << salaryStr << endl;
                    cout << "-------------------" << endl;
                    found = true;
                }
        }
        }

        if (!found) {
            cout << "No jobs found in this category." << endl;
        }
        in.close();
        char a;
        cout<<"do you want to apply? y/n";
        cin>>a;
        if (a=='y') {
            applyForJob(field,title);
        }

    }
    void applyForJob(string field, string position) {
        string  firstName, lastName, address, cv;

        cout << "=== Job Application Form ===" << endl;
        cout << "Field: "<<endl;
        cin>>field;
        cin.ignore();
        cout << "Position: "<<endl;
        getline(cin, position);
        cout << "First Name: "<<endl;
        getline(cin, firstName);
        cout << "Last Name: "<<endl;
        getline(cin, lastName);
        cout << "Address: "<<endl;
        getline(cin, address);

        cout << "Enter your CV (Max 500 characters): ";
        getline(cin, cv);

        if (cv.length() > 500) {
            cout << "Warning: CV exceeds 500 characters...." << endl;
            cv = cv.substr(0, 500);
        }

        ofstream app("application.txt", ios::app);
        if (app.is_open()) {
            // Order: field, position, first, last, address, cv
            app << field << "," << position << "," << firstName << ","
                << lastName << "," << address << "," << cv << endl;
            app.close();
            cout << "Application sent successfully!" << endl;
        } else {
            cout << "Error: Could not open file." << endl;
        }
    }
    void checkinterviewStatus() {
        string f,fn,ln, position;
        bool found = false;
        ifstream in("interviews.txt");
        if (!in) {
            cout<<"no interview selection have been made yet"<<endl;
            return;
        }
        cout<<"---interview status check---"<<endl;
        while (getline(in >> ws, f, ',') &&
              getline(in, fn, ',') &&
              getline(in, ln, ',') &&
              getline(in, position)) {
            if (fn==firstName && ln==lastName) {
                found=true;
                cout << "Field: " << f << endl;
                cout<<"result: congratulations! you have been selected for an interview"<<position<<endl;
                cout<<"please take the following interview questions for further clarifications :"<<endl;
                in.close();
                takeinterview(f);

               return;
            }

        }
        if (!found) {
            cout<<"your application for"<<" "<<position<<"is not selected."<<endl;
        }

        in.close();

    }
void takeinterview(string field) {
        string q1, q2, q3, q4;
        cout << "--- Online Interview ---" << endl;
        cout << "Welcome " << firstName << ". Please answer the following:" << endl;

        cout << "Q1: Why do you want to work for us? " << endl;
        cin.ignore();
        getline(cin, q1);

        cout << "Q2: What is your greatest professional achievement? " << endl;
        getline(cin, q2);

        cout << "Q3: What is your your expectation about the work load? " << endl;
        getline(cin, q3);

        cout << "Q4: Did our posted salary match with your initial expectation and are u willing to accept it? " << endl;
        getline(cin, q4);
        ofstream out("interview_answers.txt", ios::app);

        out << field<<","<< firstName << "," << lastName << "," << q1 << "," << q2 <<","<<q3<<","<<q4<< endl;
        out.close();

        cout << "Your interview answers have been submitted for review!" << endl;
        cout<<"please check employment status frequently"<<endl;
    }
void checkemploymentStatus() {
            string f,fn, ln, status;
            bool found = false;
            ifstream in("hired.txt");

            if (!in) {
                cout << "Final hiring results have not been posted yet." << endl;
                return;
            }

            while (in >> ws &&
                getline(in, f, ',') &&
                getline(in, fn, ',') &&
                getline(in, ln, ',') &&
                getline(in, status)) {
                if (fn == firstName && ln == lastName) {
                    cout << "FINAL DECISION: YOU ARE " << status << "!" << endl;
                    cout << "CONGRATULATIONS!!!" << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Your final employment status is still: PENDING REVIEW." << endl;
            }
            in.close();
        }

};

int main() {
    employee em;
    employer emp;
    int choice;
    cout<<"---WELCOME TO JOB PORTAL SYSTEM---"<<endl;

    cout << "1. Employee" << endl;
    cout<<"2. Employer" << endl;
    cin >> choice;
    if (choice==1) {
        em.choice();
    }

    else if (choice == 2) {
        emp.question();
    }
}