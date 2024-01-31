customer.o: customer.h customer.c
	gcc -c customer.c
testCustomer: testCustomer.o customer.o
	gcc -o testCustomer testCustomer.o customer.o
kiosk.o: kiosk.h kiosk.c customer.h
	gcc -c kiosk.c
testKiosk: testKiosk.o kiosk.o customer.o
	gcc -o testKiosk testKiosk.o kiosk.o customer.o
node.o: node.h node.c
	gcc -c node.c
list.o: list.h list.c node.h
	gcc -c list.c
queue.o: queue.h queue.c list.h
	gcc -c queue.c
testQueue: testQueue.o queue.o list.o node.o
	gcc -o testQueue testQueue.o queue.o list.o node.o
testDes: des.o kiosk.o customer.o queue.o list.o node.o
	gcc -o testDes des.o kiosk.o customer.o queue.o list.o node.o
testDesGT: desGenTable.o kiosk.o customer.o queue.o list.o node.o
	gcc -o testDesGT desGenTable.o kiosk.o customer.o queue.o list.o node.o
clean:
	rm *.o
