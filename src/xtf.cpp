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
#include "xtf/xtf.h"

using namespace XTF;

KeyValue::KeyValue(bool value)
{
    Zero();
    type_ = KV_BOOLEAN;
    bool_val_ = value;
}

KeyValue::KeyValue(long value)
{
    Zero();
    type_ = KV_INTEGER;
    int_val_ = value;
}

KeyValue::KeyValue(double value)
{
    Zero();
    type_ = KV_DOUBLE;
    flt_val_ = value;
}

KeyValue::KeyValue(std::string value)
{
    Zero();
    type_ = KV_STRING;
    str_val_ = value;
}

KeyValue::KeyValue(std::vector<bool> value)
{
    Zero();
    type_ = KV_BOOLEANLIST;
    bool_list_ = value;
}

KeyValue::KeyValue(std::vector<long> value)
{
    Zero();
    type_ = KV_INTEGERLIST;
    int_list_ = value;
}

KeyValue::KeyValue(std::vector<double> value)
{
    Zero();
    type_ = KV_DOUBLELIST;
    flt_list_ = value;
}

KeyValue::KeyValue(std::vector<std::string> value)
{
    Zero();
    type_ = KV_STRINGLIST;
    str_list_ = value;
}

void KeyValue::Zero()
{
    bool_val_ = false;
    flt_val_ = 0.0;
    int_val_ = 0;
    str_val_.clear();
    bool_list_.clear();
    flt_list_.clear();
    int_list_.clear();
    str_list_.clear();
}

KeyValue::TYPES KeyValue::Type()
{
    return type_;
}

void KeyValue::SetValue(bool value)
{
    Zero();
    type_ = KV_BOOLEAN;
    bool_val_ = value;
}

void KeyValue::SetValue(long value)
{
    Zero();
    type_ = KV_INTEGER;
    int_val_ = value;
}

void KeyValue::SetValue(double value)
{
    Zero();
    type_ = KV_DOUBLE;
    flt_val_ = value;
}

void KeyValue::SetValue(std::string value)
{
    Zero();
    type_ = KV_STRING;
    str_val_ = value;
}

void KeyValue::SetValue(std::vector<bool> value)
{
    Zero();
    type_ = KV_BOOLEANLIST;
    bool_list_ = value;
}

void KeyValue::SetValue(std::vector<long> value)
{
    Zero();
    type_ = KV_INTEGERLIST;
    int_list_ = value;
}

void KeyValue::SetValue(std::vector<double> value)
{
    Zero();
    type_ = KV_DOUBLELIST;
    flt_list_ = value;
}

void KeyValue::SetValue(std::vector<std::string> value)
{
    Zero();
    type_ = KV_STRINGLIST;
    str_list_ = value;
}

bool KeyValue::BoolValue()
{
    if (type_ == KV_BOOLEAN)
    {
        return bool_val_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not a BOOLEAN type");
    }
}

long KeyValue::IntegerValue()
{
    if (type_ == KV_INTEGER)
    {
        return int_val_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not an INTEGER type");
    }
}

double KeyValue::DoubleValue()
{
    if (type_ == KV_DOUBLE)
    {
        return flt_val_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not a DOUBLE type");
    }
}

std::string KeyValue::StringValue()
{
    if (type_ == KV_STRING)
    {
        return str_val_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not a STRING type");
    }
}

std::vector<bool> KeyValue::BoolListValue()
{
    if (type_ == KV_BOOLEANLIST)
    {
        return bool_list_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not a BOOLEANLIST type");
    }
}

std::vector<long> KeyValue::IntegerListValue()
{
    if (type_ == KV_INTEGERLIST)
    {
        return int_list_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not an INTEGERLIST type");
    }
}

std::vector<double> KeyValue::DoubleListValue()
{
    if (type_ == KV_DOUBLELIST)
    {
        return flt_list_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not a DOUBLELIST type");
    }
}

std::vector<std::string> KeyValue::StringListValue()
{
    if (type_ == KV_STRINGLIST)
    {
        return str_list_;
    }
    else
    {
        throw std::invalid_argument("KeyValue is not a STRINGLIST type");
    }
}

