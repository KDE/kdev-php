#/bin/bash

if [[ "$(which php-parser)" == "" ]]; then
  echo "ERROR: cannot find php-parser in your PATH!"
  exit 1
fi

if [ ! -d "$1" ]; then
  echo "USAGE: $0 /path/to/php-tests"
  exit 2
fi

pass=""
fail=""

path=$1
shift 1

if [ ! -d /tmp/php-parser-tests ]; then
  mkdir /tmp/php-parser-tests
fi

for f in $(find "$path" -type f -name "*.phpt"); do
  base=$(basename $f)
  perl -ne '(/^--FILE--$/../^--EXPECT(F)?--$/) && print' "$f" | egrep -v '^--(FILE|EXPECT(F)?)--$' > /tmp/$base
  fail=$(egrep '^Parse error: ' $f)
  if php-parser /tmp/$base &>/tmp/$base.log; then
    if [[ "$fail" == "" ]]; then
      echo "passed $base"
      pass=$(echo -e "$pass\n$base")
    else
      echo
      echo "failed $base"
      cat /tmp/$base.log
      echo
      fail=$(echo -e "$fail\n$base")
    fi
  else
    if [[ "$fail" == "" ]]; then
      echo
      echo "failed $base"
      cat /tmp/$base.log
      echo
      fail=$(echo -e "$fail\n$base")
    else
      echo "passed $base"
      pass=$(echo -e "$pass\n$base")
    fi
  fi
done

echo
echo "PASSED:"
echo

echo "$pass"
echo
echo "FAILED:"
echo
echo "$fail"
