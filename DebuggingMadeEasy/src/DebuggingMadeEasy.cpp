//============================================================================
// Name        : DebuggingMadeEasy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>

using namespace std;

//*************LogFileIf***************
//Interface for log file
class LogFileIf
{
public:
	string getLine()=0;
	string getTime()=0;
};
//*********End LogFileIf***************

//*************AbstractLogFile***************
//Interface for log file
class AbstractLogFile: public LogFileIf
{
public:
	string getLine() override {return nullptr;}
	string getTime() override {return nullptr;}
};
//*********End AbstractLogFile***************

//*************scnLogFile***************
//Interface for log file
class scnLogFile: public AbstractLogFile
{
public:
	string getLine() override {return nullptr;}
	string getTime() override {return nullptr;}
};
//*********End scnLogFile***************

//*************wfmLogFile***************
//Interface for log file
class wfmLogFile: public AbstractLogFile
{
public:
	string getLine() override {return nullptr;}
	string getTime() override {return nullptr;}
};
//*********End wfmLogFile***************

//*************gslLogFile***************
//Interface for log file
class gslLogFile: public AbstractLogFile
{
public:
	string getLine() override {return nullptr;}
	string getTime() override {return nullptr;}
};
//*********End gslLogFile***************

//*************MergeFiles**************
//Merge contents based on time stamp
class mergeFiles
{
	vector<LogFileIf> logFiles;

public:
	string getNextLine() {return nullptr;};
};
//*********End MergeFiles**************

int main(int argc, char* argv[]) {
	//Usage:
	//	./a.out [-<fileType> <file>] ... -<action>
	//		fileType:
	//			-scn
	//			-wfm
	//			-gsl
	//		action:
	//			-print
	//			-grep
	//			-stime -etime
	return 0;
}
