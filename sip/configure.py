#!/usr/bin/python

import os
import sipconfig
from PyQt4 import pyqtconfig
 
build_file = "pyJR.sbf"
config =  pyqtconfig.Configuration()
pyqt_sip_flags = config.pyqt_sip_flags

jrElementDirs = ['classes', \
                 'element', \
                 'element/variable',\
                 'element/point',\
                 'element/curve', 'element/curve/snake',\
                 'element/surface',\
                 'element/plane',\
                 'element/misc','element/misc/2DGrid','element/misc/3DGrid',\
                 'model' 
                ]
                
jrRoot = '../'
                
sipIncludeDirs = "-I" + " -I".join(jrElementDirs)

sip_cmd = " ".join([ \
    config.sip_bin, \
    "-c", ".", \
    "-b", build_file, \
    "-I", config.pyqt_sip_dir, \
    sipIncludeDirs,\
    pyqt_sip_flags, \
    "jr.sip"])

print sip_cmd    
os.system(sip_cmd)

installs = []
installs.append(["jr.sip", os.path.join(config.default_sip_dir, "pyJR")])
installs.append(["pyJRConfig.py", config.default_mod_dir])


class myQtGuiModuleMakefile(pyqtconfig.QtCoreModuleMakefile):
    """The Makefile class for modules that %Import QtGui with QtXml support.
    """
    def __init__(self, *args, **kw):
        """Initialise an instance of a module Makefile.
        """
        if not kw.has_key("qt"):
            kw["qt"] = ["QtCore", "QtGui", "QtXml",  "QtOpenGL"]

        pyqtconfig.QtCoreModuleMakefile.__init__(self, *args, **kw)


#-----------------------------------------------
#-----------------------------------------------
makefile = myQtGuiModuleMakefile(
    configuration=config,
    build_file=build_file,
    installs=installs,
)

# -I (include directories):

#Directories with wrapped heades
makefile.extra_include_dirs.append('..')
for jrDir in jrElementDirs:
  makefile.extra_include_dirs.append(jrRoot+jrDir)

#Directories of headers, which are not wrapped but part of jr-library
for jrDir in ['views', 'gui', ""]:
  makefile.extra_include_dirs.append(jrRoot+jrDir)
  
#headers of libraries jr requires:
for jrDir in ['/usr/include/dxflib']:
  makefile.extra_include_dirs.append(jrDir)

makefile.extra_libs = ["jr","dxflib"]
makefile.extra_lib_dirs = [jrRoot]
 
makefile.generate()
#-----------------------------------------------
#-----------------------------------------------

content = {
  "pyJR_sip_dir":    config.default_sip_dir,
  "pyJR_sip_flags":  pyqt_sip_flags
}
	
sipconfig.create_config_module("pyJRConfig.py", "pyJRConfig.py.in", content)
