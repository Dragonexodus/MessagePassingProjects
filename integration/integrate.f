       program integration
       integer makering, links(0:1), size, topid, id, sum
       double precision pi,a,b,integrateF1
       pi = 3.14159265358979323
       a = 0
       b = 1
       size = nprocs ()
       topid = makering (1, size, -1, -1, -1, -1, -1, -1, id, links)
       sum = 0

       if(id.eq.0) then
c TODO: check if straight with mod(size,2).eq.0
              print*,"integral for f1: " ,integrateF1(size,a,b)                       
       endif

       call freetop (topid)
       end

       double precision function integrateF1(n,a,b)      
              integer n
              double precision  a,b,h,f2, summe
              h= dble((b-a)/n)
c              clientRes = f1(a)+f1(b)

              summe = f2(a)
              print*,"a: ", a ," Summe:", summe
c TODO sicherheitsabfrage n <=2
              do i=1,(n-2)
                     if(mod(i,2).eq.0) then
                          summe = summe + 2*f2(a)
                     else
                          summe = summe + 4*f2(a)
                     endif
                     a = a+h    
                     print*,"a: ", a ," Summe:", summe
              enddo
              summe = summe + f2(b)
              print*,"a: ", a ," Summe:", summe, "f1(b): ", f2(b)
              
              integrateF1 = (h/3)*summe
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
