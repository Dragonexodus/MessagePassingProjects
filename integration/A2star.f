       program integration
       integer newtop,addnewlink,links(7),link
       integer topid, np, nprocs,f,n,id
       double precision summe, integral, derivation,PI

       summe = 0
       integral = 0
       f = 1
       n = 15

       id=myprocid()
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
              call startIntegration(f,n,integral)
              if(id.eq.0) then
                     print*,"use f:",f," with n:",n
c      Integralteilstück vom Master
                     summe = integral
                     do i=1,(np-1)
c      Empfange alle Teilstücke und addiere Sie
                            call recv(topid,links(i),integral,8)
                            summe = summe + integral
                     enddo
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
       end

       subroutine readCL(f,n)
       character *10 cArg
       integer f,n
       do i = 1, iargc()
              call getarg(i, cArg)
              if(i.eq.1)then                     
                     read(cArg,*) f
                     if(f.gt.2.or.f.lt.1)then
                            print*,"error-input of function:",f
                            f=1
                     endif        
              elseif(i.eq.2)then
                     read(cArg,*) n
                     if(n.gt.20.or.n.lt.1)then
                            print*,"error-input of n:",n
                            n=20
                     endif
              endif
       end do
       end

       subroutine startIntegration(f,n,integral)
       integer f,n
       double precision integral,a,b1,b2,PI
       parameter(a = 0, b2 = 1.0)
     
       if(f.eq.1)then
              b1 = PI()
              call integrate(n,integral,f,a,b1)
       else
              call integrate(n,integral,f,a,b2)    
       endif
       end

       subroutine integrate(n,summe,f,a,b)
       integer start,stop,timenowhigh,timediff,n,id,exponent,nL,f
       integer factor,i,offset
       double precision a,b,h,summe,step,micro,aL,getVal
       parameter(micro=10**6)

       id = myprocid()
       start = timenowhigh()

       h = dble((b-a)/n)
       nL = n / nprocs()
       aL = a + id * nL * h

c      Relevant für exponent!
       offset = 0

c      Randwert a, erste id
c      Erstes aL, berechnet gehe zum nächsten über 
c      und mache einen Schritt weniger 
       if(id.eq.0)then
              summe = getVal(f,a)
              aL = aL + h
              nL = nL-1  
       endif

c      Randwert b, letzte id
c      Letztes aL, berechnet und mache einen Schritt weniger
       if(id.eq.(nprocs()-1))then
              summe = getVal(f,b)   
              nL = nL-1  
       endif
   
c      End/zwischenstück(e) starten mit Faktor 2, nicht Faktor 4
c      Verschiebe um eins, Schrittanzahl bleibt gleich  
       if(id.gt.0)then            
              offset = 1
       endif

       step = aL

c      Berechnung zwischenstücke
       do i=1,nL
              exponent = mod(i+offset,2) + 1
              factor=2**exponent
              summe = summe + dble(getVal(f,step) * factor)
              step = step + h    
       enddo
       
       summe = dble(h/3)*summe  
       stop = timenowhigh()
       print*,"ID:",id," T:", dble(timediff(stop,start)/micro)
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
       f2 = dble(4/(1+x**2))
       return 
       end

c      Fortran 77 empfohlen um Pi zu erzeugen
c      https://stackoverflow.com/questions/2157920/why-define-pi-4atan1#2157952
       double precision function PI()
       PI = 4.D0*DATAN(1.D0)
       return 
       end

c compile with: f77.px -o A2star.px A2star.f
c run with: run -f0 4 2 A2star.px