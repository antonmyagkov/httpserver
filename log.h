#ifndef __LOG1_H__
#define __LOG1_H__

#include <fstream>
#include <string>
#include <stdio.h>

inline std::string NowTime();

enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4};


class Log
{
public:
    virtual ~Log();
public:
   static FILE* GetLog();
protected:
    Log();
    FILE* f;
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

inline FILE*  Log::GetLog() {
  static Log log;
  return log.f;
}

inline Log::Log()
{
  f = fopen("/home/box/final.log", "w+");
  if (!f) {
    throw std::exception();
  }
}


inline Log::~Log()
{
    fclose(f);
}

#endif //__LOG_H__
