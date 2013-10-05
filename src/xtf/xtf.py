#!/usr/bin/python

#################################################
#                                               #
#   Calder Phillips-Grafflin - WPI/ARC Lab      #
#                                               #
#   Reference Python implementation of the      #
#   eXtensible Trajectory File format.          #
#                                               #
#################################################

import xml.etree.ElementTree as ET
import re

class XTFState:

    def __init__(self, desiredP, desiredV, desiredA, actualP, actualV, actualA, sequence, timing):
        self._data_length = 0
        self._verify_size(desiredP)
        self.position_desired = desiredP
        self._verify_size(desiredV)
        self.velocity_desired = desiredV
        self._verify_size(desiredA)
        self.acceleration_desired = desiredA
        self._verify_size(actualP)
        self.position_actual = actualP
        self._verify_size(actualV)
        self.velocity_actual = actualV
        self._verify_size(actualA)
        self.acceleration_actual = actualA
        self.sequence = sequence
        if (len(timing) == 2):
            self.secs = timing[0]
            self.nsecs = timing[1]
        else:
            raise AttributeError("Incorrect format for timing")

    def _verify_size(self, element):
        if (self._data_length == 0 and len(element) != 0):
            self._data_length = len(element)
        elif (len(element) != 0):
            if (self._data_length != len(element)):
                raise AttributeError("Inconsistent trajectory state fields")

    def __str__(self):
        state_str = "State #" + str(self.sequence) + " at:\nsecs: " + str(self.secs) + "\nnsecs: " + str(self.nsecs)
        state_str += "\ndesired:"
        state_str += "\nposition: " + str(self.position_desired)
        state_str += "\nvelocity: " + str(self.velocity_desired)
        state_str += "\nacceleration: " + str(self.acceleration_desired)
        state_str += "\nactual:"
        state_str += "\nposition: " + str(self.position_actual)
        state_str += "\nvelocity: " + str(self.velocity_actual)
        state_str += "\nacceleration: " + str(self.acceleration_actual)
        return state_str

class XTFTrajectory:

    JOINT = 'joint'
    POSE = 'pose'
    GENERATED = 'generated'
    RECORDED = 'recorded'

    def __init__(self, uid, traj_type, timing, data_type, robot, generator, root_frame, target_frame, joint_names, trajectory_data, tags):
        if (traj_type == self.GENERATED or traj_type == self.RECORDED):
            self.traj_type = traj_type
        else:
            raise AttributeError("Invalid trajectory type: " + str(traj_type))
        if (timing == "timed" or timing == "untimed"):
            self.timed = timing
        else:
            raise AttributeError("Invalid trajectory timing type: " + str(timing))
        if (data_type == self.JOINT or data_type == self.POSE):
            self.data_type = data_type
        else:
            raise AttributeError("Invalid trajectory data type: " + str(data_type))
        self.robot = robot
        self.uid = uid
        self.generator = generator
        if (self.data_type == self.JOINT):
            self.root_frame = None
            self.target_frame = None
            if (joint_names is not None):
                self.joint_names = joint_names
            else:
                raise AttributeError("No joint names provided for joint-space trajectory")
        elif (self.data_type == self.POSE):
            self.joint_names = None
            if (root_frame is not None):
                self.root_frame = root_frame
            else:
                raise AttributeError("No root frame provided for pose-space trajectory")
            if (target_frame is not None):
                self.target_frame = target_frame
            else:
                raise AttributeError("No target frame provided for pose-space trajectory")
        if (self.data_type == self.JOINT and trajectory_data[0]._data_length == len(self.joint_names)):
            self.trajectory = trajectory_data
        elif (self.data_type == self.POSE):
            self.trajectory = trajectory_data
        else:
            raise AttributeError("Inconsistent trajectory type and data")
        if (tags is None):
            self.tags = []
        else:
            self.tags = tags

    def __str__(self):
        traj_str = ""
        if (self.traj_type == self.GENERATED):
            traj_str += "Generated"
        elif (self.traj_type == self.RECORDED):
            traj_str += "Recorded"
        traj_str += " "
        if (self.data_type == self.JOINT):
            traj_str += "Joint"
        elif (self.data_type == self.POSE):
            traj_str += "Pose"
        traj_str += " Trajectory:"
        traj_str += "\nUID: " + str(self.uid)
        if (self.data_type == self.JOINT):
            traj_str += "\nJoints: " + str(self.joint_names)
        elif (self.data_type == self.POSE):
            traj_str += "\nRoot frame: " + str(self.root_frame)
            traj_str += "\nTarget frame: " + str(self.target_frame)
        traj_str += "\nRobot: " + str(self.robot)
        traj_str += "\nGenerator: " + str(self.generator)
        traj_str += "\nTiming: " + str(self.timed)
        traj_str += "\nTags: " + str(self.tags)
        traj_str += "\nTrajectory data:"
        for state in self.trajectory:
            traj_str += "\n---\n" + str(state)
        return traj_str