std::string KeyValue::GetValueString()
{
    std::ostringstream strm;
    if (type_ == KV_BOOLEAN)
    {
        strm << PrettyPrintBool(bool_val_);
    }
    else if (type_ == KV_INTEGER)
    {
        strm << int_val_;
    }
    else if (type_ == KV_DOUBLE)
    {
        strm << flt_val_;
    }
    else if (type_ == KV_STRING)
    {
        strm << str_val_;
    }
    else if (type_ == KV_BOOLEANLIST)
    {
        strm << PrettyPrintBool(bool_list_);
    }
    else if (type_ == KV_INTEGERLIST)
    {
        strm << PrettyPrint(int_list_);
    }
    else if (type_ == KV_DOUBLELIST)
    {
        strm << PrettyPrint(flt_list_);
    }
    else if (type_ == KV_STRINGLIST)
    {
        strm << PrettyPrint(str_list_);
    }
    return strm.str();
}

std::string KeyValue::GetTypeString()
{
    if (type_ == KV_BOOLEAN)
    {
        return std::string("boolean");
    }
    else if (type_ == KV_INTEGER)
    {
        return std::string("integer");
    }
    else if (type_ == KV_DOUBLE)
    {
        return std::string("double");
    }
    else if (type_ == KV_STRING)
    {
        return std::string("string");
    }
    else if (type_ == KV_BOOLEANLIST)
    {
        return std::string("booleanlist");
    }
    else if (type_ == KV_INTEGERLIST)
    {
        return std::string("integerlist");
    }
    else if (type_ == KV_DOUBLELIST)
    {
        return std::string("doublelist");
    }
    else if (type_ == KV_STRINGLIST)
    {
        return std::string("stringlist");
    }
    else
    {
        throw std::invalid_argument("Invalid KeyValue type ID");
    }
}

std::ostream& operator<<(std::ostream& strm, KeyValue& keyvalue)
{
    strm << "type: " << keyvalue.GetTypeString() << " value: " << keyvalue.GetValueString();
    return strm;
}


void State::VerifySize(std::vector<double> element)
{
    if (data_length_ == 0 && element.size() != 0)
    {
        data_length_ = element.size();
    }
    else if (element.size() != 0)
    {
        if (data_length_ != element.size())
        {
            throw std::invalid_argument("Inconsistent trajectory state fields");
        }
    }
}

State::State(std::vector<double> desiredP, std::vector<double> desiredV, std::vector<double> desiredA, std::vector<double> actualP, std::vector<double> actualV, std::vector<double> actualA, int sequence, timespec timing)
{
    data_length_ = 0;
    VerifySize(desiredP);
    position_desired_ = desiredP;
    VerifySize(desiredV);
    velocity_desired_ = desiredV;
    VerifySize(desiredA);
    acceleration_desired_ = desiredA;
    VerifySize(actualP);
    position_actual_ = actualP;
    VerifySize(actualV);
    velocity_actual_ = actualV;
    VerifySize(actualA);
    acceleration_actual_ = actualA;
    sequence_ = sequence;
    timing_ = timing;
}

std::vector<std::string> State::ListExtras()
{
    std::vector<std::string> keys;
    std::map<std::string, KeyValue>::iterator itr;
    for(itr = extras_.begin(); itr != extras_.end(); ++itr)
    {
        std::ostringstream key_stream;
        key_stream << itr->first;
        keys.push_back(key_stream.str());
    }
    return keys;
}

