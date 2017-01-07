       program integration
       double precision integrateF1, integrateF2, micro
       integer makehcube, dim, topid, id, start, stop,f,n,size
       character *10 cArg 
       parameter(dim = 3, micro=10**6)
       integer links(dim), timenowhigh, timediff

       f=1
       n=15

c      read commandline values
       DO i = 1, iargc()
              CALL getarg(i, cArg)
              if(i.eq.1)then                     
                     READ(cArg,*) f
                     if(f.gt.3.or.f.lt.1)then
                     print*,"error-input of function:",f
                            f=1
                     endif        
              elseif(i.eq.2)then
                     READ(cArg,*) n
                     if(n.gt.17.or.n.lt.1)then
                     print*,"error-input of n:",n
                            n=17
                     endif
              endif
       END DO
 
       n = 2**n

c      create hcube
       size = nprocs ()
       topid = makehcube(1, dim, -1, -1, -1, -1, -1, -1, id, links)


c      master
c      if(id.eq.0)then
c      führe ersten teil der berechnung aus
c      slaves
c      else

c      call wanted functions
       if(id.eq.0)then
              print*,"use f",f," with n:",n
          if(f.eq.1) then
              start = timenowhigh()
              print*,"ID:",id," Pi f1:" ,integrateF1(n)
              stop = timenowhigh()
              print*,"ID:",id," T:", dble(timediff(stop,start)/micro)
          elseif(f.eq.2) then    
              start = timenowhigh()
              print*,"ID:",id," Pi f2:" ,integrateF2(n)  
              stop = timenowhigh()
              print*,"ID:",id," T: ", dble(timediff(stop,start)/micro)                   
          else 
              start = timenowhigh()
              print*,"ID:",id," Pi f1:" ,integrateF1(n)
              stop = timenowhigh()
              print*,"ID:",id," T:", dble(timediff(stop,start)/micro)    
              start = timenowhigh()
              print*,"ID:",id," Pi f2:" ,integrateF2(n)  
              stop = timenowhigh()
              print*,"ID:",id," T: ", dble(timediff(stop,start)/micro)                   
          endif
       endif
       call freetop (topid)
       end

c      functions
       double precision function integrateF1(n)      
              integer n,exponent
              double precision  a,b,h,summe,step,f1
              parameter ( a = 0, b = 3.14159265358979323)

              h= dble((b-a)/n)

c      local_n = n / p
c      local_a = a + rank * local_n * h;
c      local_b = local_a + local_n * h;

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
