OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o text1.o text2.o cita.o Cjt_autors1.o Cjt_autors2.o
	g++ -o program.exe *.o $(OPCIONS)

text1.o: text1.cc
	g++ -c text1.cc $(OPCIONS)

text2.o: text2.cc
	g++ -c text2.cc $(OPCIONS)

cita.o: cita.cc
	g++ -c cita.cc $(OPCIONS)
	
Cjt_autors1.o: Cjt_autors1.cc
	g++ -c Cjt_autors1.cc $(OPCIONS)

Cjt_autors2.o: Cjt_autors2.cc
	g++ -c Cjt_autors2.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm  *.o
	rm  *.exe
compress:
	tar -cf program.tar *.cc *.hh Makefile
cleantar:
	rm *.tar
zipme:
	zip program.zip *.cc *.hh Makefile
cleanzip:
	rm *.zip