from cx_Freeze import setup, Executable

base = None    

executables = [Executable("start.py", base=base)]

packages = ["sqlite3", "pyqt5", 'time', 'hashlib', 'defender', 'database', 'sys']
options = {
    'build_exe': {    
        'packages':packages,
    },    
}

setup(
    name = "<any name>",
    options = options,
    version = "0.1",
    description = '<any description>',
    executables = executables
)