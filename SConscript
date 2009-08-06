# -*- python -*-
# $Header: $
# Authors: T.Usher <usher@slac.stanford.edu>
# Version: OverlayEvent-00-02-01
Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('OverlayEventLib', depsOnly = 1)
OverlayEvent = libEnv.SharedLibrary('OverlayEvent', listFiles(['src/*.cpp']))

progEnv.Tool('OverlayEventLib')

test_OverlayEvent = progEnv.Program('test_OverlayEvent',
                                    ['src/test/testmain.cxx'])
progEnv.Tool('registerTargets', package='OverlayEvent',
             libraryCxts = [[OverlayEvent, libEnv]],
             testAppCxts = [[test_OverlayEvent, progEnv]],
             includes = listFiles(['OverlayEvent/*.h']) )
