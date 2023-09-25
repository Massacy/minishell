#!/bin/bash
assert() {
  # テストしようとしている内容をprint
	printf '%-50s:' "\"$1\""

	# bashの出力をcmpに保存
	echo -n -e "$1" | bash >cmp 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	echo -n -e "$1" | ./minishell >out 2>&-
	# minishellのexit statusをactualに代入
	actual=$?

	# bashとminishellの出力を比較
	diff cmp out >/dev/null && echo -ne '  diff \x1b[32mOK\x1b[39m' || echo -ne '  diff \x1b[31mNG\x1b[39m'

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -ne '  status \x1b[32mOK\x1b[39m'
	else
		echo -ne "  status \x1b[31mNG\x1b[39m, expected $expected but got $actual"
	fi
	echo
}

cleanup() {
	rm -f cmp out a.out print_args
}

# Generate Executable
cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

assert 'echo -n hello'

# assert 'echo "hello      world"'

# assert 'echo "hello world"'
# assert 'echo "'hello world'"' # これが正常動作しない $1を$*に変えると動く。
# assert 'echo '"hello world"''
# assert 'echo "'"hello world"'"'
# assert 'echo '"'hello world'"''

# assert 'echo "'hello'" "world"'

# Absolute path commands without args 
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

# Tokenize
## unquoted word
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

## single quote
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"

## double quote
assert './print_args "hello   world" "42Tokyo"'
assert 'echo "hello   world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""

## combination
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""

cleanup
echo 'all OK'