#ifndef DEBUGGER_H
#define DEBUGGER_H

enum class LogLevel {normal, important, warning, error};

class Debugger{

public:
    Debugger();
    ~Debugger();
    void displayLogMessage();
};


#endif