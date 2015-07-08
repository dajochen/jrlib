from PyQt4 import pyqtconfig
_pkg_config = {
    'pyJR_sip_dir':    '/usr/share/sip',
    'pyJR_sip_flags':  '-x VendorID -t WS_X11 -x PyQt_NoPrintRangeBug -t Qt_4_8_4 -x Py_v3 -g'
}

_default_macros = None
 
class Configuration(pyqtconfig.Configuration):
    def __init__(self, sub_cfg=None):
        if sub_cfg: cfg = sub_cfg
        else: cfg = []
        cfg.append(_pkg_config)
        pyqtconfig.Configuration.__init__(self, cfg)
 
class PyQtHybridModuleMakefile(pyqtconfig.QtGuiModuleMakefile):
    def finalise(self):
        self.extra_libs.append("pyJR")
        pyqtconfig.QtGuiModuleMakefile.finalise(self) 
