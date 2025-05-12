# uv build
# pip install dist/uv_test-0.1.0-py3-none-any.whl
# test_package_main
# 옵션 uninstall -> pip uninstall uv_test

from .module_a import module_var_a, module_a_func
from .module_b import module_var_b, Module_B

def main():
    print(module_var_a)
    module_a_func()
    print(module_var_b)
    print(Module_B())
    print(module_var_a)

    
    
if __name__ == "__main__":
    main()