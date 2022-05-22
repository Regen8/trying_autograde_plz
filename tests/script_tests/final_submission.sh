touch COMPILE_ERRORS
touch DEBUG
touch GCOV_ERRORS
touch OUTPUT
touch RUN_ERRORS
touch MISSING_COVERAGE

fail () {
  printf "FAIL\n"
  exit 1
}

echo 0.0 > OUTPUT

SOURCE=("function.cpp" "main.cpp")
HEADERS=("function.h")
FILES=("${SOURCE[@]}" "${HEADERS[@]}")

for file in "${FILES[@]}"; do
  printf "%s exists? " "$file"
  if [ -f "$file" ]; then
    printf "OK\n"
  else
    fail
  fi
done

printf "compiles without errors? "
g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ "${SOURCE[@]}" 1>OUT 2>ERR
ret=$?
if [ $ret -eq 0 ]; then
  printf "OK\n"
else
  cat ERR
  fail
fi

printf "compiles without warnings? "
if [ -s ERR ]; then
  cat ERR
  fail
else
  printf "OK\n"
fi

echo 100.0 > OUTPUT