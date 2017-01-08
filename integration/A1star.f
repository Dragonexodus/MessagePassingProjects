       program integration
       character *10 cArg 
       integer newtop,addnewlink,links(7),link
       integer topid, np, nprocs,f,n,id
       double precision summe, integral

       summe = 0
       integral = 0
       f = 1
       n = 15

       id=myprocid()
       np = nprocs()
       topid=newtop(np-1)

       call readCL(cArg,f,n)
       n = 2**n

c init star
       if(id.eq.0) then
         do i=1,(np-1)
              links(i)=addnewlink(topid,i,1)
         enddo
       else
         link=addnewlink(topid,0,1)
       endif

c integrate
       if(id.eq.0) then
          print*,"use f",f," with n:",n
          call integrate(f,n,id,integral)
c master part of the integral
          summe = integral
          do i=1,(np-1)
c receive and add all slave parts of the integral
                 call recv(topid,links(i),integral,8)
                 summe = summe + integral
          enddo
          print*,"Pi Integral:",summe
       else
c slave part of the integral + send
           call integrate(f,n,id,integral)
           call send(topid, link,integral,8)
       endif

       call freetop (topid)

       end

       subroutine readCL(cArg,f,n)
       character *10 cArg
       integer f,n
       DO i = 1, iargc()
              CALL getarg(i, cArg)
              if(i.eq.1)then                     
                     READ(cArg,*) f
                     if(f.gt.2.or.f.lt.1)then
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
       end

       subroutine integrate(f,n,id,integral)
           integer f,n,id
           double precision integral
           if(f.eq.1)then
              call integrateF1(n,id,integral)
           elseif(f.eq.2)then
              call integrateF2(n,id,integral)              
           endif
       end

       subroutine integrateF1(n,id,summe)
              integer start,stop,timenowhigh,timediff,n,id,exponent,nL
              double precision a,b,h,summe,step,f1,micro,aL,bL
              parameter(micro=10**6,a = 0, b = 3.14159265358979323)

              start = timenowhigh()

              h= dble((b-a)/n)
              nL = n / nprocs()
              aL = a + id * nL * h
              bL = aL + nL * h

c             TODO hier vermutlich noch nicht komplett korrekt wegen Rand..
              if(id.eq.0)then
                     summe = f1(a) + f1(b)
                     step = aL + h
                     nL = nl-1
              else
                     step = aL
              endif

              do i=1,(nL-1)
                     exponent = mod(i,2) + 1 
                     summe = summe + f1(step) * 2**exponent
                     step = step + h    
              enddo

              summe=(h/3)*summe  
              stop = timenowhigh()
              print*,"ID:",id," T:", dble(timediff(stop,start)/micro)
       end
       
       double precision function f1(x)
              double precision x
              f1 = x*dsin(x)
              return
       end

       subroutine integrateF2(n,id,summe)
              integer start,stop,timenowhigh,timediff,n,id,exponent,nL
              double precision a,b,h,summe,step,f2,micro,aL,bL
              parameter(micro=10**6,a = 0, b = 1)

              start = timenowhigh()

              h= dble((b-a)/n)
              nL = n / nprocs()
              aL = a + id * nL * h
              bL = aL + nL * h

c             TODO hier vermutlich noch nicht komplett korrekt wegen Rand..
              if(id.eq.0)then
                     summe = f2(a) + f2(b)
                     step = aL + h
                     nL = nl-1
              else
                     step = aL
              endif

              do i=1,(nL-1)
                     exponent = mod(i,2) + 1 
                     summe = summe + f2(step) * 2**exponent
                     step = step + h    
              enddo

              summe=(h/3)*summe  
              stop = timenowhigh()
              print*,"ID:",id," T:", dble(timediff(stop,start)/micro)
       end

       double precision function f2(x)
              double precision x
              f2 = dble(4/(1+x**2))
              return 
       end

