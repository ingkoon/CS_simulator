#매트랩 import
import matlab.engine
import numpy as np
#매트랩 실행
eng = matlab.engine.start_matlab()

eng.workspace['x'] = 3
a = eng.eval("x+3;")

eng.eval("y = 5;", nargout=0)
print(eng.workspace['y'])

x_randn_matlab = eng.randn(4,4)
print(x_randn_matlab)
#x_randn_matlab_T = eng.transpose(x_randn_matlab)
#print(x_randn_matlab)
