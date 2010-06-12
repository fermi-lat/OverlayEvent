# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/OverlayEvent/SConscript,v 1.4 2010/06/11 00:39:35 jrb Exp $
# Authors: T.Usher <usher@slac.stanford.edu>
# Version: OverlayEvent-00-03-01
Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package = 'OverlayEvent', toBuild='shared')
OverlayEvent = libEnv.SharedLibrary('OverlayEvent', listFiles(['src/*.cpp']))

progEnv.Tool('OverlayEventLib')

test_OverlayEvent = progEnv.Program('test_OverlayEvent',
                                    ['src/test/testmain.cxx'])
progEnv.Tool('registerTargets', package='OverlayEvent',
             libraryCxts = [[OverlayEvent, libEnv]],
             testAppCxts = [[test_OverlayEvent, progEnv]],
             includes = listFiles(['OverlayEvent/*.h']) )
