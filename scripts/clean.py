"""Workspace cleaner.

NOTE: This script looks for the "build" folder in the 
"workspace_directory" root directory and deletes 
it, then iterates through all the folders in the root 
directory recursively looking for folders named "doc" and 
deletes them.
"""
import os
import shutil
import argparse

def clean(workspace_directory):
    """Delete build folder in root directory and scanning 
    all folders from the root directory and delete "doc" folders.

    Parameters
    ----------
    workspace_directory : str
        Root directory
    """
    try:
        shutil.rmtree(workspace_directory + "/" + "build")
    except OSError:
        print('-- Can\'t delete build directory')
    else:
        print('-- Build directory successfully delete')
    found_doc_directory = False
    for root, dirs, files in os.walk(workspace_directory):
        for dir in dirs:
            if dir.endswith("doc"):
                print('-- Document for delete found in the directory', os.path.join(root))
                shutil.rmtree(root + "/" + "doc")
                found_doc_directory = True
    if not found_doc_directory:
        print('-- Documents for delete is not fаound')
    else:
        print('-- Workspace successfully clean')

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
    clean(args.root)

if __name__ == '__main__':
    main()