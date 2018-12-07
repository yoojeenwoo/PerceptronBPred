#README
#Be inside polybench-c-3.2 before running
#add polybench.h and polybench.c to polybench-c-3.2 before running
#after first run comment out all mv instructions

#Putting all testbenches into 2 big folder with their own folders
mv polybench-c-3.2/medley/* polybench-c-3.2/
mv polybench-c-3.2/linear-algebra/* polybench-c-3.2/
mv polybench-c-3.2/kernels/* polybench-c-3.2/
mv polybench-c-3.2/solvers/* polybench-c-3.2/
mv polybench-c-3.2/datamining/* polybench-c-3.2/
mv polybench-c-3.2/medley/* polybench-c-3.2/
mv polybench-c-3.2/stencils/* polybench-c-3.2/

NAME=awalia

#Linear Algebra Compilation
gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c 2mm/2mm.c
mv a.out 2mm

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c 3mm/3mm.c
mv a.out 3mm

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c atax/atax.c
mv a.out atax

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c bicg/bicg.c
mv a.out bicg

#gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c cholesky/cholesky.c
#mv a.out cholesky

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c doitgen/doitgen.c
mv a.out doitgen

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c gemm/gemm.c
mv a.out gemm

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c gemver/gemver.c
mv a.out gemver

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c gesummv/gesummv.c
mv a.out gesummv

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c mvt/mvt.c
mv a.out mvt

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c symm/symm.c
mv a.out symm

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c syr2k/syr2k.c
mv a.out syr2k

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c syrk/syrk.c
mv a.out syrk

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c trisolv/trisolv.c
mv a.out trisolv

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c trmm/trmm.c
mv a.out trmm

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c durbin/durbin.c
mv a.out durbin

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c dynprog/dynprog.c
mv a.out dynprog

#gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c gramschmidt/gramschmidt.c
#mv a.out gramschmidt

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c lu/lu.c
mv a.out lu

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c ludcmp/ludcmp.c
mv a.out ludcmp

#Datamining & Medley Compilation
#gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c correlation/correlation.c
#mv a.out correlation

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c covariance/covariance.c
mv a.out covariance

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c floyd-warshall/floyd-warshall.c
mv a.out floyd-warshall

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c reg_detect/reg_detect.c
mv a.out reg_detect

#Stencils
gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c adi/adi.c
mv a.out adi

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c fdtd-2d/fdtd-2d.c
mv a.out fdtd-2d

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c fdtd-apml/fdtd-apml.c
mv a.out fdtd-apml

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c jacobi-1d-imper/jacobi-1d-imper.c
mv a.out jacobi-1d-imper

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c jacobi-2d-imper/jacobi-2d-imper.c
mv a.out jacobi-2d-imper

gcc -I/home/$NAME/gem5/polybench-c-3.2/ polybench.c seidel-2d/seidel-2d.c
mv a.out seidel-2d
