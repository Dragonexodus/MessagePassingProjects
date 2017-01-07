       program integration
       character *10 cArg 
       integer newtop,addnewlink,send,recv, id, links(7),link,size
       integer topid, np, nprocs,res,tmp,f,n,size

       id=myprocid()
       np = nprocs()
       topid=newtop(np-1)
       tmp= 0
  
       f=1
       n=15
       call readCL(cArg,f,n)
       n = 2**n

c init star
       if(id.eq.0) then
         do i=1,np-1
              links(i)=addnewlink(topid,i,1)
         enddo
       else
         link=addnewlink(topid,0,1)
       endif
c choose f
       if(id.eq.0)then
              print*,"use f",f," with n:",n
          if(f.eq.1) then
              call integrateF1(n,id,topid,link,links)
          elseif(f.eq.2) then    
              call integrateF2(n,id,topid,link,links)   
          else 
              call integrateF1(n,id,topid,link,links)
              call integrateF2(n,id,topid,link,links)
          endif
       endif
       call freetop (topid)
c star communication:
c       if(id.eq.0) then
c         do i=1,np-1
c         call send(topid,links(i),99,4)
c         call recv(topid,links(i),res,4)

c         tmp = tmp+res

c         print *, "master get: ", res
c       enddo
c       print *, "master calculate: ",tmp
c       else
c         call recv(topid,link,res,4)
c         print *, "slave ",id," send back: ",res+id
c         call send(topid,link,res+id,4)
c       endif
       end

       subroutine readCL(cArg,f,n)
       character *10 cArg
       integer f,n
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
       end

       subroutine integrateF1(n,id,topid,link,links)
              integer start,stop,timenowhigh,timediff,n,id,exponent
              integer topid,link,links(7)
              double precision a,b,h,summe,step,f1,micro,res
              parameter(micro=10**6,a = 0, b = 3.14159265358979323)

              start = timenowhigh()
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

              res=(h/3)*summe

              print*,"ID:",id," Pi f1:" ,res
              stop = timenowhigh()
              print*,"ID:",id," T:", dble(timediff(stop,start)/micro)
       end
       
       double precision function f1(x)
              double precision x
              f1 = x*dsin(x)
              return
       end

       subroutine integrateF2(n,id,topid,link,links)    
              integer start,stop,timenowhigh,timediff,n,id,exponent
              integer topid,link,links(7)
              double precision res,micro,a,b,h,summe,step,f2
              parameter(micro=10**6, a = 0, b = 1)

              start = timenowhigh()
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
              
              res = (h/3)*summe

              print*,"ID:",id," Pi f2:" ,res

              stop = timenowhigh()
              print*,"ID:",id," T:", dble(timediff(stop,start)/micro) 
        end    

       double precision function f2(x)
              double precision x
              f2 = dble(4/(1+x**2))
              return 
       end

