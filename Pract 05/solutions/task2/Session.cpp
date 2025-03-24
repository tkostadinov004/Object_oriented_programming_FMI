#include "Session.h"

void initSession(Session& session)
{
    session.uid = session.start = session.end = 0;
}

Session readSession(std::ifstream& ifs)
{
    Session session;
    ifs.read((char*)&session, sizeof(session));
    return session;
}

Session* readSessions(std::ifstream& ifs, size_t size)
{
    Session* sessions = new Session[size];
    for (size_t i = 0; i < size; i++)
    {
        sessions[i] = readSession(ifs); // could also be done by ifs.read((char*)&sessions[i], sizeof(sessions[i]);
    }
    return sessions;
}

double getAverage(const Session* sessions, size_t size)
{
    if (!sessions || size == 0)
    {
        return 0;
    }

    unsigned sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum += sessions[i].end - sessions[i].start;
    }
    return sum * 1.0 / size;
}

double getDispersion(const Session* sessions, size_t size)
{
    if (!sessions || size == 0)
    {
        return 0;
    }

    double average = getAverage(sessions, size);

    unsigned sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        int deviation = (sessions[i].end - sessions[i].start) - average;
        sum += (deviation * deviation);
    }
    return sum * 1.0 / size;
}

void printSession(const Session& session)
{
    std::cout << session.uid << ": " << "s" << session.end << " e" << session.end << std::endl;
}

void printValid(const Session* sessions, double dispersion, size_t size)
{
    if (!sessions)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        unsigned duration = sessions[i].end - sessions[i].start;
        if (duration * duration > dispersion)
        {
            printSession(sessions[i]);
        }
    }
}

void countIntervals(std::ifstream& ifs)
{
    size_t size = 0;
    ifs.read((char*)&size, sizeof(size));

    Session* sessions = readSessions(ifs, size);
    double dispersion = getDispersion(sessions, size);

    printValid(sessions, size, dispersion);

    delete[] sessions;
}

void countIntervals(const char* filename)
{
    if (!filename)
    {
        return;
    }

    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open())
    {
        return;
    }

    countIntervals(ifs);
    ifs.close();
}
