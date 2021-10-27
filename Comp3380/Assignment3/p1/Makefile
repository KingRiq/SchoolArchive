JFLAGS = -g
JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
		  a3q1.java \


default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
	
run:
	java a3q1