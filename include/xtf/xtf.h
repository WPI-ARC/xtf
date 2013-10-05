#include "stdlib.h"
#include "stdio.h"
#include <vector>
#include <string>
#include <sstream>
#include "string.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <typeinfo>
#include <libxml++/libxml++.h>

#ifndef XTF_H
#define XTF_H

namespace XTF
{

class State
{
protected:

    void VerifySize(std::vector<double> element);

public:

    std::vector<double> position_desired;
    std::vector<double> velocity_desired;
    std::vector<double> acceleration_desired;
    std::vector<double> position_actual;
    std::vector<double> velocity_actual;
    std::vector<double> acceleration_actual;
    int sequence;
    timespec timing;
    unsigned int data_length;

    State(std::vector<double> desiredP, std::vector<double> desiredV, std::vector<double> desiredA, std::vector<double> actualP, std::vector<double> actualV, std::vector<double> actualA, int sequence, timespec timing);

    ~State()
    {
    }

};

class Trajectory
{
protected:

public:

    enum TIMINGS {TIMED, UNTIMED};
    enum TRAJTYPES {GENERATED, RECORDED};
    enum DATATYPES {JOINT, POSE};

    std::string robot;
    std::string generator;
    std::vector<std::string> joint_names;
    std::string root_frame;
    std::string target_frame;
    std::vector<std::string> tags;
    std::vector<State> trajectory;
    std::string uid;
    TIMINGS timing;
    TRAJTYPES traj_type;
    DATATYPES data_type;

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<State> trajectory_data, std::vector<std::string> tags);

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<State> trajectory_data, std::vector<std::string> tags);

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<std::string> tags);

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<std::string> tags);

    ~Trajectory()
    {
    }

};

class Parser
{
protected:

    std::vector<double> ReadDoubles(std::string strtovec);

    inline std::string CleanNewlines(std::string dirty)
    {
        dirty.erase(std::remove(dirty.begin(), dirty.end(), '\r'), dirty.end());
        dirty.erase(std::remove(dirty.begin(), dirty.end(), '\n'), dirty.end());
        return dirty;
    }

    inline std::string CleanWhitespace(std::string dirty)
    {
        size_t start = dirty.find_first_not_of(' ');
        size_t end = dirty.find_last_not_of(' ');
        size_t length = end - start + 1;
        return dirty.substr(start, length);
    }

    inline std::string CleanString(std::string dirty)
    {
        std::string temp = CleanNewlines(dirty);
        return CleanWhitespace(temp);
    }

    std::vector<std::string> ReadStrings(std::string strtovec);

    std::vector< std::vector<double> > ReadStateFields(xmlpp::Node* field_parent);

public:

    Parser()
    {
        ;
    }

    ~Parser()
    {
    }

    Trajectory ParseTraj(std::string filename);

    bool ExportTraj(Trajectory trajectory, std::string filename, bool compact=true);

};

}

template <typename T>
std::string PrettyPrint(std::vector<T> vectoprint);

template <typename T>
std::string PrettyPrint(T toprint);

std::ostream& operator<<(std::ostream &strm, const XTF::State &state);

std::ostream& operator<<(std::ostream &strm, const XTF::Trajectory &traj);

#endif // XTF_H
