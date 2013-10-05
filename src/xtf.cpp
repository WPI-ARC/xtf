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

void State::VerifySize(std::vector<double> element)
{
    if (data_length == 0 && element.size() != 0)
    {
        data_length = element.size();
    }
    else if (element.size() != 0)
    {
        if (data_length != element.size())
        {
            throw std::invalid_argument("Inconsistent trajectory state fields");
        }
    }
}

State::State(std::vector<double> desiredP, std::vector<double> desiredV, std::vector<double> desiredA, std::vector<double> actualP, std::vector<double> actualV, std::vector<double> actualA, int sequence, timespec timing)
{
    data_length = 0;
    VerifySize(desiredP);
    position_desired = desiredP;
    VerifySize(desiredV);
    velocity_desired = desiredV;
    VerifySize(desiredA);
    acceleration_desired = desiredA;
    VerifySize(actualP);
    position_actual = actualP;
    VerifySize(actualV);
    velocity_actual = actualV;
    VerifySize(actualA);
    acceleration_actual = actualA;
    this->sequence = sequence;
    this->timing = timing;
}

std::ostream& operator<<(std::ostream &strm, const State &state)
{
    strm << "State #" << state.sequence << " at:\nsecs: " << state.timing.tv_sec << "\nnsecs: " << state.timing.tv_nsec << "\ndesired:\nposition:";
    for (unsigned int i = 0; i < state.position_desired.size(); i++)
    {
        strm << " " << state.position_desired[i];
    }
    strm << "\nvelocity:";
    for (unsigned int i = 0; i < state.velocity_desired.size(); i++)
    {
        strm << " " << state.velocity_desired[i];
    }
    strm << "\nacceleration:";
    for (unsigned int i = 0; i < state.acceleration_desired.size(); i++)
    {
        strm << " " << state.acceleration_desired[i];
    }
    strm << "\nactual:\nposition:";
    for (unsigned int i = 0; i < state.position_actual.size(); i++)
    {
        strm << " " << state.position_actual[i];
    }
    strm << "\nvelocity:";
    for (unsigned int i = 0; i < state.velocity_actual.size(); i++)
    {
        strm << " " << state.velocity_actual[i];
    }
    strm << "\nacceleration:";
    for (unsigned int i = 0; i < state.acceleration_actual.size(); i++)
    {
        strm << " " << state.acceleration_actual[i];
    }
    return strm;
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<State> trajectory_data, std::vector<std::string> tags)
{
    this->robot = robot;
    this->uid = uid;
    this->generator = generator;
    this->root_frame = root_frame;
    this->target_frame = target_frame;
    this->tags = tags;
    this->trajectory = trajectory_data;
    this->data_type = data_type;
    this->traj_type = traj_type;
    this->timing = timing;
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<State> trajectory_data, std::vector<std::string> tags)
{
    this->robot = robot;
    this->uid = uid;
    this->generator = generator;
    this->joint_names = joint_names;
    this->tags = tags;
    this->trajectory = trajectory_data;
    this->data_type = data_type;
    this->traj_type = traj_type;
    this->timing = timing;
    if (this->joint_names.size() > 0 && this->trajectory.size() > 0)
    {
        if (this->joint_names.size() != this->trajectory[0].data_length)
        {
            throw std::invalid_argument("Inconsistent joint names and joint data");
        }
    }
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<std::string> tags)
{
    this->robot = robot;
    this->uid = uid;
    this->generator = generator;
    this->root_frame = root_frame;
    this->target_frame = target_frame;
    this->tags = tags;
    this->data_type = data_type;
    this->traj_type = traj_type;
    this->timing = timing;
}

Trajectory::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<std::string> tags)
{
    this->robot = robot;
    this->uid = uid;
    this->generator = generator;
    this->joint_names = joint_names;
    this->tags = tags;
    this->data_type = data_type;
    this->traj_type = traj_type;
    this->timing = timing;
    if (this->joint_names.size() > 0 && this->trajectory.size() > 0)
    {
        if (this->joint_names.size() != this->trajectory[0].data_length)
        {
            throw std::invalid_argument("Inconsistent joint names and joint data");
        }
    }
}

