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
#include <sstream>
#include <fstream>

// For Trim
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
// End For Trim

using namespace std;

//***********************//Trim Start******************************
// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}
//******************Trim End*****************************

//*************LogFileIf***************
//Interface for log file
class LogFileIf
{
public:
        virtual string getLine()=0;
        virtual string getTime()=0;
        virtual string getName()=0;
        virtual size_t getLineSize()=0;
};
//*********End LogFileIf***************

//*************AbstractLogFile***************
//Interface for log file
class AbstractLogFile: public LogFileIf
{
protected:
        ifstream ifs;
        string name;

        string line;
        string nextLine;
        bool eofReceived;

        bool isValidTime(string time) {
                size_t index = -1;

                //The pattern "*:*:*.*" will match
                if((index=time.find(':', 0))!=string::npos &&
                   (index=time.find(':', index))!=string::npos &&
                   (index=time.find('.', index))!=string::npos) {
                        return true;
                } else {
                        return false;
                }
        }

        //Check if Second Word is valid time and if valid return
        string getTimeFromString(string line) {
                istringstream is(line.c_str());

                string tmp;
                // Get Second Word
                is >> tmp >> tmp;

                if(isValidTime(tmp)) {
                        return tmp;
                }
                else {
                        string tmp;
                        return tmp;
                }
        }

        string getSingleLine() {
                string line;

                if(nextLine.size()>0) {
                        line=nextLine;
                        nextLine.clear();
                }
                else {
                        try {
                                getline(ifs, line);
                        } catch (ios_base::failure &e) {
                                                eofReceived=true;
                        }
                }
                return line;
        }

        //Add any line without time to the previous line with time
        string getCompleLine() {
                string resLine;

                string tmpLine;
                bool tmpLineHaveTime=false;
                while(true) {
                        tmpLine=getSingleLine();

                        //Trim any white space
                        tmpLine=trim(tmpLine);

                        //No line exists
                        if(tmpLine.size()==0) {
                                if(eofReceived) {
                                        break;
                                }
                                ////Empty line received, Ignore
                        }
                        //Have atleast one line with time
                        else if(getTimeFromString(tmpLine).size()>0 && !tmpLineHaveTime) {
                                tmpLineHaveTime=true;
                                resLine = tmpLine;
                        }
                        //Second line with time received
                        else if(getTimeFromString(tmpLine).size()>0){
                                nextLine=tmpLine;
                                break;
                        }
                        //Line without time received
                        else {
                                resLine = resLine +"\n"+ tmpLine;
                        }
                }
                return resLine;
        }

public:
        AbstractLogFile(string name) {
                eofReceived=false;
                this->name=name;
                ifs.open(name.c_str(), std::ifstream::in);
                ifs.exceptions(ifstream::eofbit);
                line=getCompleLine();
        }

        string getLine() {
                string tmpLine = getCompleLine();

                swap(line, tmpLine);

                return tmpLine;
        }

        string getTime() {
                return getTimeFromString(line);
        }

        size_t getLineSize() {
                return line.size();
        }

        string getName() {
                return name;
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
                LogFileIf *lgf = NULL;
                if(type.compare("-scn")==0) {
                        lgf = new scnLogFile(name);
                }
                else if(type.compare("-wfm")==0) {
                        lgf = new wfmLogFile(name);
                }
                else if(type.compare("-gsl")==0) {
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

                string result;

                // When no log file
                if(logFiles.size()==0) {
                        return result;
                }

                //When one or more log file
                LogFileIf *resLgf = NULL;
                for(unsigned int i=0; i<logFiles.size(); i++) {
                        if(resLgf==NULL) {
                                if(logFiles.at(i)->getTime().size()>0) {
                                        resLgf=logFiles.at(i);
                                }
                                continue;
                        }
                        if(resLgf->getTime()>logFiles.at(i)->getTime()) {
                                resLgf=logFiles.at(i);
                        }
                }

                //Add the fileName to the line
                if(resLgf!=NULL && resLgf->getLineSize()>0) {
                        result=resLgf->getName()+":"+resLgf->getLine();
                }
                return result;
        }

public:
        string getNextLine() {
                return getLineWithMinTime();
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
                        mf.addFile(argv[i+1], argv[i]); i++;
                }
        }
}

int main(int argc, char* argv[]) {
        //Usage:
        //      ./a.out [-<fileType> <file>]... [-<action>]...
        //              fileType:
        //                      -scn
        //                      -wfm
        //                      -gsl
        //              action:
        //                      -print
        //                      -grep
        //                      -stime -etime

        mergeFiles mf;

        //Parse Command Line Arguments
        parseCommandLine(argc, argv, mf);

        for(string line=mf.getNextLine(); line.size()>0; line=mf.getNextLine()) {
                cout<<line<<endl;;
        }

        return 0;
}