std::ostream& operator<<(std::ostream& strm, State& state)
{
    strm << "State #" << state.sequence_ << " at:\nsecs: " << state.timing_.tv_sec << "\nnsecs: " << state.timing_.tv_nsec << "\ndesired:\nposition:";
    for (unsigned int i = 0; i < state.position_desired_.size(); i++)
    {
        strm << " " << state.position_desired_[i];
    }
    strm << "\nvelocity:";
    for (unsigned int i = 0; i < state.velocity_desired_.size(); i++)
    {
        strm << " " << state.velocity_desired_[i];
    }
    strm << "\nacceleration:";
    for (unsigned int i = 0; i < state.acceleration_desired_.size(); i++)
    {
        strm << " " << state.acceleration_desired_[i];
    }
    strm << "\nactual:\nposition:";
    for (unsigned int i = 0; i < state.position_actual_.size(); i++)
    {
        strm << " " << state.position_actual_[i];
    }
    strm << "\nvelocity:";
    for (unsigned int i = 0; i < state.velocity_actual_.size(); i++)
    {
        strm << " " << state.velocity_actual_[i];
    }
    strm << "\nacceleration:";
    for (unsigned int i = 0; i < state.acceleration_actual_.size(); i++)
    {
        strm << " " << state.acceleration_actual_[i];
    }
    strm << "\nextras:";
    std::map<std::string, KeyValue>::iterator itr;
    for(itr = state.extras_.begin(); itr != state.extras_.end(); ++itr)
    {
        strm << "\nkey: " << itr->first << " " << itr->second;
    }
    return strm;
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<State> trajectory_data, std::vector<std::string> tags)
{
    robot_ = robot;
    uid_ = uid;
    generator_ = generator;
    root_frame_ = root_frame;
    target_frame_ = target_frame;
    tags_ = tags;
    data_type_ = Trajectory::POSE;
    traj_type_ = traj_type;
    timing_ = timing;
    trajectory_ = trajectory_data;
    for (size_t index = 0; index < trajectory_.size(); index++)
    {
        if (trajectory_[index].data_length_ != 7)
        {
            throw std::invalid_argument("Pose data is not 7 doubles [X,Y,Z,X,Y,Z,W]");
        }
    }
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<State> trajectory_data, std::vector<std::string> tags)
{
    robot_ = robot;
    uid_ = uid;
    generator_ = generator;
    joint_names_ = joint_names;
    tags_ = tags;
    data_type_ = Trajectory::JOINT;
    traj_type_ = traj_type;
    timing_ = timing;
    trajectory_ = trajectory_data;
    for (size_t index = 0; index < trajectory_.size(); index++)
    {
        if (trajectory_[index].data_length_ != joint_names_.size())
        {
            throw std::invalid_argument("Inconsistent joint names and joint data");
        }
    }
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<std::string> tags)
{
    robot_ = robot;
    uid_ = uid;
    generator_ = generator;
    root_frame_ = root_frame;
    target_frame_ = target_frame;
    tags_ = tags;
    data_type_ = Trajectory::POSE;
    traj_type_ = traj_type;
    timing_ = timing;
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<std::string> tags)
{
    robot_ = robot;
    uid_ = uid;
    generator_ = generator;
    joint_names_ = joint_names;
    tags_ = tags;
    data_type_ = Trajectory::JOINT;
    traj_type_ = traj_type;
    timing_ = timing;
}

size_t Trajectory::size()
{
    return trajectory_.size();
}

void Trajectory::push_back(State& val)
{
    if (data_type_ == Trajectory::JOINT && (val.data_length_ != joint_names_.size()))
    {
        throw std::invalid_argument("Inconsistent joint names and joint data");
    }
    else if (data_type_ == Trajectory::POSE && (val.data_length_ != 7))
    {
        throw std::invalid_argument("Pose data is not 7 doubles [X,Y,Z,X,Y,Z,W]");
    }
    else
    {
        trajectory_.push_back(val);
    }
}

State& Trajectory::at(size_t idx)
{
    if (idx < trajectory_.size())
    {
        return trajectory_[idx];
    }
    else
    {
        std::ostringstream error_stream;
        error_stream << "Index " << idx << " is out of range";
        throw std::out_of_range(error_stream.str());
    }
}

State& Trajectory::operator[](size_t idx)
{
    if (idx < trajectory_.size())
    {
        return trajectory_[idx];
    }
    else
    {
        std::ostringstream error_stream;
        error_stream << "Index " << idx << " is out of range";
        throw std::out_of_range(error_stream.str());
    }
}

std::ostream& operator<<(std::ostream& strm, Trajectory& traj)
{
    if (traj.traj_type_ == traj.GENERATED)
    {
        strm << "Generated ";
    }
    else if (traj.traj_type_ == traj.RECORDED)
    {
        strm << "Recorded ";
    }
    if (traj.data_type_ == traj.JOINT)
    {
        strm << "Joint ";
    }
    else if (traj.data_type_ == traj.POSE)
    {
        strm << "Pose ";
    }
    strm << "Trajectory:\nUID: " << traj.uid_;
    if (traj.data_type_ == traj.JOINT)
    {
        strm << "\nJoint names:";
        for (unsigned int i = 0; i < traj.joint_names_.size(); i++)
        {
            strm << " " << traj.joint_names_[i];
        }
    }
    else if (traj.data_type_ == traj.POSE)
    {
        strm << "\nRoot frame: " << traj.root_frame_;
        strm << "\nTarget frame: " << traj.target_frame_;
    }
    strm << "\nRobot: " << traj.robot_ << "\nGenerator: " << traj.generator_;
    if (traj.timing_ == traj.TIMED)
    {
        strm << "\nTiming: timed";
    }
    else if (traj.timing_ == traj.UNTIMED)
    {
        strm << "\nTiming: untimed";
    }
    strm << "\nTags:";
    for (unsigned int i = 0; i < traj.tags_.size(); i++)
    {
        strm << " " << traj.tags_[i];
    }
    strm << "\nTrajectory data:";
    for (unsigned int i = 0; i < traj.trajectory_.size(); i++)
    {
        strm << "\n---\n" << traj.trajectory_[i];
    }
    return strm;
}

