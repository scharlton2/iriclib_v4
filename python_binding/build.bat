del _iric.pyd
del _iric.py
swig -c++ -python -cppext cpp iric.i
cl /LD iric_wrap.cpp ^
  -I"D:\iRIC_v4_dev\Miniconda3\envs\iric\include" ^
  "D:\iRIC_v4_dev\Miniconda3\envs\iric\libs\python312.lib" ^
  "..\release\iriclib.lib"

rename iric_wrap.dll _iric.pyd
del iric_wrap.lib
del iric_wrap.obj
del iric_wrap.exp

rem copy iric_custom.py D:\iRIC_dev\Miniconda3\envs\iric_hdf5\Lib\site-packages\iric.py
rem copy _iric.pyd D:\iRIC_dev\Miniconda3\envs\iric_hdf5\Lib\site-packages\_iric.pyd
