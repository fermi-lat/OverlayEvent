#$Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/OverlayEvent/OverlayEventLib.py,v 1.2 2012/07/24 20:33:36 jrb Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['OverlayEvent'],
                 package = 'OverlayEvent')
        if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
	    env.Tool('findPkgPath', package = 'OverlayEvent') 
    if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
        env.Tool('findPkgPath', package = 'enums') 
        env.Tool('findPkgPath', package = 'Event') 
    env.Tool('geometryLib')
    env.Tool('identsLib')
    env.Tool('addLibrary', library = env['clhepLibs'])
    env.Tool('addLibrary', library = env['gaudiLibs'])

def exists(env):
    return 1;
