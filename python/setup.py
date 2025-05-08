# python3 setup.py build
# sudo python3 setup.py install

# sudo apt install python3-pip
# pip install setuptools

from setuptools import Extension, setup

setup(
    name='mymodule',
    version='0.1',
    packages=['mymodule'],
    ext_modules=[Extension('mymodule.mymodule', ['mymodule/mymodule.c'])],
    package_data={'mymodule': ['*.pyi', 'py.typed']},
    include_package_data=True,
    zip_safe=False,
)


# poetry
# uv