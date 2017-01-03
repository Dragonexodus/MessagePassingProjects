       program integration
       integer makering, links(0:1), size, topid, id, sum
       double precision integrateF1
       n = 10000
       size = nprocs ()
       topid = makering (1, size, -1, -1, -1, -1, -1, -1, id, links)
       sum = 0
c TODO: read command line flag of used function
       if(id.eq.0.and.mod(n,2).eq.0) then
              print*,"integral for f1: " ,integrateF1(n)                       
       endif

       call freetop (topid)
       end

       double precision function integrateF1(n)      
              integer n
              double precision  a,b,h,f1, summe
              a = 0
              b = 3.14159265358979323
              h= dble((b-a)/n)

              summe = f1(a)
              if(n.gt.2) then
                     do i=1,(n-2)
                            if(mod(i,2).eq.0) then
                                 summe = summe + 2*f1(a)
                            else
                                 summe = summe + 4*f1(a)
                            endif
                            a = a+h    
                     enddo
              endif
              summe = summe + f1(b)
              
              integrateF1 = (h/3)*summe
              RETURN
       end    
       
       double precision function f1(x)
              double precision x
              f1 = x*dsin(x)
              return
       end

       double precision function integrateF2(n)      
              integer n
              double precision  a,b,h,f2, summe
              a = 0
              b = 1
              h= dble((b-a)/n)

              summe = f2(a)
              if(n.gt.2) then
                     do i=1,(n-2)
                            if(mod(i,2).eq.0) then
                                 summe = summe + 2*f2(a)
                            else
                                 summe = summe + 4*f2(a)
                            endif
                            a = a+h    
                     enddo
              endif
              summe = summe + f2(b)
              
              integrateF2 = (h/3)*summe
              RETURN
       end    

       double precision function f2(x)
              double precision x
              f2 = dble(4/(1+x**2))
              return 
       end

c compile with: f77.px -lVT -o integrate.px integrate.f
c run with: run -f0 4 2 integrate.px
