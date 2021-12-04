objects = program.o readcgnsdata.o readcgnsdata_rbf.o extra_memory.o initlize.o RUNGK.o boundary_conditions.o derivatives.o conv_flux.o update.o output.o output_tecplot.o cl_cd.o rtd.o transfer.o convergence.o time_step.o visc_flux.o  VIV.o rbf_trans.o readcgnsdata_1.o initlize_1.o accuracy_1.o nodal_velo.o face_vol_increment.o lubksb.o ludcmp.o limiter.o         

run:$(objects)
	cc -Wall -o run $(objects) -lm -lcgns -L.


program.o:program.c definitions.h
readcgnsdata.o:readcgnsdata.c definitions.h
readcgnsdata_rbf.o:readcgnsdata_rbf.c definitions_rbf.h
extra_memory.o:extra_memory.c definitions.h
initlize.o:initlize.c definitions.h
boundary_conditions.o:boundary_conditions.c definitions.h
time_step.o:time_step.c definitions.h
RUNGK.o :RUNGK.c definitions.h
derivatives.o:derivatives.c definitions.h
conv_flux.o:conv_flux.c definitions.h
visc_flux.o:visc_flux.c definitions.h
rtd.o:rtd.c definitions.h
update.o:update.c definitions.h
convergence.o:convergence.c definitions.h
output.o:output.c definitions.h
output_tecplot.o:output_tecplot.c definitions.h
cl_cd.o:cl_cd.c definitions.h
VIV.o:VIV.c definitions.h
rbf_trans.o:rbf_trans.c definitions_rbf.h
transfer.o:transfer.c definitions.h
readcgnsdata_1.o:readcgnsdata_1.c definitions.h
initlize_1.o:initlize_1.c definitions.h
nodal_velo.o:nodal_velo.c definitions.h
face_vol_increment.o:face_vol_increment.c definitions.h
accuracy_1.o:accuracy_1.c definitions.h
lubksb.o:lubksb.c definitions_rbf.h
ludcmp.o:ludcmp.c definitions_rbf.h
limiter.o:limiter.c definitions.h


.PHONY:clean
clean:
	rm -rf $(objects)
