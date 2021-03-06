#  ICE Revision: $Id: /local/openfoam/Python/PyFoam/PyFoam/Basics/Utilities.py 8435 2013-09-17T12:50:28.576631Z bgschaid  $
""" Utility functions

Can be used via a class or as functions"""

import sys
from PyFoam.ThirdParty.six import print_
from PyFoam.Error import warning
import subprocess
import os,fnmatch

if sys.version_info<(2,6):
    from popen2 import popen4
else:
    from subprocess import Popen,PIPE,STDOUT
from os import listdir,path,remove as removeFile

import re

try:
    import shutil
except ImportError:
    # this is an old python-version without it. We'll try to work around it
    pass

class Utilities(object):
    """Class with utility methods

    Can be inherited without side effects by classes that need these
    methods"""

    def __init__(self):
        pass

    def execute(self,cmd,debug=False):
        """Execute the command cmd

        Currently no error-handling is done
        @return: A list with all the output-lines of the execution"""
        if debug:
            print_(cmd)

        if sys.version_info<(2,6):
            raus,rein = popen4(cmd)
        else:
            p = Popen(cmd, shell=True,
                      stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True)
            (rein,raus)=(p.stdin,p.stdout)
        tmp=raus.readlines()
        # line=raus.readline()
        # while line!="":
        #     print line
        #     line=raus.readline()

        return tmp

    def remove(self,f):
        """Remove a file if it exists."""
        if path.exists(f):
            removeFile(f)

    def rmtree(self,path,ignore_errors=False):
        """Encapsulates the shutil rmtree and provides an alternative for
        old Python-version"""
        try:
            shutil.rmtree(path,ignore_errors=ignore_errors)
        except NameError:
            self.execute("rm -rf "+path)

    def copytree(self,src,dst,
                 symlinks=False):
        """Encapsulates the shutil copytree and provides an alternative for
        old Python-version"""
        try:
            if path.isdir(dst):
                dst=path.join(dst,path.basename(path.abspath(src)))
            if path.isdir(src):
                shutil.copytree(src,dst,
                                symlinks=symlinks)
            else:
                self.copyfile(src,dst)
        except NameError:
            cpOptions="-R"
            if not symlinks:
                cpOptions+=" -L"
            self.execute("cp "+cpOptions+" "+src+" "+dst)

    def copyfile(self,src,dst):
        """Encapsulates the shutil copyfile and provides an alternative for
        old Python-version"""
        try:
            if path.isdir(dst):
                dst=path.join(dst,path.basename(path.abspath(src)))
            shutil.copyfile(src,dst)
            shutil.copymode(src,dst)
        except NameError:
            self.execute("cp "+src+" "+dst)

    def writeDictionaryHeader(self,f):
        """Writes a dummy header so OpenFOAM accepts the file as a dictionary
        @param f: The file to write to
        @type f: file"""

        f.write("""
// * * * * * * * * * //
FoamFile
{
	version 0.5;
	format ascii;
	root "ROOT";
	case "CASE";
	class dictionary;
	object nix;
}
""")

    excludeNames=["^.svn$" , "~$"]

    def listDirectory(self,d):
        """Lists the files in a directory, but excludes certain names
        and files with certain endings
        @param d: The directory to list
        @return: List of the found files and directories"""

        result=[]

        excludes=list(map(re.compile,self.excludeNames))

        for n in listdir(d):
            ok=True

            for e in excludes:
                if e.search(n):
                    ok=False
                    break

            if ok:
                result.append(n)

        return result

    def which(self,progname):
        """Get the full path. Return None if not found"""
        pipe = subprocess.Popen('which '+progname,
                                shell=True,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.STDOUT)

        (fullname, errout) = pipe.communicate(input=input)

        stat = pipe.returncode

        if stat:
            warning("which can not find a match for",progname)
            return None
        else:
            return fullname

    def find(self,pattern, path,directoriesToo=True):
        """Find all files whose names match
        @param pattern: glob-style pattern
        @param path: path under which this files are to be searched
        @param directoriesToo: also match directories?"""
        result = []
        for root, dirs, files in os.walk(path):
            for name in files:
                if fnmatch.fnmatch(name, pattern):
                    result.append(os.path.join(root, name))
            if directoriesToo:
                for name in dirs:
                    if fnmatch.fnmatch(name, pattern):
                        result.append(os.path.join(root, name))
        return result

    def humanReadableSize(self,num):
        """Lifted from http://stackoverflow.com/questions/1094841/reusable-library-to-get-human-readable-version-of-file-size
        Gets a number in bytes and returns a human readable string"""
        for x in ['bytes','KB','MB','GB']:
            if num < 1024.0 and num > -1024.0:
                return "%3.1f%s" % (num, x)
            num /= 1024.0
        return "%3.1f%s" % (num, 'TB')

def humanReadableSize(num):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().humanReadableSize(num)

def which(prog):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().which(prog)

def execute(cmd,debug=False):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().execute(cmd,debug)

def writeDictionaryHeader(f):
    """Calls the method of the same name from the Utilites class"""
    Utilities().writeDictionaryHeader(f)

def listDirectory(d):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().listDirectory(d)

def rmtree(path,ignore_errors=False):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().rmtree(path,ignore_errors=ignore_errors)

def copytree(src,dest,symlinks=False):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().copytree(src,dest,symlinks=symlinks)

def remove(f):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().remove(f)

def copyfile(src,dest):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().copyfile(src,dest)

def find(pattern,path,directoriesToo=True):
    """Calls the method of the same name from the Utilites class"""
    return Utilities().find(pattern,path,directoriesToo=directoriesToo)

# Should work with Python3 and Python2