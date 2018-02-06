# Getting a Python Package on PyPi
Having a package on PyPi is what lets you "pip install" something. I always forget how to do this. These steps are for updating an existing project, but the first time you update a project which does not already exist it will be created automatically.

## Setup.py
Place this in your package's root folder. The version must change for each upload, and you can insert a creative python script inside this script derive the version by reading the source code of some file.

```python
from setuptools import setup

__version__=1.2.3 # MUST UPDATE FOR EACH UPLOAD

setup(
    name='pyabf',
    version=__version__,
    author='Scott W Harden',
    author_email='SWHarden@gmail.com',
    packages=['pyabf'],
    url='http://github.com/swharden/pyABF',
    license='MIT License',
    platforms='any',
    description='Python library for reading files in Axon Binary Format (ABF)',
    long_description=open('README.rst').read(),
    install_requires=[	
       'matplotlib>=2.1.0',
       'numpy>=1.13.3',
	],
)
```

## Readme.rst
```

pyabf: A portable Python library for reading files in Axon Binary Format (ABF)
==============================================================================

* Project Homepage: `https://github.com/swharden/pyABF <https://github.com/swharden/pyABF>`_
* Package Usage: `https://github.com/swharden/pyABF/tree/master/doc/pyabf <https://github.com/swharden/pyABF/tree/master/doc/pyabf>`_
* ABF File Format: `https://github.com/swharden/pyABF/tree/master/doc/abf-file-format <https://github.com/swharden/pyABF/tree/master/doc/abf-file-format>`_
```

## Store your PyPi username
Create a `.pypirc` file and place it in your `~` directory.

```
[distutils]
index-servers =
    pypi

[pypi]
username: swharden
```

## Upload.bat

```
:: navigate to the source folder
cd ../../src/

:: assemble the package and upload it
python setup.py sdist upload

:: launch the webpage in the browser
explorer http://pypi.python.org/pypi/pyabf

:: wait for the user to manually close the console
pause
```