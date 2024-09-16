#!/ bin / bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="bytes.txt"
rm -rf log.txt
echo "" > log.txt

make

for var in -b -e -n -s -t -v
do
          TEST1="$var $TEST_FILE"
          echo "$TEST1"
          ./_cat $TEST1 > _cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s _cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files _cat.txt and cat.txt are identical" ]
            then
              echo "$TEST1 - SUCCESS" 
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm _cat.txt cat.txt
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $TEST_FILE"
          echo "$TEST1"
          ./_cat $TEST1 > _cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s _cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files _cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm _cat.txt cat.txt
        fi
  done
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
      for var3 in -b -e -n -s -t -v
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var $var2 $var3 $TEST_FILE"
          echo "$TEST1"
          ./_cat $TEST1 > _cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s _cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files _cat.txt and cat.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm _cat.txt cat.txt

        fi
      done
  done
done

for var in -b -e -n -s -t -v
do
  for var2 in -b -e -n -s -t -v
  do
      for var3 in -b -e -n -s -t -v
      do
          for var4 in -b -e -n -s -t -v
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $TEST_FILE"
              echo "$TEST1"
              ./_cat $TEST1 > _cat.txt
              cat $TEST1 > cat.txt
              DIFF_RES="$(diff -s _cat.txt cat.txt)"
              if [ "$DIFF_RES" == "Files _cat.txt and cat.txt are identical" ]
                then
                  (( COUNTER_SUCCESS++ ))
                else
                  echo "$TEST1" >> log.txt
                  (( COUNTER_FAIL++ ))
              fi
              rm _cat.txt cat.txt

            fi
          done
      done
  done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"

make clean