Trajectory Parser::ParseTraj(std::string filename)
{
    try
    {
        xmlpp::DomParser parser;
        parser.set_substitute_entities();
        parser.parse_file(filename);
        if (parser)
        {
            const xmlpp::Node* root = parser.get_document()->get_root_node();
            /* Read the header data */
            // Get the header nodes
            xmlpp::Node::NodeList info = root->get_children("info");
            xmlpp::Node* infoEL = info.front();
            xmlpp::Node::NodeList type = infoEL->get_children("type");
            xmlpp::Node* typeEL = type.front();
            xmlpp::Node::NodeList tgs = infoEL->get_children("tags");
            xmlpp::Node* tagsEL = tgs.front();
            xmlpp::Node::NodeList rf = typeEL->get_children("root_frame");
            xmlpp::Node* rfEL = rf.front();
            xmlpp::Node::NodeList tf = typeEL->get_children("target_frame");
            xmlpp::Node* tfEL = tf.front();
            xmlpp::Node::NodeList jn = typeEL->get_children("joint_names");
            xmlpp::Node* jnEL = jn.front();
            // Get the trajectory uid
            const xmlpp::Element* rootEL = dynamic_cast<const xmlpp::Element*>(root);
            xmlpp::Attribute* uidAttrib = rootEL->get_attribute("uid");
            std::string uid;
            if (uidAttrib)
            {
                uid = CleanString(uidAttrib->get_value());
            }
            else
            {
                throw std::invalid_argument("XTF file is malformed or otherwise corrupted");
            }
            // Get the info attributes
            xmlpp::Element* infoAttribs = dynamic_cast<xmlpp::Element*>(infoEL);
            xmlpp::Attribute* robotAttrib = infoAttribs->get_attribute("robot");
            xmlpp::Attribute* generatorAttrib = infoAttribs->get_attribute("generator");
            std::string robot;
            std::string generator;
            if (robotAttrib && generatorAttrib)
            {
                robot = CleanString(robotAttrib->get_value());
                generator = CleanString(generatorAttrib->get_value());
            }
            else
            {
                throw std::invalid_argument("XTF file is malformed or otherwise corrupted");
            }
            // Get the type attributes
            xmlpp::Element* typeAttribs = dynamic_cast<xmlpp::Element*>(typeEL);
            xmlpp::Attribute* timingAttrib = typeAttribs->get_attribute("timing");
            xmlpp::Attribute* trajtypeAttrib = typeAttribs->get_attribute("traj_type");
            xmlpp::Attribute* datatypeAttrib = typeAttribs->get_attribute("data_type");
            Trajectory::TIMINGS timing;
            Trajectory::TRAJTYPES traj_type;
            Trajectory::DATATYPES data_type;
            if (timingAttrib && trajtypeAttrib && datatypeAttrib)
            {
                std::string timingstr = CleanString(timingAttrib->get_value());
                std::string trajtypestr = CleanString(trajtypeAttrib->get_value());
                std::string datatypestr = CleanString(datatypeAttrib->get_value());
                if (timingstr.compare("timed") == 0)
                {
                    timing = Trajectory::TIMED;
                }
                else if (timingstr.compare("untimed") == 0)
                {
                    timing = Trajectory::UNTIMED;
                }
                else
                {
                    throw std::invalid_argument("Invalid timing type");
                }
                if (trajtypestr.compare("generated") == 0)
                {
                    traj_type = Trajectory::GENERATED;
                }
                else if (trajtypestr.compare("recorded") == 0)
                {
                    traj_type = Trajectory::RECORDED;
                }
                else
                {
                    throw std::invalid_argument("Invalid trajectory type");
                }
                if (datatypestr.compare("joint") == 0)
                {
                    data_type = Trajectory::JOINT;
                }
                else if (datatypestr.compare("pose") == 0)
                {
                    data_type = Trajectory::POSE;
                }
                else
                {
                    throw std::invalid_argument("Invalid trajectory data type");
                }
            }
            else
            {
                throw std::invalid_argument("XTF file is malformed or otherwise corrupted");
            }
            // Get the type data
            std::string root_frame;
            std::string target_frame;
            std::vector<std::string> joint_names;
            if (data_type == Trajectory::JOINT)
            {
                xmlpp::ContentNode* jointnamesText = dynamic_cast<xmlpp::ContentNode*>(jnEL->get_children().front());
                if (jointnamesText && !jointnamesText->is_white_space())
                {
                    joint_names = ReadStrings(jointnamesText->get_content());
                }
                else
                {
                    throw std::invalid_argument("Type fields do not match type attribute");
                }
            }
            else if (data_type == Trajectory::POSE)
            {
                xmlpp::ContentNode* rootframeText = dynamic_cast<xmlpp::ContentNode*>(rfEL->get_children().front());
                xmlpp::ContentNode* targetframeText = dynamic_cast<xmlpp::ContentNode*>(tfEL->get_children().front());
                if (rootframeText && targetframeText && !rootframeText->is_white_space() && !targetframeText->is_white_space())
                {
                    root_frame = CleanString(rootframeText->get_content());
                    target_frame = CleanString(targetframeText->get_content());
                }
                else
                {
                    throw std::invalid_argument("Type fields do not match type attribute");
                }
            }
            else
            {
                throw std::invalid_argument("XTF file is malformed or otherwise corrupted");
            }
            // Get the tags
            std::vector<std::string> tags;
            // First, we need to check that current file actually has tags
            xmlpp::Node* tagN = tagsEL->get_children().front();
            if (tagN != NULL && (tagsEL->get_children().size() > 0))
            {
                xmlpp::ContentNode* tagsText = dynamic_cast<xmlpp::ContentNode*>(tagN);
                if (tagsText != NULL && !tagsText->is_white_space())
                {
                    tags = ReadStrings(tagsText->get_content());
                }
                else
                {
                    //throw std::invalid_argument("XTF file is malformed or otherwise corrupted");
                }
            }
            ////////////////////////////////////////////////////////////////////////////////
            /* Read the trajectory data */
            // Get the state nodes
            xmlpp::Node::NodeList states = root->get_children("states");
            xmlpp::Node* statesEL = states.front();
            xmlpp::Node::NodeList statelist = statesEL->get_children("state");
            // Run through the state nodes
            std::vector<State> trajectory_data;
            for (xmlpp::Node::NodeList::iterator iter = statelist.begin(); iter != statelist.end(); ++iter)
            {
                // Get the desired data
                xmlpp::Node::NodeList desired = ((xmlpp::Node*)*iter)->get_children("desired");
                xmlpp::Node* desiredEL = desired.front();
                std::vector< std::vector<double> > desiredData = ReadStateFields(desiredEL);
                // Get the actual data
                xmlpp::Node::NodeList actual = ((xmlpp::Node*)*iter)->get_children("actual");
                xmlpp::Node* actualEL = actual.front();
                std::vector< std::vector<double> > actualData = ReadStateFields(actualEL);
                // Get the extras
                std::map<std::string, KeyValue> extras;
                xmlpp::Node::NodeList extralist = ((xmlpp::Node*)*iter)->get_children("extra");
                for (xmlpp::Node::NodeList::iterator xiter = extralist.begin(); xiter != extralist.end(); ++xiter)
                {
                    xmlpp::Element* extraElement = dynamic_cast<xmlpp::Element*>(*xiter);
                    xmlpp::Attribute* nameAttrib = extraElement->get_attribute("name");
                    xmlpp::Attribute* typeAttrib = extraElement->get_attribute("type");
                    xmlpp::Attribute* valueAttrib = extraElement->get_attribute("value");
                    if (nameAttrib && typeAttrib && valueAttrib)
                    {
                        std::string real_type(typeAttrib->get_value());
                        if (real_type.compare("BOOLEAN") == 0 || real_type.compare("boolean") == 0)
                        {
                            bool value = false;
                            std::string value_string(valueAttrib->get_value());
                            if (value_string.compare("TRUE") == 0 || value_string.compare("true") == 0 || value_string.compare("1") == 0)
                            {
                                value = true;
                            }
                            KeyValue extra(value);
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else if (real_type.compare("INTEGER") == 0 || real_type.compare("integer") == 0)
                        {
                            KeyValue extra(atol(valueAttrib->get_value().c_str()));
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else if (real_type.compare("DOUBLE") == 0 || real_type.compare("double") == 0)
                        {
                            KeyValue extra(atof(valueAttrib->get_value().c_str()));
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else if (real_type.compare("STRING") == 0 || real_type.compare("string") == 0)
                        {
                            KeyValue extra(std::string(valueAttrib->get_value()));
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else if (real_type.compare("BOOLEANLIST") == 0 || real_type.compare("booleanlist") == 0)
                        {
                            std::vector<bool> bools = ReadBools(std::string(valueAttrib->get_value()));
                            KeyValue extra(bools);
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else if (real_type.compare("INTEGERLIST") == 0 || real_type.compare("integerlist") == 0)
                        {
                            std::vector<long> longs = ReadLongs(std::string(valueAttrib->get_value()));
                            KeyValue extra(longs);
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else if (real_type.compare("DOUBLELIST") == 0 || real_type.compare("doublelist") == 0)
                        {
                            std::vector<double> doubles = ReadDoubles(std::string(valueAttrib->get_value()));
                            KeyValue extra(doubles);
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else if (real_type.compare("STRINGLIST") == 0 || real_type.compare("stringlist") == 0)
                        {
                            std::vector<std::string> strings = ReadStrings(std::string(valueAttrib->get_value()));
                            KeyValue extra(strings);
                            extras.insert(std::pair<std::string, KeyValue>(std::string(nameAttrib->get_value()), extra));
                        }
                        else
                        {
                            throw std::invalid_argument("XTF file is malformed or otherwise corrupted - a state contains invalid extra type");
                        }
                    }
                    else
                    {
                        throw std::invalid_argument("XTF file is malformed or otherwise corrupted - a state contains invalid extras");
                    }
                }
                // Get the state header data
                xmlpp::Element* nodeElement = dynamic_cast<xmlpp::Element*>(*iter);
                xmlpp::Attribute* sequenceAttrib = nodeElement->get_attribute("sequence");
                xmlpp::Attribute* secsAttrib = nodeElement->get_attribute("secs");
                xmlpp::Attribute* nsecsAttrib = nodeElement->get_attribute("nsecs");
                if (sequenceAttrib && secsAttrib && nsecsAttrib)
                {
                    int sequence = atoi(sequenceAttrib->get_value().c_str());
                    unsigned long secs = atoi(secsAttrib->get_value().c_str());
                    unsigned long nsecs = atoi(nsecsAttrib->get_value().c_str());
                    timespec timing;
                    timing.tv_sec = secs;
                    timing.tv_nsec = nsecs;
                    State new_state(desiredData[0], desiredData[1], desiredData[2], actualData[0], actualData[1], actualData[2], sequence, timing);
                    new_state.extras_ = extras;
                    trajectory_data.push_back(new_state);
                }
                else
                {
                    throw std::invalid_argument("XTF file is malformed or otherwise corrupted - one of the states is invalid");
                }
            }
            // Assemble the trajectory
            if (data_type == Trajectory::JOINT)
            {
                Trajectory new_traj(uid, traj_type, timing, robot, generator, joint_names, trajectory_data, tags);
                return new_traj;
            }
            else if (data_type == Trajectory::POSE)
            {
                Trajectory new_traj(uid, traj_type, timing, robot, generator, root_frame, target_frame, trajectory_data, tags);
                return new_traj;
            }
            else
            {
                std::string error_str("Unable to read XTF file: " + filename);
                throw std::invalid_argument(error_str.c_str());
            }
        }
        else
        {
            std::string error_str("Unable to read XTF file: " + filename);
            throw std::invalid_argument(error_str.c_str());
        }
    }
    catch (xmlpp::internal_error e)
    {
        std::string error_str("Unable to read XTF file (file may not exist): " + filename);
        throw std::invalid_argument(error_str.c_str());
    }
}

bool Parser::ExportTraj(Trajectory trajectory, std::string filename, bool compact)
{
    xmlpp::Document trajXTF;
    // Make root
    xmlpp::Element* root = trajXTF.create_root_node("trajectory");
    root->set_attribute("uid", trajectory.uid_);
    // - Make info block
    xmlpp::Element* info = root->add_child("info");
    info->set_attribute("robot", trajectory.robot_);
    info->set_attribute("generator", trajectory.generator_);
    // -- Make type block
    xmlpp::Element* type = info->add_child("type");
    if (trajectory.traj_type_ == Trajectory::GENERATED)
    {
        type->set_attribute("traj_type", "generated");
    }
    else if (trajectory.traj_type_ == Trajectory::RECORDED)
    {
        type->set_attribute("traj_type", "recorded");
    }
    else
    {
        throw std::invalid_argument("Trajectory is invalid/inconsistent");
    }
    if (trajectory.timing_ == Trajectory::TIMED)
    {
        type->set_attribute("timing", "timed");
    }
    else if (trajectory.timing_ == Trajectory::UNTIMED)
    {
        type->set_attribute("timing", "untimed");
    }
    else
    {
        throw std::invalid_argument("Trajectory is invalid/inconsistent");
    }
    // --- Make type fields
    if (trajectory.data_type_ == Trajectory::JOINT)
    {
        type->set_attribute("data_type", "joint");
        xmlpp::Element* joint_names = type->add_child("joint_names");
        joint_names->set_child_text(PrettyPrint(trajectory.joint_names_));
    }
    else if (trajectory.data_type_ == Trajectory::POSE)
    {
        type->set_attribute("data_type", "pose");
        xmlpp::Element* root_frame = type->add_child("root_frame");
        root_frame->set_child_text(trajectory.root_frame_);
        xmlpp::Element* target_frame = type->add_child("target_frame");
        target_frame->set_child_text(trajectory.target_frame_);
    }
    else
    {
        throw std::invalid_argument("Trajectory is invalid/inconsistent");
    }
    // -- Make tag block
    xmlpp::Element* tags = info->add_child("tags");
    tags->set_child_text(PrettyPrint(trajectory.tags_));
    // - Make state block
    xmlpp::Element* states = root->add_child("states");
    states->set_attribute("length", PrettyPrint(trajectory.trajectory_.size()));
    // -- Make states
    for (unsigned int i = 0; i < trajectory.trajectory_.size(); i++)
    {
        State current = trajectory.trajectory_[i];
        xmlpp::Element* state = states->add_child("state");
        state->set_attribute("sequence", PrettyPrint(current.sequence_));
        state->set_attribute("secs", PrettyPrint(current.timing_.tv_sec));
        state->set_attribute("nsecs", PrettyPrint(current.timing_.tv_nsec));
        // --- Make state fields
        xmlpp::Element* desired = state->add_child("desired");
        xmlpp::Element* actual = state->add_child("actual");
        // ---- Fill in the state fields
        xmlpp::Element* dp = desired->add_child("position");
        dp->set_child_text(PrettyPrint(current.position_desired_));
        xmlpp::Element* dv = desired->add_child("velocity");
        dv->set_child_text(PrettyPrint(current.velocity_desired_));
        xmlpp::Element* da = desired->add_child("acceleration");
        da->set_child_text(PrettyPrint(current.acceleration_desired_));
        xmlpp::Element* ap = actual->add_child("position");
        ap->set_child_text(PrettyPrint(current.position_actual_));
        xmlpp::Element* av = actual->add_child("velocity");
        av->set_child_text(PrettyPrint(current.velocity_actual_));
        xmlpp::Element* aa = actual->add_child("acceleration");
        aa->set_child_text(PrettyPrint(current.acceleration_actual_));
        std::map<std::string, KeyValue>::iterator itr;
        for(itr = current.extras_.begin(); itr != current.extras_.end(); ++itr)
        {
            xmlpp::Element* extra = state->add_child("extra");
            extra->set_attribute("name", itr->first);
            extra->set_attribute("type", itr->second.GetTypeString());
            extra->set_attribute("value", itr->second.GetValueString());
        }
    }
    // Write the xml document to file
    if (compact)
    {
        trajXTF.write_to_file(filename, "utf-8");
    }
    else
    {
        trajXTF.write_to_file_formatted(filename, "utf-8");
    }
    return true;
}

std::string PrettyPrintBool(std::vector<bool> vectoprint)
{
    std::ostringstream strm;
    if (vectoprint.size() > 0)
    {
        strm << PrettyPrintBool(vectoprint[0]);
        for (unsigned int i = 1; i < vectoprint.size(); i++)
        {
            strm << ", " << PrettyPrintBool(vectoprint[i]);
        }
    }
    return strm.str();
}

template <typename T>
std::string PrettyPrint(std::vector<T> vectoprint)
{
    std::ostringstream strm;
    if (vectoprint.size() > 0)
    {
        strm << PrettyPrint(vectoprint[0]);
        for (unsigned int i = 1; i < vectoprint.size(); i++)
        {
            strm << ", " << PrettyPrint(vectoprint[i]);
        }
    }
    return strm.str();
}

std::string PrettyPrintBool(bool toprint)
{
    if (toprint)
    {
        return std::string("true");
    }
    else
    {
        return std::string("false");
    }
}

template <typename T>
std::string PrettyPrint(T toprint)
{
    std::ostringstream strm;
    strm << toprint;
    return strm.str();
}

std::vector<bool> Parser::ReadBools(std::string strtovec)
{
    std::vector<std::string> elements = Parser::ReadStrings(strtovec);
    std::vector<bool> bools;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        bool temp = false;
        if (elements[i].compare("TRUE") == 0 || elements[i].compare("true") == 0 || elements[i].compare("1") == 0)
        {
            temp = true;
        }
        bools.push_back(temp);
    }
    return bools;
}

std::vector<long> Parser::ReadLongs(std::string strtovec)
{
    std::vector<std::string> elements = Parser::ReadStrings(strtovec);
    std::vector<long> longs;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        long temp = atol(elements[i].c_str());
        longs.push_back(temp);
    }
    return longs;
}

std::vector<double> Parser::ReadDoubles(std::string strtovec)
{
    std::vector<std::string> elements = Parser::ReadStrings(strtovec);
    std::vector<double> doubles;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        double temp = atof(elements[i].c_str());
        doubles.push_back(temp);
    }
    return doubles;
}

std::vector<std::string> Parser::ReadStrings(std::string strtovec)
{
    std::string temp = CleanString(strtovec);
    std::vector<std::string> elements;
    std::stringstream ss(temp);
    std::string item;
    char delim = ',';
    while (std::getline(ss, item, delim))
    {
        std::string cleaned = CleanString(item);
        elements.push_back(cleaned);
    }
    return elements;
}

std::vector< std::vector<double> > Parser::ReadStateFields(xmlpp::Node* field_parent)
{
    // Get the basic nodes
    xmlpp::Node::NodeList position = field_parent->get_children("position");
    xmlpp::Node* positionEL = position.front();
    xmlpp::Node::NodeList velocity = field_parent->get_children("velocity");
    xmlpp::Node* velocityEL = velocity.front();
    xmlpp::Node::NodeList acceleration = field_parent->get_children("acceleration");
    xmlpp::Node* accelerationEL = acceleration.front();
    // Intermediate step
    xmlpp::Node* posN = positionEL->get_children().front();
    xmlpp::Node* velN = velocityEL->get_children().front();
    xmlpp::Node* accelN = accelerationEL->get_children().front();
    // Make the storage containers
    std::vector<double> position_data;
    std::vector<double> velocity_data;
    std::vector<double> acceleration_data;
    // Attempt to populate - NOTE: we check both if the node is NULL and if it came from an empty container because libxml++ does not necessarily return NULL from empty NodeLists!
    if (posN != NULL && (positionEL->get_children().size() > 0))
    {
        xmlpp::ContentNode* positionText = dynamic_cast<xmlpp::ContentNode*>(posN);
        if (positionText != NULL && !positionText->is_white_space())
        {
            position_data = ReadDoubles(positionText->get_content());
        }
    }
    if (velN != NULL && (velocityEL->get_children().size() > 0))
    {
        xmlpp::ContentNode* velocityText = dynamic_cast<xmlpp::ContentNode*>(velN);
        if (velocityText != NULL && !velocityText->is_white_space())
        {
            velocity_data = ReadDoubles(velocityText->get_content());
        }
    }
    if (accelN != NULL && (accelerationEL->get_children().size() > 0))
    {
        xmlpp::ContentNode* accelerationText = dynamic_cast<xmlpp::ContentNode*>(accelN);
        if (accelerationText != NULL && !accelerationText->is_white_space())
        {
            acceleration_data = ReadDoubles(accelerationText->get_content());
        }
    }
    // Pack everything together for return
    std::vector< std::vector<double> > data;
    data.push_back(position_data);
    data.push_back(velocity_data);
    data.push_back(acceleration_data);
    return data;
}
