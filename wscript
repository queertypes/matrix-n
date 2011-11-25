import os

def options(opt):
  opt.load('compiler_cxx waf_unit_test')

def try_file(ctx, file_name):
  feature_name = os.path.basename(file_name).replace('.cpp', '')
  def_name = ('HAS_' + feature_name.upper())
  feature_msg = 'checking for c++11 feature ' + feature_name
  data = ""
  with open(file_name, "r") as f:
    data = f.readlines()
  ctx.check_cxx(fragment=''.join(data), define_name=def_name,
                msg = feature_msg,
                cxxflags='-std=c++0x', mandatory=False)

def configure(cfg):
  cfg.load('compiler_cxx waf_unit_test')

  # mandatory libraries
  cfg.check_cxx(lib='gsl')
  cfg.check_cxx(lib='gslcblas')

  # optional libraries
  cfg.check_cxx(header_name='CL/cl.hpp', 
                includes='/opt/AMDAPP/include',
                mandatory=False, define_name='HAS_OPENCL_C++')  

  cfg.check_cxx(header_name='CL/cl.h', 
                includes='/opt/AMDAPP/include',
                mandatory=False, define_name='HAS_OPENCL')  

  # check for c++0x features
  path = os.path.join(cfg.path.abspath(), 'config_tests')
  [try_file(cfg,os.path.join(path,x)) for x in os.listdir(path) if x.endswith('.cpp')]
  
  cfg.write_config_header('../include/config.h')

def build(bld):
  bld.program(source='src/fast-slater.cpp',
              includes='include',
              target='fast-slater',
              cxxflags='-Wall -Wextra -pedantic -ansi -std=c++0x -g -O2')
              
