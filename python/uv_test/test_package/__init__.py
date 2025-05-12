# python3 setup.py build
# sudo python3 setup2.py bdist_wheel

# sudo apt install python3-pip
# pip install setuptools

from .main import main
from .module_a import module_var_a, module_a_func
from .module_b import Module_B, module_var_b

__all__ = ["module_var_a", "module_a_func", "Module_B", "module_var_b"]

def package_func():
    print("Function defined from package")

print("테스트 패키지가 불러와 졌다!!")
