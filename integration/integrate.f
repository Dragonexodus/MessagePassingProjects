       program integration
       double precision integrateF1, integrateF2, micro
       integer makehcube, dim, topid, id, start, stop
       parameter(dim = 3, micro=10**6)
       integer links(dim), timenowhigh, timediff

c       integer iArg
c       character cArg

c       iArg = iargc()
c       call getarg(iArg,cArg)
c       print*,"iArg: " ,iArg
c       print*,"cArg: " ,cArg

c      Für Messungen wird 2^n empfohlen
       n = 2**15

       size = nprocs ()
       topid = makehcube(1, dim, -1, -1, -1, -1, -1, -1, id, links)

c TODO: read command line flag of used function


       if(id.eq.0.and.mod(n,2).eq.0) then
              start = timenowhigh()
              print*,"ID:",id," Pi f1:" ,integrateF1(n)
              stop = timenowhigh()
              print*,"ID:",id," T:", dble(timediff(stop,start)/micro)                     
       endif
       if(id.eq.1.and.mod(n,2).eq.0) then    
              start = timenowhigh()
              print*,"ID:",id," Pi f2:" ,integrateF2(n)  
              stop = timenowhigh()
              print*,"ID:",id," T: ", dble(timediff(stop,start)/micro)                   
       endif

       call freetop (topid)
       end

       double precision function integrateF1(n)      
              integer n,exponent
              double precision  a,b,h,summe,step,f1
              parameter ( a = 0, b = 3.14159265358979323)

              h= dble((b-a)/n)

              summe = f1(a)
              step = a + h
              if(n.gt.2) then
                     do i=1,(n-2)
                            exponent = mod(i,2) + 1 
                            summe = summe + f1(step) * 2**exponent
                            step = step + h    
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
              integer n,exponent
              double precision  a,b,h,summe,step,f2
              parameter ( a = 0, b = 1)
              h= dble((b-a)/n)

              summe = f2(a)
              step = a + h
              if(n.gt.2) then
                     do i=1,(n-2)
                            exponent = mod(i,2) + 1 
                            summe = summe + f2(step) * 2**exponent
                            step = step + h   
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
