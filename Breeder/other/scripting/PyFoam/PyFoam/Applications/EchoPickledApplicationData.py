#  ICE Revision: $Id: /local/openfoam/Python/PyFoam/PyFoam/Applications/EchoPickledApplicationData.py 8415 2013-07-26T11:32:37.193675Z bgschaid  $
"""
Application class that implements pyFoamEchoPickledApplicationData
"""

import sys,re

from .PyFoamApplication import PyFoamApplication

from PyFoam.RunDictionary.ParsedParameterFile import ParsedParameterFile

from .CommonPickledDataInput import CommonPickledDataInput

from PyFoam.Error import PyFoamException

class EchoPickledApplicationData(PyFoamApplication,
                     CommonPickledDataInput):
    def __init__(self,args=None,inputApp=None):
        description="""\ Reads a file with pickled application data
and if asked for prints it. Mainly used for testing the exchange of
data via pickled data
        """

        PyFoamApplication.__init__(self,
                                   args=args,
                                   description=description,
                                   usage="%prog [options]",
                                   nr=0,
                                   changeVersion=False,
                                   interspersed=True,
                                   inputApp=inputApp)

    def addOptions(self):
        CommonPickledDataInput.addOptions(self)

    def run(self):
        self.setData(self.readPickledData())

# Should work with Python3 and Python2
