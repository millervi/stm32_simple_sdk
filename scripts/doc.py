"""Doxygen documentation generator.

NOTE: The script recursively bypasses the folders 
located in the "workspace_directory" directory and 
looks for files with the name "Doxyfile", if the 
file is found, the "doxygen" utility is launched.
"""
import os
import sys
import argparse

def doxygen(workspace_directory):
    """Scanning all folders from the root
    directory and generating documentation.

    Parameters
    ----------
    workspace_directory : str
        Root directory
    """
    found_doxyfile = False
    for root, dirs, files in os.walk(workspace_directory):
        for file in files:
            if file.endswith("Doxyfile"):
                print('-- Doxyfile found in the directory:', os.path.join(root))
                try:
                    os.chdir(root)
                except OSError:
                    print('-- Can\'t change to root directory:', root)
                status = os.system("doxygen Doxyfile")
                if status > 0:
                    sys.exit(status)
                try:
                    os.chdir(workspace_directory)
                except OSError:
                    print('-- Can\'t change to workspace directory:', workspace_directory)
                found_doxyfile = True
    if not found_doxyfile:
        print('-- Doxyfiles is not found')

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
    args = parse_args()
    doxygen(args.root)

if __name__ == '__main__':
    main()