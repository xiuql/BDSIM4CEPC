import pymadx.Ptc
import pymadx.Beam
import pymadx.Builder
import pymadx.Tfs
import pybdsim.Beam
import pybdsim.Builder
import pybdsim.Data
import os as _os
import matplotlib.pyplot as _plt
import robdsim

class Test:
    def __init__(self,type_,foldername=None,particle="e-",energy=1.0,distribution='flat',nparticles=10,length=1.0,**kwargs): 
        """
        Tracking test class

        type = 'drift' | 'quadrupole' | 'sextupole'
        distribution = 'flat' | 'gaussian'
        """
        self.type_        = type_
        self.filename     = self.type_
        self.foldername   = foldername
        self.ptcfilename  = 'inrays.madx'
        if self.foldername != None:
            self.usingfolder = True
            self.filepath = self.foldername+'/'+self.filename
            self.ptcfilepath =  self.foldername+'/'+self.ptcfilename
            _os.system("mkdir -p " + self.foldername)
        else:
            self.usingfolder = False
            self.filepath = self.filename
            self.ptcfilepath = self.ptcfilename
        self.particle     = particle
        self.energy       = energy
        self.distribution = distribution
        self.distrkwargs  = {}
        self.nparticles   = nparticles
        self.length       = 1.0
        self.kwargs       = kwargs
        
    def CleanMakeRun(self):
        self.Clean()
        self.Make()
        self.Execute()
        self.Compare()
    
    def Clean(self):        
        _os.system("rm -rf "+self.filepath+"*")
        _os.system("rm -rf "+self.foldername+"/output*")
        _os.system("rm -rf "+self.foldername+"/Maxwellian_bend_for_ptc.txt trackone inrays.madx")
        _os.system("rm -rf "+self.foldername+"/test*")
        _os.system("rm -rf "+self.foldername+"/*.log")
        _os.system("rm -rf "+self.foldername+"/trackone")
        _os.system("rm -rf "+self.foldername+"/inrays.madx")
        
    def ChangeDistribution(self,distribution='flat',nparticles=10,**kwargs):
        """
        'flat'
        kwargs: mux=0.0, widthx=1e-05, mupx=0.0, widthpx=1e-05, muy=0.0, 
                widthy=0.001, mupy=0.0, widthpy=0.001
        'gauss'
        kwargs: gemx=1e-10, betax=0.1, alfx=0.0, gemy=1e-10, betay=0.1, 
                alfy=0.0, sigmat=1e-12, sigmapt=1e-12
        """
        self.distribution = distribution
        self.distrkwargs  = kwargs
        self.nparticles   = nparticles
        
    def Make(self):
        #type_='drift', foldername=None, particle='e-', energy=1.0,**kwargs) : 
        print 'Test> Element type:         ',self.type_
        print 'Test> Destination filepath: ',self.filepath
        print 'Test> kwargs: ',
        for k in self.kwargs : 
            print k+'='+str(self.kwargs[k]),

        if self.distribution == 'flat':
            ptc = pymadx.Ptc.FlatGenerator(**self.distrkwargs)
        elif self.distribution == 'gauss':
            ptc = pymadx.Ptc.GaussGenerator(**self.distrkwargs)
        
        ptc.Generate(self.nparticles,self.ptcfilepath)
        
        bb  = pybdsim.Beam(self.particle,self.energy,'ptc')
        xb  = pymadx.Beam(self.particle,self.energy,'ptc')
        
        bb.SetDistribFileName(self.ptcfilename) 
        xb.SetDistribFileName(self.ptcfilename) 
        
        bm  = pybdsim.Builder.Machine()
        xm  = pymadx.Builder.Machine()
        
        bm.AddBeam(bb)
        xm.AddBeam(xb)
    
        if self.type_ == 'drift' :
            name = 'd1'
            bm.AddDrift(name,length=self.length,**self.kwargs)
            xm.AddDrift(name,length=self.length,**self.kwargs)
        elif self.type_ == 'sbend':
            name = 'sb1'
            bm.AddDipole(name,length=self.length,**self.kwargs)
            xm.AddDipole(name,length=self.length,**self.kwargs)
        elif self.type_ == 'quadrupole' :
            name = 'q1'
            bm.AddQuadrupole(name,length=self.length,**self.kwargs)
            xm.AddQuadrupole(name,length=self.length,**self.kwargs)
        elif self.type_ == 'sextupole' :
            name = 's1'
            bm.AddSextupole(name,length=self.length,**self.kwargs)
            xm.AddSextupole(name,length=self.length,**self.kwargs)        

        bm.AddMarker("theend") # Need a post element marker to sample at, only for bdsim
        
        bm.AddSampler('theend')
        xm.AddSampler('all')

        bm.WriteLattice(self.filepath)
        xm.WriteLattice(self.filepath)
            
    def Execute(self):
        if self.usingfolder:
            _os.chdir(self.foldername)
        
        _os.system("madx < "+self.filename+".madx > madx.log")
        _os.system("bdsim --file="+self.filename+".gmad --batch --outfile='test' > bdsim.log")
        _os.system("bdsim --file="+self.filename+".gmad --batch --output=root --outfile='test' > bdsim.log")
        
        if self.usingfolder:
            _os.chdir("../")

    def Compare(self):

        bdsim = pybdsim.Data.Load(self.foldername+"/test.txt")
        Bx = bdsim.X()
        By = bdsim.Y()
        Bxp = bdsim.Xp()
        Byp = bdsim.Yp()

        madx = pymadx.Tfs(self.foldername+"/trackone")
        madx = madx.GetSegment(madx.nsegments) #get the last 'segment' / sampler
        Mx = madx.GetColumn('X')*1e6
        My = madx.GetColumn('Y')*1e6
        Mxp = madx.GetColumn('PX')
        Myp = madx.GetColumn('PY')
        
        bfn =''
        if self.usingfolder:
            bfn += self.foldername
        _plt.figure()
        _plt.plot(Mx,My,'b.',label='PTC')
        _plt.plot(Bx,By,'g.',label='BDSIM')
        _plt.legend()
        _plt.xlabel(r"x ($\mu$m)")
        _plt.ylabel(r"y ($\mu$m)")
        _plt.title(self.type_)
        _plt.savefig(bfn+'_xy.pdf')
        _plt.savefig(bfn+'_xy.png')

        _plt.figure()
        _plt.plot(Mxp,Myp,'b.',label='PTC')
        _plt.plot(Bxp,Byp,'g.',label='BDSIM')
        _plt.legend()
        _plt.xlabel(r"x' (rad)")
        _plt.ylabel(r"y' (rad)")
        _plt.title(bfn)
        _plt.savefig(bfn+'_xpyp.pdf')
        _plt.savefig(bfn+'_xpyp.png')

        _plt.figure()
        _plt.plot(Mx,Mxp,'b.',label='PTC')
        _plt.plot(Bx,Bxp,'g.',label='BDSIM')
        _plt.legend()
        _plt.xlabel(r"x (rad)")
        _plt.ylabel(r"x' (rad)")
        _plt.title(self.type_)
        _plt.savefig(bfn+'_xxp.pdf')
        _plt.savefig(bfn+'_xxp.png')

        _plt.figure()
        _plt.plot(My,Myp,'b.',label='PTC')
        _plt.plot(By,Byp,'g.',label='BDSIM')
        _plt.legend()
        _plt.xlabel(r"y (rad)")
        _plt.ylabel(r"y' (rad)")
        _plt.title(self.type_)
        _plt.savefig(bfn+'_yyp.pdf')
        _plt.savefig(bfn+'_yyp.png')

        #emittance
        
        r = robdsim.robdsimOutput(bfn+"/test_0.root")
        r.CalculateOpticalFunctions("optics.dat")
        d = pybdsim.Data.Load("optics.dat")
        print 'Horizontal emittance ',d.Emitt_x()
        print 'Vertical emittance   ',d.Emitt_y()
