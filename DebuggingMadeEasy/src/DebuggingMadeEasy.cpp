//============================================================================
// Name        : DebuggingMadeEasy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

//*************LogFileIf***************
//Interface for log file
class LogFileIf
{
public:
	virtual string getLine()=0;
	virtual string getTime()=0;
};
//*********End LogFileIf***************

//*************AbstractLogFile***************
//Interface for log file
class AbstractLogFile: public LogFileIf
{
protected:
	string line;
	ifstream ifs;

public:
	AbstractLogFile(string name) {
		cout<<"AbstractLogFile."<<endl;
		ifs.open(name.c_str(), std::ifstream::in);
		getline(ifs, line);
	}

	string getLine() override {
		cout<<"AbstractLogFile:getLine."<<endl;
		if(ifs.eof()) {
			throw "noMoreLogLines";
		}
		string tmpLine = line;
		getline(ifs, line);
		return tmpLine;
	}
	string getTime() override {
		return nullptr;
	}
};
//*********End AbstractLogFile***************

//*************scnLogFile***************
//Interface for log file
class scnLogFile: public AbstractLogFile
{
public:
	scnLogFile(string name): AbstractLogFile(name) {}
};
//*********End scnLogFile***************

//*************wfmLogFile***************
//Interface for log file
class wfmLogFile: public AbstractLogFile
{
public:
	wfmLogFile(string name): AbstractLogFile(name) {}
};
//*********End wfmLogFile***************

//*************gslLogFile***************
//Interface for log file
class gslLogFile: public AbstractLogFile
{
public:
	gslLogFile(string name): AbstractLogFile(name) {}
};
//*********End gslLogFile***************

//*************gslLogFile***************
//Interface for log file
class LogFileFactory
{
public:
	static LogFileIf* getInstance(const string &name, const string &type) {
		LogFileIf *lgf = nullptr;
		if(type=="-scn") {
			lgf = new scnLogFile(name);
		}
		else if(type=="-wfm") {
			lgf = new wfmLogFile(name);
		}
		else if(type=="-gsl") {
			lgf = new gslLogFile(name);
		}
		return lgf;
	}
};
//*********End gslLogFile***************

//*************MergeFiles**************
//Merge contents based on time stamp
class mergeFiles
{
	vector<LogFileIf*> logFiles;

	string getLineWithMinTime() {
		string minTime = logFiles.at(0)->getTime();
		string minLine = logFiles.at(0)->getLine();

		for(LogFileIf *lgf: logFiles) {
			if(minTime>lgf->getTime()) {
				minTime=lgf->getTime();
				minLine=lgf->getLine();
			}
		}
		return minLine;
	}

public:
	string getNextLine() {
		if(logFiles.size()==0) {
			cout<<"throwing noLogFiles"<<endl;
			throw "noLogFiles";
		}
		else if(logFiles.size()==1) {
			cout<<"else if"<<endl;
			return logFiles.at(0)->getLine();
		}
		else {
			cout<<"else"<<endl;
			return getLineWithMinTime();
		}
	}
	void addFile(string name, string type) {
		logFiles.push_back(LogFileFactory::getInstance(name, type));
	}
};
//*********End MergeFiles**************

void parseCommandLine(int argc, char* argv[], mergeFiles &mf)
{
	for(int i=0; i<argc; i++) {
		if(strcmp(argv[i],"-scn")==0 ||
			strcmp(argv[i],"-wfm")==0 ||
			strcmp(argv[i],"-gsl")==0) {
			mf.addFile(argv[i], argv[i+1]); i++;
		}
	}
}

int main(int argc, char* argv[]) {
	//Usage:
	//	./a.out [-<fileType> <file>]... [-<action>]...
	//		fileType:
	//			-scn
	//			-wfm
	//			-gsl
	//		action:
	//			-print
	//			-grep
	//			-stime -etime

	mergeFiles mf;

	//Parse Command Line Arguments
	parseCommandLine(argc, argv, mf);

	for(string line=mf.getNextLine(); 1 ; line=mf.getNextLine()) {
		cout<<"InFor"<<endl;
		cout<<line;
	}

	return 0;
}
