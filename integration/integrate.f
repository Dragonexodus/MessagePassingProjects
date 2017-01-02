       program integration
       integer makering, links(0:1), size, topid, id, sum
c 0:1 verschiebt auf 0
c double precision mit dble(4.0)/dble(2.0) -> richtiger datentyp

       size = nprocs ()
       topid = makering (1, size, -1, -1, -1, -1, -1, -1, id, links)
       sum = 0   

       if (id.eq.0) then
              print*, 'Prozess :', id, ' sendet  :', sum
              call send(topid, links(1),sum,1)
		call recv(topid,links(0),sum,1)
              print*, 'Prozess :', id, ' empfangen  :', sum
       else
              call recv(topid,links(0),sum,1)
              sum = sum + id
              print*, 'Prozess :', id, ' empfangen  :', sum
              call send(topid, links(1),sum,1)
	endif
       call freetop (topid)
       end

