"""Project builder.

NOTE: This script runind generate Makefiles and build project.
"""
import os
import sys
import argparse
import platform

CMAKE_COMAND_FOR_WINDOWS = "cmake -G \"MinGW Makefiles\" .."
CMAKE_COMAND_FOR_LINUX = "cmake -G \"Unix Makefiles\" .."
BUILD_COMAND_FOR_WINDOWS = "mingw32-make -j4"
BUILD_COMAND_FOR_LINUX = "make -j4"

def generate(workspace_directory, path_to_build_directory, generate_command):
    """Generate Makefiles.

    Parameters
    ----------
    workspace_directory : str
        Root directory
    path_to_build_directory : str
        Binary directory
    generate_command : str
        Command of cmake generate Makefiles
    """
    try:
        os.mkdir(path_to_build_directory)
    except OSError:
        if os.path.exists(path_to_build_directory):
            print('-- The build directory is already created')
        else:
            print('-- Creation of the build directory failed')
    try:
        os.chdir(path_to_build_directory)
    except OSError:
        print('-- Can\'t change to build directory: ', path_to_build_directory)
    print('-- Sysytem command:', generate_command)
    status = os.system(generate_command)
    if status > 0:
        sys.exit(status)
    try:
        os.chdir(workspace_directory)
    except OSError:
        print('-- Can\'t change to workspace directory:', workspace_directory)

def build(workspace_directory, path_to_build_directory, build_command):
    """Build project.

    Parameters
    ----------
    workspace_directory : str
        Root directory
    path_to_build_directory : str
        Binary directory
    build_command : str
        Command of make build
    """
    try:
        os.chdir(path_to_build_directory)
    except OSError:
        print('-- Can\'t change to build directory:', path_to_build_directory)
    print('-- Sysytem command:', build_command)
    status = os.system(build_command)
    if status > 0:
        sys.exit(status)
    try:
        os.chdir(workspace_directory)
    except OSError:
        print('-- Can\'t change to workspace directory:', workspace_directory)

def parse_args():
    """Parsing incoming arguments.

    Returns
    -------
    int
        Stream identificator
    argparse
        Data for hendling
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("root", help="-- Workspace directory")
    return parser.parse_args()

def main():
    """Entry point."""
    system = platform.system().lower()
    generate_command = ""
    build_command = ""
    if system == 'windows':
        generate_command = CMAKE_COMAND_FOR_WINDOWS
        build_command = BUILD_COMAND_FOR_WINDOWS
    elif system == 'linux':
        generate_command = "cmake -G \"Unix Makefiles\" .."
        build_command = "make -j4"
    else:
        sys.exit(-1)
    args = parse_args()
    path_to_build_directory = args.root + "/" + "build"
    generate(args.root, path_to_build_directory, generate_command)
    build(args.root, path_to_build_directory, build_command)

if __name__ == "__main__":
    main()