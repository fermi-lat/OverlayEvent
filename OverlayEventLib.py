#$Header: /nfs/slac/g/glast/ground/cvs/OverlayEvent/OverlayEventLib.py,v 1.1 2009/08/06 01:50:49 jrb Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['OverlayEvent'],
                 package = 'OverlayEvent')
    env.Tool('geometryLib')
    env.Tool('identsLib')
    env.Tool('addLibrary', library = env['clhepLibs'])

def exists(env):
    return 1;
