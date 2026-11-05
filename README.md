# C++ Job Portal Management System

##  About the Project

The **Job Portal Management System** is a console-based application developed using C++. It connects employers and employees through a simple recruitment process.

The system allows employers to publish job vacancies, review applications, select candidates for interviews, evaluate interview answers, and make hiring decisions. Employees can create accounts, explore available jobs, submit applications, participate in interviews, and check their employment status.

##  Features

###  Employer Module
- Employer registration and login.
- Post job vacancies.
- Categorize jobs into Health, Technology, Design, and Marketing.
- View and review job applications.
- Eliminate applicants.
- Select candidates for interviews.
- Review interview answers.
- Hire qualified candidates.

### Employee Module
- Employee registration and login.
- Browse available jobs by category.
- Apply for job vacancies.
- Submit a CV (maximum 500 characters).
- Check interview selection status.
- Answer online interview questions.
- Check final employment status.

##  Technologies Used

- **Programming Language:** C++
- **Concepts:** Object-Oriented Programming (OOP)
- **File Handling:** `fstream`, `ifstream`, `ofstream`
- **Libraries:** `iostream`, `string`, `fstream`

##  Project Structure

```text
cpp-job-portal-system/
│
├── main.cpp
├── README.md
└── .gitignore
```

The application creates text files at runtime to store user accounts, job postings, applications, interview records, and hiring results.

##  How to Run

### Requirements
- A C++ compiler (GCC/G++).
- A terminal or code editor.

### 1. Clone the repository

```bash
git clone https://github.com/YOUR-USERNAME/cpp-job-portal-system.git
```

### 2. Navigate to the project directory

```bash
cd cpp-job-portal-system
```

### 3. Compile the program

```bash
g++ main.cpp -o job_portal
```

### 4. Run the application

**Windows:**
```bash
job_portal.exe
```

**Linux/macOS:**
```bash
./job_portal
```

## Job Categories

1. Health
2. Technology
3. Design
4. Marketing

##  Project Objective

The main objective of this project is to demonstrate the practical application of C++ programming concepts, particularly object-oriented programming, classes, functions, conditional statements, loops, and file handling, by developing a simple recruitment management system.

##  Future Improvements

- Secure password storage.
- Improved input validation and error handling.
- Better user interface.
- Database integration.
- Search and filter functionality.
- More advanced recruitment and application management.


