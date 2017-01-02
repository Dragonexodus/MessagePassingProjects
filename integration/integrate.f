       program integration
       integer makering, links(0:1), size, topid, id, sum
       double precision pi,a,b,integrateF1
       pi = 3.14159265358979323
       a = 0
       b = pi
       size = nprocs ()
       topid = makering (1, size, -1, -1, -1, -1, -1, -1, id, links)
       sum = 0

       if(id.eq.0) then
c todo: check if straight with mod(size,2).eq.0
              print*,"integral for f1: " ,integrateF1(size,a,b)                       
       endif

       call freetop (topid)
       end

       double precision function integrateF1(n,a,b)      
              integer n
              double precision  a,b,h,f1,clientRes
              h= dble((b-a)/n)
              clientRes = f1(a)+f1(b)
              integrateF1 = (h/3)*clientRes
              RETURN
       end           

       double precision function f1(x)
              double precision x
              f1 = x*dsin(x)
              return
       end

       double precision function f2(x)
              double precision x
              f2 = dble(4/(1+x**2))
              return 
       end

c compile with: f77.px -lVT -o integrate.px integrate.f
c run with: run -f0 4 2 integrate.px   