std::ostream& operator<<(std::ostream &strm, const Trajectory &traj)
{
    if (traj.traj_type == traj.GENERATED)
    {
        strm << "Generated ";
    }
    else if (traj.traj_type == traj.RECORDED)
    {
        strm << "Recorded ";
    }
    if (traj.data_type == traj.JOINT)
    {
        strm << "Joint ";
    }
    else if (traj.data_type == traj.POSE)
    {
        strm << "Pose ";
    }
    strm << "Trajectory:\nUID: " << traj.uid;
    if (traj.data_type == traj.JOINT)
    {
        strm << "\nJoint names:";
        for (unsigned int i = 0; i < traj.joint_names.size(); i++)
        {
            strm << " " << traj.joint_names[i];
        }
    }
    else if (traj.data_type == traj.POSE)
    {
        strm << "\nRoot frame: " << traj.root_frame;
        strm << "\nTarget frame: " << traj.target_frame;
    }
    strm << "\nRobot: " << traj.robot << "\nGenerator: " << traj.generator;
    if (traj.timing == traj.TIMED)
    {
        strm << "\nTiming: timed";
    }
    else if (traj.timing == traj.UNTIMED)
    {
        strm << "\nTiming: untimed";
    }
    strm << "\nTags:";
    for (unsigned int i = 0; i < traj.tags.size(); i++)
    {
        strm << " " << traj.tags[i];
    }
    strm << "\nTrajectory data:";
    for (unsigned int i = 0; i < traj.trajectory.size(); i++)
    {
        strm << "\n---\n" << traj.trajectory[i];
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
            xmlpp::ContentNode* tagsText = dynamic_cast<xmlpp::ContentNode*>(tagsEL->get_children().front());
            if (tagsText && !tagsText->is_white_space())
            {
                tags = ReadStrings(tagsText->get_content());
            }
            else
            {
                throw std::invalid_argument("XTF file is malformed or otherwise corrupted");
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
                    trajectory_data.push_back(new_state);
                }
                else
                {
                    throw std::invalid_argument("XTF file is malformed or otherwise corrupted");
                }
            }
            // Assemble the trajectory
            if (data_type == Trajectory::JOINT)
            {
                Trajectory new_traj(uid, traj_type, timing, data_type, robot, generator, joint_names, trajectory_data, tags);
                return new_traj;
            }
            else if (data_type == Trajectory::POSE)
            {
                Trajectory new_traj(uid, traj_type, timing, data_type, robot, generator, root_frame, target_frame, trajectory_data, tags);
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
    root->set_attribute("uid", trajectory.uid);
    // - Make info block
    xmlpp::Element* info = root->add_child("info");
    info->set_attribute("robot", trajectory.robot);
    info->set_attribute("generator", trajectory.generator);
    // -- Make type block
    xmlpp::Element* type = info->add_child("type");
    if (trajectory.traj_type == Trajectory::GENERATED)
    {
        type->set_attribute("traj_type", "generated");
    }
    else if (trajectory.traj_type == Trajectory::RECORDED)
    {
        type->set_attribute("traj_type", "recorded");
    }
    else
    {
        throw std::invalid_argument("Trajectory is invalid/inconsistent");
    }
    if (trajectory.timing == Trajectory::TIMED)
    {
        type->set_attribute("timing", "timed");
    }
    else if (trajectory.timing == Trajectory::UNTIMED)
    {
        type->set_attribute("timing", "untimed");
    }
    else
    {
        throw std::invalid_argument("Trajectory is invalid/inconsistent");
    }
    // --- Make type fields
    if (trajectory.data_type == Trajectory::JOINT)
    {
        type->set_attribute("data_type", "joint");
        xmlpp::Element* joint_names = type->add_child("joint_names");
        joint_names->set_child_text(PrettyPrint(trajectory.joint_names));
    }
    else if (trajectory.data_type == Trajectory::POSE)
    {
        type->set_attribute("data_type", "pose");
        xmlpp::Element* root_frame = type->add_child("root_frame");
        root_frame->set_child_text(trajectory.root_frame);
        xmlpp::Element* target_frame = type->add_child("target_frame");
        target_frame->set_child_text(trajectory.target_frame);
    }
    else
    {
        throw std::invalid_argument("Trajectory is invalid/inconsistent");
    }
    // -- Make tag block
    xmlpp::Element* tags = info->add_child("tags");
    tags->set_child_text(PrettyPrint(trajectory.tags));
    // - Make state block
    xmlpp::Element* states = root->add_child("states");
    states->set_attribute("length", PrettyPrint(trajectory.trajectory.size()));
    // -- Make states
    for (unsigned int i = 0; i < trajectory.trajectory.size(); i++)
    {
        State current = trajectory.trajectory[i];
        xmlpp::Element* state = states->add_child("state");
        state->set_attribute("sequence", PrettyPrint(current.sequence));
        state->set_attribute("secs", PrettyPrint(current.timing.tv_sec));
        state->set_attribute("nsecs", PrettyPrint(current.timing.tv_nsec));
        // --- Make state fields
        xmlpp::Element* desired = state->add_child("desired");
        xmlpp::Element* actual = state->add_child("actual");
        // ---- Fill in the state fields
        xmlpp::Element* dp = desired->add_child("position");
        dp->set_child_text(PrettyPrint(current.position_desired));
        xmlpp::Element* dv = desired->add_child("velocity");
        dv->set_child_text(PrettyPrint(current.velocity_desired));
        xmlpp::Element* da = desired->add_child("acceleration");
        da->set_child_text(PrettyPrint(current.acceleration_desired));
        xmlpp::Element* ap = actual->add_child("position");
        ap->set_child_text(PrettyPrint(current.position_actual));
        xmlpp::Element* av = actual->add_child("velocity");
        av->set_child_text(PrettyPrint(current.velocity_actual));
        xmlpp::Element* aa = actual->add_child("acceleration");
        aa->set_child_text(PrettyPrint(current.acceleration_actual));
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

template <typename T>
std::string PrettyPrint(T toprint)
{
    std::ostringstream strm;
    strm << toprint;
    return strm.str();
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
