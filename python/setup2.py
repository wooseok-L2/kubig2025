# python3 setup.py build
# sudo python3 setup2.py bdist_wheel
# pip install dist/test_package-0.1.0-py3-none-any.whl
# test_package_main
# pip uninstall test_package


from setuptools import Extension, setup

setup(
    name="test_package",
    version="0.1.0",
    description="practice code",
    packages=["test_package"],
    entry_points={'console_scripts':['test_package_main = test_package:main']},      
    include_package_data=True,
    zip_safe=False,
)


# poetry
# uv