class XTFParser:

    def __init__(self):
        self.decimal_regex = re.compile(r'[^\d.-]+')

    def _gettypeinfo(self, trajectory):
        typetext = ""
        if (trajectory.traj_type == trajectory.GENERATED):
            typetext = "generated"
        elif (trajectory.traj_type == trajectory.RECORDED):
            typetext = "recorded"
        datatext = ""
        if (trajectory.data_type == trajectory.JOINT):
            datatext = "joint"
        elif (trajectory.data_type == trajectory.POSE):
            datatext = "pose"
        timingtext = ""
        if (trajectory.timed == "timed"):
            timingtext = "timed"
        else:
            timingtext = "untimed"
        return [typetext, datatext, timingtext]

    def _prettyprint(self, listtoprint):
        basestr = ""
        for item in listtoprint:
            basestr += (", " + str(item))
        basestr = basestr.lstrip(", ")
        return basestr

    def _readfloats(self, strtolist):
        if (strtolist is None):
            return []
        strtolist = strtolist.strip("\n")
        chunks = strtolist.split(", ")
        floated = []
        for chunk in chunks:
            try:
                chunk = self.decimal_regex.sub('', chunk)
                floated.append(float(chunk))
            except:
                pass
        return floated

    def _readstrings(self, strtolist):
        if (strtolist is None):
            return []
        strtolist = strtolist.strip("\n")
        raw_chunks = strtolist.split(", ")
        cleaner_chunks = []
        for chunk in raw_chunks:
            cleaner_chunks.append(chunk.strip(" ").strip("\n"))
        return cleaner_chunks

    def ParseTraj(self, filename):
        tree = ET.parse(filename)
        # Read in the header information
        root = tree.getroot()
        uid = root.attrib['uid']
        infoEL = tree.find("info")
        robot = infoEL.attrib['robot']
        generator = infoEL.attrib['generator']
        typeEL = infoEL.find("type")
        traj_type = typeEL.attrib["traj_type"]
        timing = typeEL.attrib["timing"]
        data_type = typeEL.attrib["data_type"]
        root_frame = None
        target_frame = None
        joint_names = None
        if (data_type == "pose"):
            root_frame = self._readstrings(typeEL.find("root_frame").text)[0]
            target_frame = self._readstrings(typeEL.find("target_frame").text)[0]
        elif (data_type == "joint"):
            joint_names = self._readstrings(typeEL.find("joint_names").text)
        tags = self._readstrings(infoEL.find("tags").text)
        # Read in the state information
        states = tree.find("states")
        num_states = states.attrib['length']
        trajectory_data = []
        state_list = states.findall("state")
        for state in state_list:
            sequence = state.attrib['sequence']
            secs = int(state.attrib['secs'])
            nsecs = int(state.attrib['nsecs'])
            dEL = state.find("desired")
            desiredP = self._readfloats(dEL.find("position").text)
            desiredV = self._readfloats(dEL.find("velocity").text)
            desiredA = self._readfloats(dEL.find("acceleration").text)
            aEL = state.find("actual")
            actualP = self._readfloats(aEL.find("position").text)
            actualV = self._readfloats(aEL.find("velocity").text)
            actualA = self._readfloats(aEL.find("acceleration").text)
            state_timing = (secs, nsecs)
            new_state = XTFState(desiredP, desiredV, desiredA, actualP, actualV, actualA, sequence, state_timing)
            trajectory_data.append(new_state)
        # Sanity check
        assert(int(num_states) == len(trajectory_data))
        new_traj = XTFTrajectory(uid, traj_type, timing, data_type, robot, generator, root_frame, target_frame, joint_names, trajectory_data, tags)
        return new_traj

    def ExportTraj(self, trajectory, filename, compact=True):
        trajEL = ET.Element("trajectory", {"uid":trajectory.uid})
        infoEL = ET.SubElement(trajEL, "info", {"robot":trajectory.robot, "generator":trajectory.generator})
        [typetext, datatext, timingtext] = self._gettypeinfo(trajectory)
        typeEL = ET.SubElement(infoEL, "type", {"traj_type":typetext, "timing":timingtext, "data_type":datatext})
        if (trajectory.data_type == trajectory.POSE):
            rfEL = ET.SubElement(typeEL, "root_frame")
            rfEL.text = trajectory.root_frame
            tfEL = ET.SubElement(typeEL, "target_frame")
            tfEL.text = trajectory.target_frame
        elif (trajectory.data_type == trajectory.JOINT):
            jnEL = ET.SubElement(typeEL, "joint_names")
            jnEL.text = self._prettyprint(trajectory.joint_names)
        tagsEL = ET.SubElement(infoEL, "tags")
        tagsEL.text = self._prettyprint(trajectory.tags)
        statesEL = ET.SubElement(trajEL, "states", {"length":str(len(trajectory.trajectory))})
        for state in trajectory.trajectory:
            stateEL = ET.SubElement(statesEL, "state", {"sequence":str(state.sequence), "secs":str(state.secs), "nsecs":str(state.nsecs)})
            desiredEL = ET.SubElement(stateEL, "desired")
            dpEL = ET.SubElement(desiredEL, "position")
            dpEL.text = self._prettyprint(state.position_desired)
            dvEL = ET.SubElement(desiredEL, "velocity")
            dvEL.text = self._prettyprint(state.velocity_desired)
            daEL = ET.SubElement(desiredEL, "acceleration")
            daEL.text = self._prettyprint(state.acceleration_desired)
            actualEL = ET.SubElement(stateEL, "actual")
            apEL = ET.SubElement(actualEL, "position")
            apEL.text = self._prettyprint(state.position_actual)
            avEL = ET.SubElement(actualEL, "velocity")
            avEL.text = self._prettyprint(state.velocity_actual)
            aaEL = ET.SubElement(actualEL, "acceleration")
            aaEL.text = self._prettyprint(state.acceleration_actual)
        tree = ET.ElementTree(trajEL)
        if (compact):
            tree.write(filename, encoding="utf-8", xml_declaration=True)
        else:
            tree.write(filename, encoding="utf-8", xml_declaration=True)

if __name__ == "__main__":
    print "Testing XTF reference library [Python]"
    print "Making reader..."
    reader = XTFParser()
    print "...done"
    print "Reading reference pose trajectory file..."
    pose_example = reader.ParseTraj("pose_recorded.xtf")
    print "...done"
    print "Printing trajectory to the screen..."
    print pose_example
    print "...done"
    print "Saving pose_example..."
    reader.ExportTraj(pose_example, "pose_recorded_copy.xtf")
    print "...done"
    print "Reading copy back in..."
    pose_copy = reader.ParseTraj("pose_recorded_copy.xtf")
    print "...done"
    print "Printing copy to the screen..."
    print pose_copy
    print "...done"
    print "ALL PASS --- exiting..."
