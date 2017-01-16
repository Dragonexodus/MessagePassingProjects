       program integration
       integer newtop,addnewlink,links(7),link
       integer topid, np, nprocs,f,n,id,start,stop,timenowhigh,timediff
       double precision summe, integral, derivation,PI,h,micro
       parameter(micro=10**6)

       f = 1
       n = 15

       start = timenowhigh()

       id = myprocid()
       np = nprocs()

c      Beschränkung auf eine gerade Prozessoranzahl!
c      (nL sollte ganzzahlig sein)
       if(np.eq.1.or.mod(np,2).eq.0)then
c
       topid=newtop(np-1)

       call readCL(f,n)
       n = 2**n

c      initalisierie Stern-Topologie
       if(id.eq.0) then
              do i=1,(np-1)
                     links(i)=addnewlink(topid,i,1)
              enddo
       else
              link=addnewlink(topid,0,1)
       endif

c      starte die Integration
       call startIntegration(f,n,integral,h)
       if(id.eq.0) then
              print*,"use f:",f," with n:",n
c      Integralteilstück vom Master
              summe = integral
              do i=1,(np-1)
c      Empfange alle Teilstücke und addiere Sie
                     call recv(topid,links(i),integral,8)
                     summe = summe + integral
              enddo
              summe = h/3 *summe
              derivation =  PI() - summe
              print*,"--------------------------"
              print*,"PI Referece:",PI()                   
              print*,"PI Integral:",summe
              print*,"PI Derivat.:",derivation
       else
c      Sende Integralteilstücke zum Master
              call send(topid, link,integral,8)
       endif
c      Löse erstellte Topologie wieder auf            
       call freetop (topid)
       

       else
              if(id.eq.0) then
              print*,"error-input of procs:",np ," (mod(p,2) != 0)"
              endif
       endif

       stop = timenowhigh()
       if(id.eq.0) then
              print*, " T:", dble(timediff(stop,start)/micro)
       endif
       end

       subroutine readCL(f,n)
       character *10 cArg
       integer f,n,id

       id = myprocid()

       do i = 1, iargc()
              call getarg(i, cArg)
              if(i.eq.1)then                     
                     read(cArg,*) f
                     if(f.gt.2.or.f.lt.1)then
                            if(id.eq.0) then
                                   print*,"error-input of function:",f
                            endif
                            f=1
                     endif        
              elseif(i.eq.2)then
                     read(cArg,*) n
                     if(n.gt.20.or.n.lt.1)then
                            if(id.eq.0) then
                                   print*,"error-input of n:",n
                            endif
                            n=20
                     endif
              endif
       end do
       end

       subroutine startIntegration(f,n,integral,h)
       integer f,n
       double precision integral,a,PI,b,h
       parameter(a = 0)

       if(f.eq.1)then
              b=PI()
       else
              b=1.0
       endif 

       h = dble(b-a)/dble(n)
       call integrate(n,integral,f,a,h)    

       end

       subroutine integrate(n,summe,f,a,h)
       integer n,id,exponent,nL,f
       integer factor,i
       double precision a,h,summe,step,aL,bL,getVal

       id = myprocid()
   
       nL = n / nprocs()
       aL = a + id * nL * h
       bL = aL + nL * h

c      Randwerte
       summe = getVal(f,aL) + getVal(f,bL)   
       step = aL + h

c      Berechnung zwischenstücke
       do i=1,nL-1
              exponent = mod(i,2) + 1
              factor=2**exponent
              summe = summe + dble(getVal(f,step) * factor)
              step = step + h    
       enddo

       end
  
       double precision function getVal(f,x)
       integer f
       double precision x,f1,f2
       if(f.eq.1)then
              getVal = f1(x)
       else
              getVal = f2(x)         
       endif
       return
       end
     
       double precision function f1(x)
       double precision x
       f1 = x*dsin(x)
       return
       end

       double precision function f2(x)
       double precision x
       f2 = dble(4)/dble(1+x*x)
       return 
       end

c      Fortran 77 empfohlen um Pi zu erzeugen
c      https://stackoverflow.com/questions/2157920/why-define-pi-4atan1#2157952
       double precision function PI()
       PI = 4.D0*DATAN(1.D0)
       return 
       end

c compile with: f77.px -o A2star.px A2star.f
c run with: run -f0 1 1 A2star.px 
