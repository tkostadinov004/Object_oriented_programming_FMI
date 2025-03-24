#pragma once
#include <fstream>
#include <iostream>
struct Session
{
    unsigned uid;
    unsigned start;
    unsigned end;
};

void initSession(Session& session);
Session readSession(std::ifstream& ifs);
Session* readSessions(std::ifstream& ifs, size_t size);
double getAverage(const Session* sessions, size_t size);
double getDispersion(const Session* sessions, size_t size);
void printSession(const Session& session);
void printValid(const Session* sessions, double dispersion, size_t size);
void countIntervals(std::ifstream& ifs);
void countIntervals(const char* filename);