       program integration
       integer makering, links(0:1), size, topid, id, sum
       double precision f1,f2,pi,a,b
       pi = 3.14159265358979323
       a = 0
       b = pi
c 0:1 verschiebt auf 0
c double precision mit dble(4.0)/dble(2.0) -> richtiger datentyp

       size = nprocs ()
       topid = makering (1, size, -1, -1, -1, -1, -1, -1, id, links)
       sum = 0

       if(id.eq.0) then
c mod(size,2).eq.0.and.
              print*,"integral for f1: " ,integrateF1(size,a,b)                       
       endif

c       if (id.eq.0) then
c              print*, 'Prozess :', id, ' sendet  :', sum
c              call send(topid, links(1),sum,1)
c		call recv(topid,links(0),sum,1)
c              print*, 'Prozess :', id, ' empfangen  :', sum
c       else
c              call recv(topid,links(0),sum,1)
c              sum = sum + id
c              print*, 'Prozess :', id, ' empfangen  :', sum
c              call send(topid, links(1),sum,1)
c	endif
       call freetop (topid)
       end

       function integrateF1(n,a,b)
              double precision  iF1       
              integer  n
              double precision  a              
              double precision  b
              double precision h = dble(b-a)/dble(n)
              print*,"n:",n," a:",a," b:",b
              print*,"h:",h
              print*,"f1(a):",f1(a)
              print*,"f1(b):",f1(b)
              integrateF1 = dble(h/3)*(f1(a)+f1(b)) 
              RETURN
       end           

       function f1(x)
              double precision f1      
              double precision  x
              f1 = dble(x*sin(x))
              return
       end

       double precision function f2(double precision x)
              f2 = dble(4)/dble((1+x**2))
       end

c compile with: f77.px -lVT -o integrate.px integrate.f
c run with: run -f0 4 2 integrate.px   
