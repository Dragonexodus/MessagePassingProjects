       program integration
       integer newtop,addnewlink,links(7),link
       integer topid, np, nprocs,f,n,id
       double precision summe, integral

       summe = 0
       integral = 0
       f = 1
       n = 15

       id=myprocid()
       np = nprocs()

c      check processor count
       topid=newtop(np-1)

              call readCL(f,n)
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
                 call startIntegration(f,n,integral)
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
                  call startIntegration(f,n,integral)
                  call send(topid, link,integral,8)
              endif
            
              call freetop (topid)
       
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
           double precision integral,a,b1,b2
           parameter(a = 0, b1 = 3.14159265358979323, b2 = 1.0)
           if(f.eq.1)then
              call integrate(n,integral,f,a,b1)
           else
              call integrate(n,integral,f,a,b2)    
           endif
       end


       subroutine integrate(n,summe,f,a,b)
              integer start,stop,timenowhigh,timediff,n,id,exponent,nL,f
              double precision a,b,h,summe,step,micro,aL,getVal
              parameter(micro=10**6)

              id=myprocid()
              start = timenowhigh()

              h= dble((b-a)/n)
              nL = n / nprocs()
              aL = a + id * nL * h

c             Randwert a 
              if(id.eq.0)then
                     summe = getVal(f,a)
                     aL = aL + h
              endif
c             Randwert b, letzte id
              if(id.eq.(nprocs()-1))then
                     summe = getVal(f,b)
                     nL = nL-1
              endif                
              step = aL

c             Zwischenstücke
              do i=1,(nL-1)
c TODO herausfinden warum im sequenziellen Fall mit nL das Ergebnis viel genauer ist
c TODO betrachte 1 Randstück zu viel bei mehreren Prozessoren fixen
                     if(id.eq.0)then
                            print*,"i:",i
                            exponent = mod(i,2) + 1 
                     else
                            exponent = mod(i+1,2) + 1
                     endif
                     summe = summe + getVal(f,step)* 2**exponent
                     step = step + h    
              enddo

              summe=(h/3)*summe  
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

