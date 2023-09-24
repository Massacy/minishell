#!/bin/bash
assert() {
  # テストしようとしている内容をprint
	printf '%-30s:' "$1"

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

# Generate Executable
cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

assert ''
assert 'echo'
assert 'pwd'
assert 'ls'

assert 'a.out'
assert 'nosuchfile'


assert 'echo -n hello'

# assert 'echo "hello      world"'

assert 'echo "hello world"'
assert 'echo "'hello world'"' # これが正常動作しない $1を$*に変えると動く。
assert 'echo '"hello world"''
assert 'echo "'"hello world"'"'
assert 'echo '"'hello world'"''

assert 'echo "'hello'" "world"'
