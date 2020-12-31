
#                   BUILT-IN ECHO

echo  "###### ECHO ######" >> mini_file.txt

./minishell "echo    hello    world"    >> mini_file.txt

./minishell "echo hello world" >> mini_file.txt

#./minishell "ech\"o\" hello" >> mini_file.txt

#./minishell "ech'o' hello" >> mini_file.txt

#./minishell "ec\"ho\" hello" >> mini_file.txt

#./minishell "ech\"\"\"o\"\"\" hello" >> mini_file.txt

# ./minishell "echo"  >> mini_file.txt FAIL

./minishell "echo '\$PATH' " >> mini_file.txt

./minishell "echo \"hello 'world'\"" >> mini_file.txt

./minishell "echo hello \$" >> mini_file.txt

./minishell "echo 'hello \"world\" '" >> mini_file.txt

./minishell  "echo this \"is \"a tes't'" >> mini_file.txt

 ./minishell "echo hello \"my\"friend" >> mini_file.txt

./minishell "echo I 'like'\$PATH" >> mini_file.txt

./minishell "echo mol\"abh\" 'ai'ri" >> mini_file.txt

./minishell "echo \"hello \$mouad\"" >> mini_file.txt

./minishell "echo ..." >> mini_file.txt

#               BUILT_IN PWD

echo  "###### PWD ######" >> mini_file.txt

./minishell "pwd" >> mini_file.txt

./minishell "pwd pwd " >> mini_file.txt

./minishell "pwd pwd pwd pwd pwd pwd" >> mini_file.txt

./minishell "pwd pwd pwd pWd pwd pwd" >> mini_file.txt

./minishell "Pwd pwd pwd pwd pwd pwd" >> mini_file.txt

./minishell "pwd pwd pwd pwd pwd pwD" >> mini_file.txt

./minishell "PWD" >> mini_file.txt

./minishell "PWD pwd" >> mini_file.txt