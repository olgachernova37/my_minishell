 Implement these cases to match the usual 42 minishell tests for echo. Be concise: parse arguments (argv[]) and treat any leading argument matching ^-n+$ as the -n option (allow multiple), do NOT implement -e escape processing, print arguments separated by single spaces, and control the trailing newline with -n. Return exit status 0.

List of inputs and expected behavior (examples show what should be printed):

echo

prints: "\n" (just a newline)
echo hello

prints: "hello\n"
echo hello world

prints: "hello world\n"
echo hello world (multiple spaces in command line → tokenization removes extras)

prints: "hello world\n"
echo "hello world" (quoted arg preserves internal spaces)

prints: "hello world\n"
echo '' or echo ""

prints: "\n" (empty argument produces empty field; with no other args it's just newline)
echo a "" b

prints: "a b\n" (note two spaces between a and b because empty arg is an empty field)
echo -n

prints: "" (no newline)
echo -n hello

prints: "hello" (no trailing newline)
echo -nnn hello or echo -n -n hello

treat all as -n: prints "hello" (no newline)
echo -n -e hello

parse leading -n as option; "-e" is a normal argument: prints "-e hello" with no newline (do NOT interpret \n escapes)
echo -ne hello

do NOT implement -e behavior; if "-ne" does not match ^-n+$ it should be treated as an argument and printed (so output depends on parser rule — safer: only accept /^-n+$/ as option)
echo -nfoo

"-nfoo" does NOT match /^-n+$/ → treat as normal argument: prints "-nfoo\n"
echo "\t" or echo '\n'

do NOT expand escapes: prints "\t\n" (i.e., backslash characters shown) then newline
echo " " (quoted spaces-only argument)

prints three spaces followed by newline
echo -n "" (only empty arg with -n)

prints nothing, no newline
echo (many args) long/UTF-8 content

print all args separated by single spaces, newline unless -n present
Return code:

echo should exit/return status 0 on normal operation
Implementation notes:

Option parsing: scan argv from index 1 while arg matches regex ^-n+$, set suppress_newline = true. Stop at first arg that does not match.
Do not implement -e, -E, or other options.
Do not interpret backslash escapes; quoted strings are already passed as single argv entries by your tokenizer.
Print arguments separated by single spaces in the order from argv after option parsing.
Preserve empty arguments (""), causing adjacent spaces in output.
That set covers the typical 42 tests and edge cases you’ll need.

Environment Variables
- Execute echo with some $ variables as argumentss
- Check that $ is interprated as an environment variable
- Check that double quotes interpolate $
- Check that $USER exist or set it.
- echo "$USER" should print the value of $USER

- set USER environment variable.
- Test echo "'$USER'" this should print 'USER_VALUE'
- Test echo '"$USER"' this should print "$USER"