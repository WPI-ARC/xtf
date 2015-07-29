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

class KeyValue
{

protected:

    enum TYPES {KV_BOOLEAN, KV_INTEGER, KV_DOUBLE, KV_STRING, KV_BOOLEANLIST, KV_INTEGERLIST, KV_DOUBLELIST, KV_STRINGLIST};
    TYPES type_;
    bool bool_val_;
    double flt_val_;
    long int_val_;
    std::string str_val_;
    std::vector<bool> bool_list_;
    std::vector<double> flt_list_;
    std::vector<long> int_list_;
    std::vector<std::string> str_list_;

    void Zero();

public:

    KeyValue(bool value);

    KeyValue(long value);

    KeyValue(double value);

    KeyValue(std::string value);

    KeyValue(std::vector<bool> value);

    KeyValue(std::vector<long> value);

    KeyValue(std::vector<double> value);

    KeyValue(std::vector<std::string> value);

    KeyValue() {}

    TYPES Type();

    void SetValue(bool value);

    void SetValue(long value);

    void SetValue(double value);

    void SetValue(std::string value);

    void SetValue(std::vector<bool> value);

    void SetValue(std::vector<long> value);

    void SetValue(std::vector<double> value);

    void SetValue(std::vector<std::string> value);

    bool BoolValue();

    long IntegerValue();

    double DoubleValue();

    std::string StringValue();

    std::vector<bool> BoolListValue();

    std::vector<long> IntegerListValue();

    std::vector<double> DoubleListValue();

    std::vector<std::string> StringListValue();

    std::string GetValueString();

    std::string GetTypeString();

};

class State
{
protected:

    void VerifySize(std::vector<double> element);

public:

    std::vector<double> position_desired_;
    std::vector<double> velocity_desired_;
    std::vector<double> acceleration_desired_;
    std::vector<double> position_actual_;
    std::vector<double> velocity_actual_;
    std::vector<double> acceleration_actual_;
    std::map<std::string, KeyValue> extras_;
    int sequence_;
    timespec timing_;
    unsigned int data_length_;

    State(std::vector<double> desiredP, std::vector<double> desiredV, std::vector<double> desiredA, std::vector<double> actualP, std::vector<double> actualV, std::vector<double> actualA, int sequence, timespec timing);

    State() {}

    std::vector<std::string> ListExtras();

};

class Trajectory
{
protected:

public:

    enum TIMINGS {TIMED, UNTIMED};
    enum TRAJTYPES {GENERATED, RECORDED};
    enum DATATYPES {JOINT, POSE};

    std::string robot_;
    std::string generator_;
    std::vector<std::string> joint_names_;
    std::string root_frame_;
    std::string target_frame_;
    std::vector<std::string> tags_;
    std::vector<State> trajectory_;
    std::string uid_;
    TIMINGS timing_;
    TRAJTYPES traj_type_;
    DATATYPES data_type_;

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<State> trajectory_data, std::vector<std::string> tags);

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<State> trajectory_data, std::vector<std::string> tags);

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<std::string> tags);

    Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<std::string> tags);

    Trajectory() {}

    void push_back(State& val);

    State& at(size_t idx);

    State& operator[](size_t idx);

    size_t size();

};

class Parser
{
protected:

    std::vector<bool> ReadBools(std::string strtovec);

    std::vector<long> ReadLongs(std::string strtovec);

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

    Parser() {}

    Trajectory ParseTraj(std::string filename);

    bool ExportTraj(Trajectory trajectory, std::string filename, bool compact=false);

};

}

std::ostream& operator<<(std::ostream& strm, XTF::KeyValue& keyvalue);

std::ostream& operator<<(std::ostream& strm, XTF::State& state);

std::ostream& operator<<(std::ostream& strm, XTF::Trajectory& traj);

#endif // XTF_H
