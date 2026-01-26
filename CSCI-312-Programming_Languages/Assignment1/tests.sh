#!/bin/bash

# README: run the test suite with ./tests.sh
# The number of passed tests and unrecognized characters in frequency.txt will print automatically
# Enter y or n to see the list of passed and/or failed tests

pass_count=0
failed_tests=()
passed_tests=()
test_count=0

unrecognized=$(find linux/sound/ -type f -name "*.c" -exec cat {} + | ./scanner | awk '{if ($1 ~ /^[A-Z_]+$/) print $1}' | grep "^UNRECOGNIZED" | wc -l)

runTest() {
    test_name="$1"
    input="$2"
    expectation="$3"
    ((test_count++))

    scanned_input=$(echo "$input" | ./scanner | sed 's/[ \t]*$//')
    if [[ "$scanned_input" == "$expectation" ]]; then
        ((pass_count++))
	passed_tests+=("$test_name")  # Store passed test names in shell array
    else
        failed_tests+=("$test_name")  # Store failed test names in shell array
    fi
}

#Test each lexeme for correct functionality
runTest "Keywords" "if else return static struct" \
"KEYWORD	if
KEYWORD	else
KEYWORD	return
KEYWORD	static
KEYWORD	struct"

runTest "Identifiers" "var1 _myVar funcName" \
"IDENTIFIER	var1
IDENTIFIER	_myVar
IDENTIFIER	funcName"

runTest "Arithmetic Operators" "+ - * / %" \
"OPERATOR	+
OPERATOR	-
OPERATOR	*
OPERATOR	/
OPERATOR	%"

runTest "Comparison Operators" "== != < > <= >=" \
"COMPARISON_OPERATOR	==
COMPARISON_OPERATOR	!=
COMPARISON_OPERATOR	<
COMPARISON_OPERATOR	>
COMPARISON_OPERATOR	<=
COMPARISON_OPERATOR	>="

runTest "Logical Operators" "&& ||" \
"LOGICAL_OPERATOR	&&
LOGICAL_OPERATOR	||"

runTest "Constants" "123 3.14 0xFF 2E-3" \
"CONSTANT	123
CONSTANT	3.14
CONSTANT	0xFF
CONSTANT	2E-3"

runTest "String Literals" "\"hello world\" \"test123\"" \
"STRING_LITERAL	\"hello world\"
STRING_LITERAL	\"test123\""

runTest "Bitwise Operators" "& \| ^ ~ << >>" \
"BITWISE_OPERATOR	&
BITWISE_OPERATOR	|
BITWISE_OPERATOR	^
BITWISE_OPERATOR	~
BITWISE_OPERATOR	<<
BITWISE_OPERATOR	>>"

runTest "Separators" "() [] {} ; , ." \
"SEPARATOR	(
SEPARATOR	)
SEPARATOR	[
SEPARATOR	]
SEPARATOR	{
SEPARATOR	}
SEPARATOR	;
SEPARATOR	,
SEPARATOR	."

runTest "Assignments" "= += -= *= /=" \
"ASSIGNMENT	=
ASSIGNMENT	+=
ASSIGNMENT	-=
ASSIGNMENT	*=
ASSIGNMENT	/="

# Print the number of tests passed and each of the passed/failed tests (if chosen to do so)
echo "Number of Passed Tests: $pass_count out of $test_count"
echo "Number of Unrecognized Characters in frequency.txt: $unrecognized"
echo "Would you like the list of passed tests? (y or n): "
read -r print_pass
if [[ "$print_pass" == "y" ]]; then
	for test in "${passed_tests[@]}"; do
	        echo "Passed Lexically Analyzing: $test"
	done
fi

echo "Would you like the list of failed tests? (y or n): "
read -r print_fail
if [[ "$print_fail" == "y" ]]; then
        for test in "${failed_tests[@]}"; do
                echo "Failed to Lexically Analyze: $test"
        done
fi

