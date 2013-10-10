xtf
=======

ROS package to support the XTF trajectory file format. C++ and Python libraries are provided.

*While this code is freely licensed (2-clause BSD), it would be nice for you send [us](mailto:calder.pg@gmail.com) an email so we can see who is using this software.*

Repository structure
--------------------
Unlike earlier Catkinized software we have provided, this repository does not contain a Catkin workspace. As we expect that other teams will be well on their way to migrating to ROS Groovy, the difficulties of managing multiple workspaces do not justify the convenience of distributing these packages in their own workspace. As such, you will need to clone this repository inside the `src/` directory of an existing Catkin workspace.

Please note that this software is structured for ROS Groovy+, and is incompatible with ROS Fuerte and earlier. Versions of this software for earlier versions of ROS will not be actively developed or maintained, but historical versions may be available upon request.

This repository consists of 1 package:

1.  `xtf` - Support for the eXtensible Trajectory File (XTF) format for both C++ and Python.

Stability and development status
--------------------------------
`xtf` - Core format specification was completed as of 6/1/2013, all changes since have retained backwards+forwards compatibility (i.e. all files are readable by all historical versions of the library) with the exception of the <extra> tags added in 10/2013 which will be ignored by old versions. The file format specification is currently stable and no changes are planned. No breaking changes are planned for either the C++ or Python APIs, although bugs will be fixed when encountered.

Depencies
---------
1.  Full ROS Groovy installation - on Ubuntu systems: `$ sudo apt-get install ros-groovy-desktop-full`

2.  Libxml++ - on Ubuntu systems: `$ sudo apt-get install libxml++2.6-dev`

Build instructions
------------------
First, clone this repository:
```
$ cd /your/catkin/workspace/src
$ git clone https://github.com/WPI-ARC/xtf.git
$ rospack profile
```

To build all packages in this repository:

```
(in the surrounding Catkin workspace directory)
$ catkin_make
```

To build a particular package in the repository:

```
(in the surrounding Catkin workspace directory)
$ catkin_make --pkg <package name>
```
To use, you must source the workspace:

```
(in the surrounding Catkin workspace directory)
$ source devel/setup.bash
```

Library API
===========
Within reason, the C++ and Python interfaces are designed to be as similar as possible. Obviously, given the significant differences betwen the two languages, a number of important differences exist while achieving equivalent functionality.

Shared API Classes
------------------
1.  Parser - Provided by `XTF::Parser` (C++) and `XTFParser` (Python)

    Constructors:

    `XTF::Parser()` (C++)
    `XTFParser()` (Python)

    Methods:

    `XTF::Trajectory XTF::Parser::ParseTraj(std::string filename)` (C++)
    `XTFTrajectory XTFParser.ParseTraj(string filename)` (Python)

    Provided a valid XTF file, the parser will return a XTF::Trajectory or XTFTrajectory object containing the parsed trajectory. If parsing fails, the parser will throw exceptions.

    `bool XTF::Parser::ExportTraj(XTF::Trajectory traj, std::string filename, bool compact=false)  ` (C++)
    `XTFParser.ExportTraj(XTFTrajectory traj, string filename, bool compact=false)` (Python)

    Provided a XTF::Trajectory or XTFTrajectory, the parser will produce an XTF file at the provided filepath. Parameter `compact` switches between compact XML (no line breaks, no indents) and human-readable XML. If the file cannot be written, the parser will throw exceptions.

2.  Trajectory - Provided by `XTF::Trajectory` (C++) and `XTFTrajectory` (Python)

    Fundamentally, the trajectory classes serve to store header information and a vector/list of states. Beyond this basic structure, very little functionality has been provided on the basis that additional functionality would result in a loss of generality.

    Constructors:

    In C++, four constructors are provided:

    `XTF::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<State> trajectory_data, std::vector<std::string> tags)`

    Creates a new joint-space XTF::Trajectory with existing trajectory data.

    `XTF::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::string root_frame, std::string target_frame, std::vector<std::string> tags)`

    Creates a new joint-space XTF::Trajectory without existing trajectory data.

    `XTF::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<State> trajectory_data, std::vector<std::string> tags)`

    Creates a new pose-space XTF::Trajectory with existing trajectory data.

    `XTF::Trajectory(std::string uid, TRAJTYPES traj_type, TIMINGS timing, DATATYPES data_type, std::string robot, std::string generator, std::vector<std::string> joint_names, std::vector<std::string> tags)`

    Creates a new pose-space XTF::Trajectory without existing trajectory data.

    In Python, as the language lacks overloading, a single constructor is provided:

    `XTFTrajectory(string uid, string traj_type, string timing, string data_type, string robot, string generator, string root_frame, string target_frame, string[] joint_names, XTFState[] trajectory_data, string[] tags)` (Python)

    Not all parameters must be provided - *either* `joint_names` with `data_type="joint"` *or* `root_frame` and `target_frame` with `data_type="pose"` must be provided. All list paramters may be provided as empty lists [].

    Methods:

    Both C++ and Python classes override the "to string" operator (<< in C++, __str__() in Python)

    **The C++ API provides a limited set of functions with no Python equivalent to match a subset of the behavior of std::vector**

    `XTF::Trajectory::push_back(XTF::State val)`

    Wraps the push_back() call of the underlying data structure, with an added safety check to make sure # of joint names in the trajectory and number of joint values in the new state match.

    `XTF::Trajectory::size()`

    Wraps the size() call of the underlying data structure.

    `XTF::Trajectory::at(size_t idx)`

    Wraps the at() call of the underlying data structure.

    `XTF::Trajectory::operator[](size_t idx)`

    Allows direct indexing into the underlying data structure.

    **The Python interface provides no additional functions**

3.  State - Provided by `XTF::State` (C++) and `XTFState` (Python)

    Stores a single state in a trajectory, containing any (or all) of the following:

    - desired position

    - desired velocity

    - desired acceleratiom

    - actual position

    - actual velocity

    - actual acceleration

    - timing (secs + nsecs)

    - sequence

    - "extras" (a fairly free-form key-value way to store additional data in a state, such as a cost value or human observation)

    Constructors:

    `XTF::State(std::vector<double> desiredP, std::vector<double> desiredV, std::vector<double> desiredA, std::vector<double> actualP, std::vector<double> actualV, std::vector<double> actualA, int sequence, timespec timing)` (C++)

    All std::vector parameters must either have zero elements or the same size. Different numbers of elements will result in an exception being thrown.

    `XTFState(float[] desiredP, float[] desiredV, float[] desiredA, float[] actualP, float[] actualV, float[] actualA, int sequence, timing)` (Python)

    All list parameters must either have zero elements or the same size. Different numbers of elements will result in an exception being thrown. Parameter `timing` may either be a list/tuple of (int secs, int nsecs) or (float secs).

    Methods:

    Both C++ and Python classes override the "to string" operator (<< in C++, __str__() in Python)

    **The C++ API provides a single additional function to overcome a limit in std::map**

    `std::vector<std::string> XTF::State::ListExtras()`

    Returns a list of the keys for the "extras" stored in the state. This function is provided because std::map provides no way to query the currently present keys.

    **The Python interface provides no additional functions**

C++ Specific
------------

    `XTF::KeyValue` - Provides a flexible storage container for all supported types of "extras". A given KeyValue object can only be one supported type at a time, and if the type changes, all previous values will be erased.

    Users can query the current type on a KeyValue object and request its value - however, requesting the value as a different type than currently stored will result in an exception being thrown.

Python Specific
---------------

    **None**

    Support for "extras" is provided natively by dictionaries which directly support all value types.
