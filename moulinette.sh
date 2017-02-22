#!/bin/bash

# TEST1 #
./my_nm tests/* > student 2>/dev/null
nm tests/* > source 2>/dev/null
diff=`awk -f diff.awk student source`
if [ -n "$diff" ]
then
    echo "Test1: KO (awk diff stored in test1.output)"
    echo "$diff" > test1.output
else
    echo "Test1: OK"
fi
rm -f student
rm -f source

# TEST2 #
./my_objdump tests/* > student 2>/dev/null
objdump -sf tests/* > source 2>/dev/null
diff=`diff student source`
if [ -n "$diff" ]
then
    echo "Test2: KO (diff stored in test2.output)"
    echo "$diff" > test2.output
else
    echo "Test2: OK"
fi
rm -f student
rm -f source

# TEST3 #
./my_objdump /bin/* > student 2>/dev/null
objdump -sf /bin/* > source 2>/dev/null
diff=`diff student source`
if [ -n "$diff" ]
then
    echo "Test3: KO (diff stored in test3.output)"
    echo "$diff" > test3.output
else
    echo "Test3: OK"
fi
rm -f student
rm -f source

# TEST4 #
touch tmp
mv my_objdump objdump_name
./objdump_name tmp > student 2>&1
mv objdump_name my_objdump
cp /usr/bin/objdump objdump_name
./objdump_name -sf tmp > source 2>&1
rm objdump_name
rm tmp
diff=`diff student source`
if [ -n "$diff" ]
then
    echo "Test4: KO (diff stored in test4.output)"
    echo "$diff" > test4.output
else
    echo "Test4: OK"
fi
rm -f student
rm -f source

# TEST5 #
mv my_objdump objdump_name
./objdump_name tests/**/* > student 2> student
mv objdump_name my_objdump
cp /usr/bin/objdump objdump_name
./objdump_name -sf tests/**/* > source 2> source
rm objdump_name
diff=`diff student source`
if [ -n "$diff" ]
then
    echo "Test5: KO (diff stored in test5.output)"
    echo "$diff" > test5.output
else
    echo "Test5: OK"
fi
rm -f student
rm -f source

# TEST6 #
mv my_nm nm_name
./nm_name tests/**/* > student 2> student
mv nm_name my_nm
cp /usr/bin/nm nm_name
./nm_name tests/**/* > source 2> source
rm nm_name
diff=`awk -f diff.awk student source`
if [ -n "$diff" ]
then
    echo "Test6: KO (diff stored in test6.output)"
    echo "$diff" > test6.output
else
    echo "Test6: OK"
fi
rm -f student
rm -f source
